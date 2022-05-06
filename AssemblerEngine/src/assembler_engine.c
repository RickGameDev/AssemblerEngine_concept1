#include "AssemblerEngine/assembler_engine.h"

#include <assert.h>

struct ae_api_registry_api* ae_global_api_registry_api = NULL;
struct ae_plugin_registry_api* ae_global_plugin_registry_api = NULL;

bool ae_assembler_engine_init()
{
	assert(!ae_global_api_registry_api);
	assert(!ae_global_plugin_registry_api);

	if (!(ae_global_api_registry_api = ae_api_registry_new()))
		return false;

	if (!(ae_global_plugin_registry_api = ae_plugin_registry_new()))
		return false;

	return true;
}

void ae_assembler_engine_free()
{
	assert(!ae_global_api_registry_api);
	assert(!ae_global_plugin_registry_api);

	ae_plugin_registry_free(ae_global_plugin_registry_api);
	ae_api_registry_api_free(ae_global_api_registry_api);
}