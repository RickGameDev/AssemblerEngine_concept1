#include "opengl_shader.h"
#include "glad/glad.h"

#include <apis/shader.h>
#include <math/io.h>
#include <math/struct.h>

#define AE_MAX_SHADER_STAGES 5

static int32_t ubo_view_projection_matrix = 0;

void ae_shader_set_view_projection(float* view_projection)
{
	glNamedBufferSubData(ubo_view_projection_matrix, 0, sizeof(mat4), (float*)view_projection);
}

void ae_shader_set_blending(struct ae_shader* shader, bool enable, uint32_t source, uint32_t destination)
{
	if (shader == NULL)
		return;

	if (enable)
	{
		shader->enable_blending = true;
		shader->blend_source = source;
		shader->blend_destination = destination;
	}
	else
	{
		shader->enable_blending = false;
	}
}
void ae_shader_set_depth_test(struct ae_shader* shader, bool enable)
{
	if (shader == NULL)
		return;

	if (enable)
	{
		shader->enable_depth_test = true;
	}
	else
	{
		shader->enable_depth_test = false;
	}
}

void ae_shader_set_current_shader(struct ae_shader* shader)
{
	if (shader->enable_blending)
	{
		glEnable(GL_BLEND);
		glBlendFunc(shader->blend_source, shader->blend_destination);
	}

	if (shader->enable_depth_test)
	{
		glEnable(GL_DEPTH_TEST);
	}

	glUseProgram(shader->id);
}

struct ae_shader* ae_shader_create(
	char* debug_output,
	int32_t debug_output_size,
	char** stage_sources,
	int32_t* stage_sizes,
	int32_t* stage_types,
	int32_t stage_count)
{
	if (stage_count > AE_MAX_SHADER_STAGES)
		return NULL;

	struct ae_shader* out = NULL;

	if ((out = malloc(sizeof(*out))) == NULL)
		return NULL;

	if (ubo_view_projection_matrix == 0)
	{
		glCreateBuffers(1, &ubo_view_projection_matrix);
		glNamedBufferStorage(ubo_view_projection_matrix, sizeof(mat4), NULL, GL_DYNAMIC_STORAGE_BIT);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo_view_projection_matrix);
	}

	int32_t stage_ids[AE_MAX_SHADER_STAGES] = { 0 };
	int32_t stage_ids_count = 0;
	int32_t success = 0;

	for (int i = 0; i < stage_count; ++i)
	{
		if (stage_sources[i] == NULL)
			return NULL;

		int32_t stage_id = glCreateShader(stage_types[i]);
		glShaderSource(stage_id, 1, &stage_sources[i], &stage_sizes[i]);
		glCompileShader(stage_id);
		glGetShaderiv(stage_id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			glGetShaderInfoLog(stage_id, debug_output_size, NULL, debug_output);
			free(out);
			return NULL;
		}

		stage_ids[i] = stage_id;
		stage_ids_count++;
	}

	out->id = glCreateProgram();

	for (int32_t i = 0; i < stage_ids_count; i++)
	{
		glAttachShader(out->id, stage_ids[i]);
	}

	glLinkProgram(out->id);
	glGetProgramiv(out->id, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(out->id, debug_output_size, NULL, debug_output);
		glDeleteProgram(out->id);
		free(out);
		return NULL;
	}

	for (int32_t i = 0; i < stage_ids_count; i++)
	{
		glDeleteShader(stage_ids[i]);
	}

	out->enable_blending = false;
	out->enable_depth_test = false;

	return out;
}

struct ae_shader* ae_shader_create_basic(
	char* debug_output,
	int32_t debug_output_size,
	char* vertex_shader,
	char* fragment_shader)
{
	char* stage_sources[2] = { vertex_shader, fragment_shader };
	int32_t stages_types[2] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };
	int32_t stage_sizes[2] = { (int32_t)strlen(vertex_shader), (int32_t)strlen(fragment_shader) };
	return ae_shader_create(debug_output, debug_output_size, stage_sources, stage_sizes, stages_types, 2);
}

void ae_shader_terminate(int32_t id)
{
	glDeleteProgram(id);
}
