#include <stdafx.h>
#include <varargs.h>

enum CallingConvention {
    Winapi = 1,
    Cdecl = 2,
    StdCall = 3,
    ThisCall = 4,
    FastCall = 5,
    x64Call
};

extern "C"
__declspec(dllexport)
void Shinobi_NativeCallVoid(void* address, CallingConvention cc, ...)
{
#if _M_X64

    (((void(*)(...))address)
#else
#error "32-bit compilation of native calls Not implemented"
#endif

}