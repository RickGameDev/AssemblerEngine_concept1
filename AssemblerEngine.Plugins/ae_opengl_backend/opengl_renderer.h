#pragma once

#include <core/types.h>

struct ae_render_batch;
struct ae_camera;
struct ae_draw_params;
struct ae_textured_draw_params;
struct ae_shader;

struct ae_render_batch* ae_render_batch_create(struct ae_shader* const shader, const uint32_t max_quad_count);
void ae_render_batch_destroy(struct ae_render_batch* batch);
void ae_render_scene_start(const struct ae_camera* camera);
void ae_render_batch_start(const struct ae_render_batch* batch);
void ae_render_batch_end(struct ae_render_batch* batch);
void ae_render_batch_draw(struct ae_render_batch* batch,  struct ae_draw_params* const params);
void ae_render_batch_draw_textured(struct ae_render_batch* batch, struct ae_textured_draw_params* const params);