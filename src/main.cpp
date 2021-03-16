#include <Windows.h>
#include <stdio.h>



extern "C" void __declspec(dllexport) dllStartPlugin(void)
{
    AllocConsole();
    freopen("CONOUT$","w", stdout);
}
extern "C" void __declspec(dllexport) dllStopPlugin(void)
{
}