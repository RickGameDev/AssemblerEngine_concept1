#pragma once

#include "core/types.h"

struct ae_application;
struct ae_window;

struct ae_application_api
{
	struct ae_application*	(*get)();
	struct ae_application*	(*create)(int argc, char** argv);
	void					(*exit)(struct ae_application* application);
	bool  					(*update)(struct ae_application* application);
	struct ae_window*		(*get_window)(struct ae_application* application);
	struct ae_window*		(*create_child_window)(struct ae_application* application);
};