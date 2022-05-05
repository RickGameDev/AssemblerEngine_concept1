#if defined(_MSC_VER)
//  Microsoft 
#define AE_DLL_EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
//  GCC
#define AE_DLL_EXPORT __attribute__((visibility("default")))
#else
//  do nothing and hope for the best?
#define AE_DLL_EXPORT
#pragma warning Unknown dynamic link import/export semantics.
#endif