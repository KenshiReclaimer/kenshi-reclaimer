#include "RVAPtr.h"

uintptr_t RVAPtrCore::c_base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));