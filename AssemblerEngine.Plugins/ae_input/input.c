#include <core/core.h>
#include <apis/api_registry.h>
#include <apis/input.h>

struct ae_input_source
{

};

static const struct ae_input_api input_api =
{

};

AE_DLL_EXPORT void plugin_load(struct ae_api_registry_api* registry, bool reload)
{
	AE_UNREFERENCED_PARAMETER(registry);
	AE_UNREFERENCED_PARAMETER(reload);
}

AE_DLL_EXPORT void plugin_unload(struct ae_api_registry_api* registry)
{
	AE_UNREFERENCED_PARAMETER(reload);
}
