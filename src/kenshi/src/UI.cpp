#include "../UI.h"

#include <stdio.h>

MyGUI::Gui* Kenshi::getGuiInstance()
{
    // 48 8B D0 48 8D 45 C7 48 89 44 24 48
    static RVAPtr<MyGUI::Gui*> c_inst(0x1AAD858);
    printf("getGuiInstance() = %p\n", c_inst.GetUIntPtr());
    return *c_inst;
}