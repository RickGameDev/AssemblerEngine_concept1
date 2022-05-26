
#include <apis/camera.h>
#include <apis/api_registry.h>
#include <core/core.h>
#include <math/mat4.h>
#include <math/affine.h>
#include <math/cam.h>

#include <stdlib.h>

static struct ae_camera* ae_camera_create_orthograpic(
	vec3 position,
	const float aspect_ratio,
	const float left,
	const float right,
	const float bottom,
	const float top,
	const float near,
	const float far)
{
	struct ae_camera* camera = malloc(sizeof(*camera));
	
	if (!camera)
		return NULL;

	ae_mat4_identity(camera->view);
	ae_translate(camera->view, position);
	ae_ortho(aspect_ratio * left, aspect_ratio * right, bottom, top, near, far, camera->projection);
	ae_mul(camera->view, camera->projection, camera->view_projection);

	return camera;
}

static void ae_camera_destroy(struct ae_camera* camera)
{
	free(camera);
}

static const struct ae_camera_api camera_api =
{
	.create_orthographic = ae_camera_create_orthograpic,
	.destroy = ae_camera_destroy,
};

AE_DLL_EXPORT void plugin_load(struct ae_api_registry_api* registry, bool reload)
{
	AE_UNREFERENCED_PARAMETER(reload);

	ae_set_api(registry, ae_camera_api, &camera_api);
}

AE_DLL_EXPORT void plugin_unload(struct ae_api_registry_api* registry)
{
	AE_UNREFERENCED_PARAMETER(registry);
}
