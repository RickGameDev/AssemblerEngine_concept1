// Index
// [SECTION] Includes
// [SECTION] Globals
// [SECTION] Imgui Initialization
// [SECTION] Imgui Viewport
// [SECTION] Imgui Styles
// [SECTION] Imgui API

//-----------------------------------------------------------------------------
// [SECTION] Includes
//-----------------------------------------------------------------------------
#include "imgui.h"
#include "shaders.h"

#include <core/core.h>
#include <math/mat4.h>
#include <math/vec2.h>
#include <apis/api_registry.h>
#include <apis/imgui.h>
#include <apis/window.h>
#include <apis/opengl_backend.h>
#include <apis/renderer.h>
#include <apis/shader.h>
#include <apis/camera.h>

#include <string.h>

//-----------------------------------------------------------------------------
// [SECTION] Globals
//-----------------------------------------------------------------------------
struct ae_window_api* window_api = NULL;
struct ae_opengl_backend_api* render_backend_api = NULL;
struct ae_renderer_api* render_api = NULL;
struct ae_shader_api* shader_api = NULL;
struct ae_camera_api* camera_api = NULL;
static struct ae_render_batch* render_batch = NULL;
static struct ae_camera* camera = NULL;

struct ae_imgui_context context = { 0 };
static struct ae_draw_params draw_data = { .position = {0.0f, 0.0f, -0.1f } };

//-----------------------------------------------------------------------------
// [SECTION] Imgui Initialization
//-----------------------------------------------------------------------------
static void ae_imgui_init(struct ae_window* window)
{
    vector_window_init(&context.window_stack, 1);
    vector_viewport_init(&context.viewport_stack, 1);
    vector_vec4_init(&context.background_color_stack, 0);
    vector_vec4_init(&context.border_color_stack, 0);
    vector_vec4_init(&context.font_color_stack, 0);
    vector_vec4_init(&context.padding_stack, 0);
    vector_vec4_init(&context.margin_stack, 0);
    vector_vec4_init(&context.border_width_stack, 0);
    vector_vec4_init(&context.border_radius_stack, 0);
    vector_vec2_init(&context.size_stack, 0);
    vector_float_init(&context.font_size_stack, 0);
    vector_float_init(&context.font_weigth_stack, 0);
    vector_uint_init(&context.texture_stack, 0);
    vector_uint_init(&context.text_flags_stack, 0);

    context.current_viewport_index = 0;
    context.current_window_index = 0;

    struct ae_imgui_viewport main_viewport = { 0 };
    ae_vec2_copy(window->size, main_viewport.size);
    ae_vec2_copy((vec2)
    {
        0.0f, 0.0f
    }, main_viewport.position);

    vector_window_push_back(&context.window_stack, window);
    vector_viewport_push_back(&context.viewport_stack, main_viewport);

    char output[256] = { 0 };
    struct ae_shader* shader = shader_api->create_basic(output, 256, default_vertex, default_fragment);

    if (!shader)
    {
        return;
    }

    render_batch = render_api->render_batch_create(shader, 4096);
    camera = camera_api->create_orthographic((vec3)
    {
        0, 0, 0
    }, window->size[0] / window->size[1], 0.0f, 1000.0f, 0.0f, 1000.0f, 0.0f, 1.0f);
    float L = window->position[0];
    float R = window->position[0] + window->size[0];
    float T = window->position[0];
    float B = window->position[0] + window->size[1];

    mat4 ortho = {
        { 2.0f / (R - L),		0.0f,				0.0f,	0.0f },
        { 0.0f,					2.0f / (T - B),		0.0f,	0.0f },
        { 0.0f,					0.0f,			   -1.0f,	0.0f },
        { (R + L) / (L - R),	(T + B) / (B - T),	0.0f,   1.0f },
    };

    ae_mat4_copy(ortho, camera->view_projection);
}

//-----------------------------------------------------------------------------
// [SECTION] Imgui Viewport
//-----------------------------------------------------------------------------
void ae_imgui_start_viewport(const char* name)
{
    AE_UNREFERENCED_PARAMETER(name);

    struct ae_imgui_viewport* parent_viewport = vector_viewport_ptr_at(&context.viewport_stack, context.current_viewport_index);
    struct ae_imgui_viewport* current_viewport = NULL;

    // get existing, else create new
    if (context.viewport_stack.size > ++context.current_viewport_index)
    {
        current_viewport = vector_viewport_ptr_at(&context.viewport_stack, ++context.current_viewport_index);
    }
    else
    {
        current_viewport = vector_viewport_emplace_back(&context.viewport_stack);
        current_viewport->window_id = parent_viewport->window_id;
        ae_vec2_copy(parent_viewport->position, current_viewport->position);
    }

    struct ae_window* window = vector_window_at(&context.window_stack, current_viewport->window_id);
    render_backend_api->set_window(render_backend_api->get(), window);

    float* size = vector_vec2_last(&context.size_stack);
    float* bg_color = vector_vec4_last(&context.background_color_stack);

    ae_vec2_copy(size, current_viewport->size);
    ae_vec2_add(parent_viewport->position, current_viewport->position, current_viewport->position);

    render_api->render_scene_start(camera);
    render_api->render_batch_start(render_batch);

    ae_vec2_copy(size, draw_data.size);
    ae_vec2_copy(&current_viewport->position[0], &draw_data.position[0]);
    ae_vec4_copy(bg_color, draw_data.color);

    render_api->render_batch_draw(render_batch, &draw_data);
    render_api->render_batch_end(render_batch);
    //struct ae_window* parent = vector_ae_window_at(context.windows, context.current_window_id);
    //struct ae_window* child = NULL;

    //if (context.windows->size == ++context.current_window_id)
    //{
    //	child_window_params.title = name;

    //	child = window_api->create_child(parent, &child_window_params);

    //	vector_ae_window_push_back(context.windows, child);
    //	window_api->show(child, true);
    //}

    //if (!child)
    //	child = vector_ae_window_at(context.windows, context.current_window_id);

    //render_backend_api->set_window(render_backend_api->get(), child);

    //render_api->render_scene_start(camera);
    //render_api->render_batch_start(render_batch);

    //// title bar
    //ae_imgui_draw_title(child);

    //// body

    //render_api->render_batch_end(render_batch);
}

void ae_imgui_end_viewport()
{
    //struct ae_window* current = vector_ae_window_at(context.windows, context.current_window_id);
    //struct ae_window* parent = vector_ae_window_at(context.windows, --context.current_window_id);

    //window_api->update(current);
    //render_backend_api->set_window(render_backend_api->get(), parent);
}

//-----------------------------------------------------------------------------
// [SECTION] Imgui Styles
//-----------------------------------------------------------------------------

void ae_imgui_styles_push_size(vec2 size)
{
    vector_vec2_push_back(&context.size_stack, size);
}

void ae_imgui_styles_pop_size()
{
    vector_vec2_pop_back(&context.size_stack);
}

void ae_imgui_styles_push_padding(vec4 padding)
{
    vector_vec4_push_back(&context.padding_stack, padding);
}

void ae_imgui_styles_pop_padding()
{
    vector_vec4_pop_back(&context.padding_stack);
}

void ae_imgui_styles_push_margin(vec4 margin)
{
    vector_vec4_push_back(&context.margin_stack, margin);
}

void ae_imgui_styles_pop_margin()
{
    vector_vec4_pop_back(&context.margin_stack);
}

void ae_imgui_styles_push_background_color(vec4 color)
{
    vector_vec4_push_back(&context.background_color_stack, color);
}

void ae_imgui_styles_pop_background_color()
{
    vector_vec4_pop_back(&context.background_color_stack);
}

//-----------------------------------------------------------------------------
// [SECTION] Imgui API
//-----------------------------------------------------------------------------
static struct ae_imgui_api imgui_api = {
    .init = ae_imgui_init,
    .start_viewport = ae_imgui_start_viewport,
    .end_viewport = ae_imgui_end_viewport,
    .styles_push_size = ae_imgui_styles_push_size,
    .styles_pop_size = ae_imgui_styles_pop_size,
    .styles_push_padding = ae_imgui_styles_push_padding,
    .styles_pop_padding = ae_imgui_styles_pop_padding,
    .styles_push_margin = ae_imgui_styles_push_margin,
    .styles_pop_margin = ae_imgui_styles_pop_margin,
    .styles_push_background_color = ae_imgui_styles_push_background_color,
    .styles_pop_background_color = ae_imgui_styles_pop_background_color
};

AE_DLL_EXPORT void plugin_load(struct ae_api_registry_api* registry, bool reload)
{
    AE_UNREFERENCED_PARAMETER(reload);

    window_api = ae_get_api(registry, ae_window_api);
    render_backend_api = ae_get_api(registry, ae_opengl_backend_api);
    render_api = ae_get_api(registry, ae_renderer_api);
    shader_api = ae_get_api(registry, ae_shader_api);
    camera_api = ae_get_api(registry, ae_camera_api);
    ae_set_api(registry, ae_imgui_api, &imgui_api);
}

AE_DLL_EXPORT void plugin_unload(struct ae_api_registry_api* registry)
{
    AE_UNREFERENCED_PARAMETER(registry);
}
