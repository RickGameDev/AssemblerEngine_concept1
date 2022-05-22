#pragma once
#include <core/types.h>


struct ae_logger;

enum ae_log_levels
{
	LEVEL_TRACE, LEVEL_DEBUG, LEVEL_INFO, LEVEL_WARN, LEVEL_ERROR, LEVEL_CRITICAL
};

typedef void (*ae_logger_lock_fn)(void* data);
typedef void (*ae_logger_unlock_fn)(void* data);

struct ae_logging_api
{
	struct ae_logger*	(*get_main_logger)();
	struct ae_logger*	(*get_or_create_main_logger)(const enum ae_log_levels level);
	struct ae_logger*	(*create)(const enum ae_log_levels level);
	struct ae_logger*	(*create_threaded)(const enum ae_log_levels level, ae_logger_lock_fn lock_fn, ae_logger_unlock_fn unlock_fn);
	void				(*enable_threading)(struct ae_logger* logger, ae_logger_lock_fn lock_fn, ae_logger_unlock_fn unlock_fn);
	bool				(*add_console_sink)(struct ae_logger* logger, void* data, const enum ae_log_levels level);
	bool				(*add_file_sink)(struct ae_logger* logger, FILE* file, const enum ae_log_levels level);
	bool				(*set_level)(struct ae_logger* logger, const enum ae_log_levels level);
	void				(*log)(struct ae_logger* logger, const enum ae_log_levels level, const char* file, int32_t line, const char* fmt, ...);
	void				(*log_main)(const enum ae_log_levels level, const char* file, int32_t line, const char* fmt, ...);
};

/// <summary>
/// utility log macro calls log_log with predefined level, file and line
/// </summary>
/// <param name="...">: variadic parameter to pass log string and values to pass to log string</param>
#define ae_log_trace(...) ae_logging_api->log_main(LEVEL_TRACE, __FILE__, __LINE__, __VA_ARGS__)

/// <summary>
/// utility log macro calls log_log with predefined level, file and line
/// </summary>
/// <param name="...">: variadic parameter to pass log string and values to pass to log string</param>
#define ae_log_debug(...) ae_logging_api->log_main(LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)

/// <summary>
/// utility log macro calls log_log with predefined level, file and line
/// </summary>
/// <param name="...">: variadic parameter to pass log string and values to pass to log string</param>
#define ae_log_info(...)  ae_logging_api->log_main(LEVEL_INFO,  __FILE__, __LINE__, __VA_ARGS__)

/// <summary>
/// utility log macro calls log_log with predefined level, file and line
/// </summary>
/// <param name="...">: variadic parameter to pass log string and values to pass to log string</param>
#define ae_log_warn(...)  ae_logging_api->log_main(LEVEL_WARN,  __FILE__, __LINE__, __VA_ARGS__)

/// <summary>
/// utility log macro calls log_log with predefined level, file and line
/// </summary>
/// <param name="...">: variadic parameter to pass log string and values to pass to log string</param>
#define ae_log_error(...) ae_logging_api->log_main(LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)

/// <summary>
/// utility log macro calls log_log with predefined level, file and line
/// </summary>
/// <param name="...">: variadic parameter to pass log string and values to pass to log string</param>
#define ae_log_critical(...) ae_logging_api->log_main(LEVEL_CRITICAL, __FILE__, __LINE__, __VA_ARGS__)