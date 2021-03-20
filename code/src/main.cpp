#include <stdafx.h>
#include <stdio.h>

#include <ogre/OgreRoot.h>

#include <reclaimer/Reclaimer.h>

ReclaimerMain* g_main = nullptr;

extern "C" void __declspec(dllexport) dllStartPlugin(void)
{
    g_main = new ReclaimerMain();

    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);

    printf("dllStartPlugin()\n");

    Ogre::Root::getSingleton().installPlugin(g_main);
}

extern "C" void __declspec(dllexport) dllStopPlugin(void)
{
    printf("dllStopPlugin()\n");
    
    Ogre::Root::getSingleton().uninstallPlugin(g_main);
    delete g_main;
}