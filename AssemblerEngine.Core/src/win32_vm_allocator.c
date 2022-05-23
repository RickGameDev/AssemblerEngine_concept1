#include <core/os.h>
//
//#include <assert.h>
//
//struct ae_allocator_o
//{
//	size_t page_size;
//};
//
//struct ae_allocator_o* ae_vm_allocator_init(const size_t page_size)
//{
//	static struct ae_allocator_o allocator = { 0 };
//	allocator.page_size = page_size;
//
//	return &allocator;
//}
//
//void* ae_vm_allocator_malloc(struct ae_allocator_o* allocator, size_t size)
//{
//	assert(size % allocator->page_size);
//
//	return VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
//}
//
//void* ae_vm_allocator_realloc(struct ae_allocator_o* const allocator, void* buffer, const size_t old_size, const size_t new_size)
//{
//	assert(old_size % allocator->page_size);
//	assert(new_size % allocator->page_size);
//	assert(new_size > old_size);
//
//	if (buffer && new_size)
//		return VirtualAlloc(((char*)buffer) + old_size, new_size - old_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
//
//	if (!buffer && new_size)
//		return VirtualAlloc(buffer, new_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
//
//}
//
//void ae_vm_allocator_free(struct ae_allocator_o* allocator, void* buffer)
//{
//	VirtualFree(buffer, 0, MEM_DECOMMIT | MEM_RELEASE);
//}