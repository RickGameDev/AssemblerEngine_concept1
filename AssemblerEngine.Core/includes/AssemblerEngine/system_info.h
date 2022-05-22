#pragma once

struct ae_system_info;
struct ae_system_info* ae_system_info_init();

const size_t ae_system_info_get_page_size(const struct ae_system_info* const system_info);

