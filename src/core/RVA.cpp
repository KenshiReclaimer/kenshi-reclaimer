#include "RVA.h"

uintptr_t RVAPtrCore::c_base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));