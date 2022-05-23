#include "opengl_renderer.h"
#include "opengl_shader.h"
#include "glad/glad.h"

#include <apis/shader.h>
#include <apis/renderer.h>
#include <core/core.h>
#include <math/vec4.h>

#include <stdlib.h>

struct ae_camera
{
	mat4 view;
	mat4 projection;
	mat4 view_projection;
};

struct ae_vertex
{
	vec4 color;
	vec3 position;
	vec2 texture_coordinate;
	float texture_unit;
};

struct ae_render_batch
{
	struct ae_vertex* vertices;
	struct ae_shader* shader;
	uint32_t* textures;
	uint16_t* indices;
	uint32_t vao;
	uint32_t vbo;
	uint32_t ibo;
	uint32_t total_vertex_count;
	uint32_t total_index_count;
	uint32_t total_texture_count;
	uint32_t current_vertex_count;
	uint32_t current_index_count;
	uint32_t current_texture_count;
};

static void upload_batch(struct ae_render_batch* const batch)
{
	glNamedBufferSubData(batch->vbo, 0, batch->current_vertex_count * sizeof(*(batch->vertices)), batch->vertices);
}

static void draw_batch(const struct ae_render_batch* batch)
{
	for (uint16_t i = 0; i < batch->current_texture_count; i++)
		glBindTextureUnit(i, batch->textures[i]);

	glBindVertexArray(batch->vao);
	glDrawElements(GL_TRIANGLES, batch->current_index_count, GL_UNSIGNED_SHORT, 0);
}

static void reset_batch(struct ae_render_batch* batch)
{
	batch->current_vertex_count = 0;
	batch->current_index_count = 0;
	batch->current_texture_count = 1;
}

static void test_batch(struct ae_render_batch* batch)
{
	if (batch->current_index_count >= batch->total_index_count)
	{
		upload_batch(batch);
		draw_batch(batch);
		reset_batch(batch);
	}
}

static void test_batch_with_textures(struct ae_render_batch* batch)
{
	if (batch->current_texture_count >= batch->total_texture_count || batch->current_index_count >= batch->total_index_count)
	{
		upload_batch(batch);
		draw_batch(batch);
		reset_batch(batch);
	}
}

static float get_free_texture_unit(struct ae_render_batch* batch, uint32_t texture_id)
{
	float textureUnit = 1.0;

	for (uint32_t i = 0; i < batch->current_texture_count; i++)
	{
		if (batch->textures[i] == texture_id)
		{
			textureUnit = (float)i;
			break;
		}
	}

	if (textureUnit == 1.0f)
	{
		batch->textures[batch->current_texture_count] = texture_id;
		textureUnit = (float)batch->current_texture_count;
		batch->current_texture_count++;
	}

	return textureUnit;
}

struct ae_render_batch* ae_render_batch_create(struct ae_shader* const shader, const uint32_t max_quad_count)
{
	struct ae_render_batch* batch = malloc(sizeof(*batch));

	if (!batch)
		return NULL;

	batch->total_vertex_count = max_quad_count * 4;
	batch->total_index_count = max_quad_count * 6;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (int32_t*)&batch->total_texture_count);

	batch->vertices = malloc(sizeof(*batch->vertices) * batch->total_vertex_count);

	if (!batch->vertices)
		return NULL;

	batch->textures = malloc(sizeof(*batch->textures) * batch->total_texture_count);

	if (!batch->textures)
		return NULL;

	batch->indices = malloc(sizeof(*batch->indices) * batch->total_index_count);

	if (!batch->indices)
		return NULL;

	batch->shader = shader;

	size_t offset = 0;
	for (size_t i = 0; i < batch->total_index_count; i += 6)
	{
		((uint16_t*)batch->indices)[i] =		(uint16_t)(0 + offset);
		((uint16_t*)batch->indices)[i + 1] =	(uint16_t)(1 + offset);
		((uint16_t*)batch->indices)[i + 2] =	(uint16_t)(2 + offset);			 
		((uint16_t*)batch->indices)[i + 3] =	(uint16_t)(2 + offset);
		((uint16_t*)batch->indices)[i + 4] =	(uint16_t)(3 + offset);
		((uint16_t*)batch->indices)[i + 5] =	(uint16_t)(0 + offset);

		offset += 4;
	}

	glCreateBuffers(1, &batch->vbo);
	glNamedBufferStorage(batch->vbo, sizeof(*batch->vertices) * batch->total_vertex_count, NULL, GL_DYNAMIC_STORAGE_BIT);

	glCreateBuffers(1, &batch->ibo);
	glNamedBufferStorage(batch->ibo, sizeof(*batch->indices) * batch->total_index_count, batch->indices, GL_MAP_READ_BIT | GL_MAP_PERSISTENT_BIT);

	glCreateVertexArrays(1, &batch->vao);

	glVertexArrayVertexBuffer(batch->vao, 0, batch->vbo, 0, sizeof(*batch->vertices));
	glVertexArrayElementBuffer(batch->vao, batch->ibo);

	glEnableVertexArrayAttrib(batch->vao, 0);
	glEnableVertexArrayAttrib(batch->vao, 1);
	glEnableVertexArrayAttrib(batch->vao, 2);
	glEnableVertexArrayAttrib(batch->vao, 3);

	glVertexArrayAttribFormat(batch->vao, 0, 4, GL_FLOAT, GL_FALSE, offsetof(struct ae_vertex, color));
	glVertexArrayAttribFormat(batch->vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(struct ae_vertex, position));
	glVertexArrayAttribFormat(batch->vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(struct ae_vertex, texture_coordinate));
	glVertexArrayAttribFormat(batch->vao, 3, 1, GL_FLOAT, GL_FALSE, offsetof(struct ae_vertex, texture_unit));

	glVertexArrayAttribBinding(batch->vao, 0, 0);
	glVertexArrayAttribBinding(batch->vao, 1, 0);
	glVertexArrayAttribBinding(batch->vao, 2, 0);
	glVertexArrayAttribBinding(batch->vao, 3, 0);

	uint32_t texure;
	int32_t color = 0xffffffff;

	glCreateTextures(GL_TEXTURE_2D, 1, &texure);
	glTextureStorage2D(texure, 1, GL_RGBA8, 1, 1);
	glTextureSubImage2D(texure, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &color);

	int32_t samplers[64] = { 0 };
	samplers[0] = texure;

	for (uint32_t i = 0; i < batch->total_texture_count; i++)
	{
		samplers[i] = i;
		batch->textures[i] = 0;
	}

	batch->textures[0] = texure;

	glUseProgram(batch->shader->id);
	glUniform1iv(glGetUniformLocation(batch->shader->id, "u_textures"), batch->total_texture_count, samplers);

	batch->current_vertex_count = 0;
	batch->current_texture_count = 1;
	batch->current_index_count = 0;

	return batch;
}

void ae_render_batch_destroy(struct ae_render_batch* batch)
{
	glDeleteVertexArrays(1, &batch->vao);
	glDeleteBuffers(1, &batch->vbo);
	glDeleteBuffers(1, &batch->ibo);
	free(batch);
}

void ae_render_scene_start(const struct ae_camera* camera)
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	ae_shader_set_view_projection(&camera->view_projection[0][0]);
}

void ae_render_batch_start(const struct ae_render_batch* batch)
{
	ae_shader_set_current_shader(batch->shader);
}

void ae_render_batch_end(struct ae_render_batch* batch)
{
	upload_batch(batch);
	draw_batch(batch);
	reset_batch(batch);
}

void ae_render_batch_draw(struct ae_render_batch* batch, struct ae_draw_params* const params)
{
	test_batch(batch);

	ae_vec4_copy(&params->color[0], &batch->vertices[batch->current_vertex_count].color[0]);
	batch->vertices[batch->current_vertex_count].position[0] = params->position[0];
	batch->vertices[batch->current_vertex_count].position[1] = params->position[1] + params->size[1];
	batch->vertices[batch->current_vertex_count].position[2] = params->position[2];
	batch->vertices[batch->current_vertex_count].texture_coordinate[0] = 0.0f;
	batch->vertices[batch->current_vertex_count].texture_coordinate[1] = 0.0f;
	batch->vertices[batch->current_vertex_count].texture_unit = 0.0f;

	batch->current_vertex_count++;

	ae_vec4_copy(&params->color[0], &batch->vertices[batch->current_vertex_count].color[0]);
	batch->vertices[batch->current_vertex_count].position[0] = params->position[0] + params->size[0];
	batch->vertices[batch->current_vertex_count].position[1] = params->position[1] + params->size[1];
	batch->vertices[batch->current_vertex_count].position[2] = params->position[2];
	batch->vertices[batch->current_vertex_count].texture_coordinate[0] = 1.0f;
	batch->vertices[batch->current_vertex_count].texture_coordinate[1] = 0.0f;
	batch->vertices[batch->current_vertex_count].texture_unit = 0.0f;

	batch->current_vertex_count++;

	ae_vec4_copy(&params->color[0], &batch->vertices[batch->current_vertex_count].color[0]);
	batch->vertices[batch->current_vertex_count].position[0] = params->position[0] + params->size[0];
	batch->vertices[batch->current_vertex_count].position[1] = params->position[1];
	batch->vertices[batch->current_vertex_count].position[2] = params->position[2];
	batch->vertices[batch->current_vertex_count].texture_coordinate[0] = 1.0f;
	batch->vertices[batch->current_vertex_count].texture_coordinate[1] = 1.0f;
	batch->vertices[batch->current_vertex_count].texture_unit = 0.0f;

	batch->current_vertex_count++;

	ae_vec4_copy(&params->color[0], &batch->vertices[batch->current_vertex_count].color[0]);
	batch->vertices[batch->current_vertex_count].position[0] = params->position[0];
	batch->vertices[batch->current_vertex_count].position[1] = params->position[1];
	batch->vertices[batch->current_vertex_count].position[2] = params->position[2];
	batch->vertices[batch->current_vertex_count].texture_coordinate[0] = 0.0f;
	batch->vertices[batch->current_vertex_count].texture_coordinate[1] = 1.0f;
	batch->vertices[batch->current_vertex_count].texture_unit = 0.0f;

	batch->current_vertex_count++;

	batch->current_index_count += 6;
}

void ae_render_batch_draw_textured(struct ae_render_batch* batch, struct ae_textured_draw_params* const params)
{
	test_batch_with_textures(batch);

	float textureUnit = get_free_texture_unit(batch, params->texture);

	ae_vec4_copy(&params->color[0], &batch->vertices[batch->current_vertex_count].color[0]);
	batch->vertices[batch->current_vertex_count].position[0] = params->position[0];
	batch->vertices[batch->current_vertex_count].position[1] = params->position[1] + params->size[1];
	batch->vertices[batch->current_vertex_count].position[2] = params->position[2];
	batch->vertices[batch->current_vertex_count].texture_coordinate[0] = params->texture_coordinates[0][0];
	batch->vertices[batch->current_vertex_count].texture_coordinate[1] = params->texture_coordinates[0][1];
	batch->vertices[batch->current_vertex_count].texture_unit = textureUnit;

	batch->current_vertex_count++;

	ae_vec4_copy(&params->color[0], &batch->vertices[batch->current_vertex_count].color[0]);
	batch->vertices[batch->current_vertex_count].position[0] = params->position[0] + params->size[0];
	batch->vertices[batch->current_vertex_count].position[1] = params->position[1] + params->size[1];
	batch->vertices[batch->current_vertex_count].position[2] = params->position[2];
	batch->vertices[batch->current_vertex_count].texture_coordinate[0] = params->texture_coordinates[1][0];
	batch->vertices[batch->current_vertex_count].texture_coordinate[1] = params->texture_coordinates[1][1];
	batch->vertices[batch->current_vertex_count].texture_unit = textureUnit;

	batch->current_vertex_count++;

	ae_vec4_copy(&params->color[0], &batch->vertices[batch->current_vertex_count].color[0]);
	batch->vertices[batch->current_vertex_count].position[0] = params->position[0] + params->size[0];
	batch->vertices[batch->current_vertex_count].position[1] = params->position[1];
	batch->vertices[batch->current_vertex_count].position[2] = params->position[2];
	batch->vertices[batch->current_vertex_count].texture_coordinate[0] = params->texture_coordinates[2][0];
	batch->vertices[batch->current_vertex_count].texture_coordinate[1] = params->texture_coordinates[2][1];
	batch->vertices[batch->current_vertex_count].texture_unit = textureUnit;

	batch->current_vertex_count++;

	ae_vec4_copy(&params->color[0], &batch->vertices[batch->current_vertex_count].color[0]);
	batch->vertices[batch->current_vertex_count].position[0] = params->position[0];
	batch->vertices[batch->current_vertex_count].position[1] = params->position[1];
	batch->vertices[batch->current_vertex_count].position[2] = params->position[2];
	batch->vertices[batch->current_vertex_count].texture_coordinate[0] = params->texture_coordinates[3][0];
	batch->vertices[batch->current_vertex_count].texture_coordinate[1] = params->texture_coordinates[3][1];
	batch->vertices[batch->current_vertex_count].texture_unit = textureUnit;

	batch->current_vertex_count++;

	batch->current_index_count += 6;
}