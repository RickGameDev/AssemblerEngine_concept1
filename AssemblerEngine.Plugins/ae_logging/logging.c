#include <apis/logging.h>
#include <apis/api_registry.h>
#include <core/core.h>

#include <stdarg.h>
#include <time.h>
#include <stdio.h>

#ifndef AE_MAX_LOG_SINKS
#define AE_MAX_LOG_SINKS 8
#endif // !AE_MAX_LOG_SINKS

struct ae_sink
{
	void* data;
	enum ae_log_levels level;
};

struct ae_logger_event
{
	va_list arguments;
	const char* fmt;
	const char* file;
	void* data;
	struct tm time;
	enum ae_log_levels level;
	uint32_t line;
};

typedef void (*ae_logger_log_fn)(const struct ae_logger* const logger, struct ae_logger_event* event);

static const char* level_strings[] = {
  "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

#ifdef AE_LOGGER_USE_COLOR
static const char* level_colors[] = {
  "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};
#endif

struct ae_logger
{
	struct ae_sink console_sinks[AE_MAX_LOG_SINKS];
	struct ae_sink file_sinks[AE_MAX_LOG_SINKS];
	struct tm time;
	ae_logger_log_fn log_function;
	ae_logger_lock_fn lock_function;
	ae_logger_unlock_fn unlock_function;

	uint16_t console_sink_count;
	uint16_t file_sink_count;
	enum ae_log_levels level;
};

static struct ae_logger* main_logger = NULL;

static void ae_on_log_to_console(struct ae_logger_event* event)
{
	char buf[16] = { 0 };
	buf[strftime(buf, sizeof(buf), "%H:%M:%S", &event->time)] = '\0';
#ifdef LOGGER_USE_COLOR
	fprintf(
		event->data,
		"%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
		buf,
		level_colors[event->level],
		level_strings[event->level],
		event->file,
		event->line
	);
#else
	fprintf(
		event->data,
		"%s %-5s %s:%d: ",
		buf,
		level_strings[event->level],
		event->file,
		event->line
	);
#endif
	vfprintf(event->data, event->fmt, event->arguments);
	fprintf(event->data, "\n");
	fflush(event->data);
}

static void ae_on_log_to_file(struct ae_logger_event* event)
{
	char buf[64] = { 0 };
	buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &event->time)] = '\0';
	fprintf(
		event->data,
		"%s %-5s %s:%d: ",
		buf,
		level_strings[event->level],
		event->file,
		event->line
	);
	vfprintf(event->data, event->fmt, event->arguments);
	fprintf(event->data, "\n");
	fflush(event->data);
}

static void ae_on_log(const struct ae_logger* const logger, struct ae_logger_event* event)
{
	if (event->level >= logger->level)
	{
		for (int i = 0; i < logger->console_sink_count; i++)
		{
			const struct ae_sink* sink = &logger->console_sinks[i];

			if (event->level >= sink->level)
			{
				event->data = sink->data;
				ae_on_log_to_console(event);
			}
		}

		for (int j = 0; j < logger->file_sink_count; j++)
		{
			const struct ae_sink* sink = &logger->file_sinks[j];

			if (event->level >= sink->level)
			{
				event->data = sink->data;
				ae_on_log_to_file(event);
			}
		}
	}
}

static void ae_on_log_thread_safe(const struct ae_logger* const logger, struct ae_logger_event* event)
{
	if (event->level >= logger->level)
	{
		for (int i = 0; i < logger->console_sink_count; i++)
		{
			logger->lock_function(logger->console_sinks[i].data);

			const struct ae_sink* sink = &logger->console_sinks[i];

			if (event->level >= sink->level)
			{
				event->data = sink->data;
				ae_on_log_to_console(event);
			}

			logger->unlock_function(logger->console_sinks[i].data);
		}

		for (int j = 0; j < logger->file_sink_count; j++)
		{
			logger->lock_function(logger->file_sinks[j].data);

			const struct ae_sink* sink = &logger->file_sinks[j];

			if (event->level >= sink->level)
			{
				event->data = sink->data;
				ae_on_log_to_file(event);
			}

			logger->unlock_function(logger->file_sinks[j].data);
		}
	}
}

struct ae_logger* ae_logger_create(enum ae_log_levels level)
{
	struct ae_logger* logger = malloc(sizeof(*logger));

	if (!logger)
		return NULL;

	logger->level = level;
	logger->log_function = ae_on_log;
	logger->lock_function = NULL;
	logger->unlock_function = NULL;
	logger->console_sink_count = 0;
	logger->file_sink_count = 0;

	return logger;
}

struct ae_logger* ae_logger_create_threaded(enum ae_log_levels level, ae_logger_lock_fn lock_fn, ae_logger_unlock_fn unlock_fn)
{
	struct ae_logger* logger = malloc(sizeof(*logger));

	if (!logger)
		return NULL;

	logger->level = level;
	logger->log_function = ae_on_log_thread_safe;
	logger->lock_function = lock_fn;
	logger->unlock_function = unlock_fn;
	logger->console_sink_count = 0;
	logger->file_sink_count = 0;

	return logger;
}


static bool ae_logger_add_file_sink(struct ae_logger* logger, FILE* file, enum ae_log_levels level)
{
	if (!file)
		return false;

	if (logger->file_sink_count == AE_MAX_LOG_SINKS)
		return false;

	logger->file_sinks[logger->file_sink_count].level = level;
	logger->file_sinks[logger->file_sink_count].data = file;
	logger->file_sink_count++;

	return true;
}

static bool ae_logger_add_console_sink(struct ae_logger* logger, void* data, enum ae_log_levels level)
{
	if (!data)
		return false;

	if (logger->file_sink_count == AE_MAX_LOG_SINKS)
		return false;

	logger->console_sinks[logger->console_sink_count].level = level;
	logger->console_sinks[logger->console_sink_count].data = data;
	logger->console_sink_count++;

	return true;
}

static struct ae_logger* ae_logger_get_main_logger()
{
	return main_logger;
}

static struct ae_logger* ae_logger_get_or_create_main_logger(enum ae_log_levels level)
{
	if (main_logger)
		return main_logger;

	main_logger = ae_logger_create(level);

	ae_logger_add_console_sink(main_logger, stderr, level);

	return main_logger;
}

static void ae_logger_log(struct ae_logger* logger, enum ae_log_levels level, const char* file, int32_t line, const char* fmt, ...)
{
	struct ae_logger_event event = {
	.fmt = fmt,
	.file = file,
	.line = line,
	.level = level,
	};

	// fix warning(C4996) on WIN32
#ifdef WIN32
	time_t t = time(NULL);
	localtime_s(&event.time, &t);
#else
	time_t t = time(NULL);
	event.time = *localtime(&t);
#endif // WIN32

	va_start(event.arguments, fmt);
	logger->log_function(logger, &event);
	va_end(event.arguments);
}

static void ae_logger_log_main(enum ae_log_levels level, const char* file, int32_t line, const char* fmt, ...)
{
	ae_logger_log(main_logger, level, file, line, fmt);
}

static struct ae_logging_api logging_api =
{
	.get_main_logger = ae_logger_get_main_logger,
	.get_or_create_main_logger = ae_logger_get_or_create_main_logger,
	.create = ae_logger_create,
	.create_threaded = ae_logger_create_threaded,
	.add_console_sink = ae_logger_add_console_sink,
	.add_file_sink = ae_logger_add_file_sink,
	.log = ae_logger_log,
	.log_main = ae_logger_log_main
};

AE_DLL_EXPORT void plugin_load(struct ae_api_registry_api* registry, bool reload)
{
	AE_UNREFERENCED_PARAMETER(reload);

	ae_set_api(registry, ae_logging_api, &logging_api);
}

AE_DLL_EXPORT void plugin_unload(struct ae_api_registry_api* registry)
{
	AE_UNREFERENCED_PARAMETER(registry);
}
