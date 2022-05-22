#pragma once

struct ae_ui_tab;

struct ae_ui_tab_api 
{
	struct ae_ui_tab*	(*create)();
	void				(*destroy)();
};