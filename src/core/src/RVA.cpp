#include <RVA.h>

uintptr_t RVACore::c_base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));