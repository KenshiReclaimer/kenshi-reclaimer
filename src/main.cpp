#include "stdafx.h"

#include <stdio.h>

#include <Ogre.h>
#include <OgrePlugin.h>
#include <OgreRoot.h>

#include <MyGUI.h>
#include "kenshi/Kenshi.h"

class ReclaimerMain : public Ogre::Plugin
{
    virtual const Ogre::String& getName() const { return "Reclaimer"; };

    /** Perform the plugin initial installation sequence.
    @remarks An implementation must be supplied for this method. It must perform
    the startup tasks necessary to install any rendersystem customisations
    or anything else that is not dependent on system initialisation, ie
    only dependent on the core of Ogre. It must not perform any
    operations that would create rendersystem-specific objects at this stage,
    that should be done in initialise().
    */
    virtual void install() override
    {
        printf("ReclaimerMain::install()\n");
    }

    /** Perform any tasks the plugin needs to perform on full system
        initialisation.
    @remarks An implementation must be supplied for this method. It is called
        just after the system is fully initialised (either after Root::initialise
        if a window is created then, or after the first window is created)
        and therefore all rendersystem functionality is available at this
        time. You can use this hook to create any resources which are
        dependent on a rendersystem or have rendersystem-specific implementations.
    */
    virtual void initialise() override
    {
        printf("ReclaimerMain::initialise()\n");
        auto gui = Kenshi::getGuiInstance();
        printf("ui_instance=%p\n", gui);

    }

    /** Perform any tasks the plugin needs to perform when the system is shut down.
    @remarks An implementation must be supplied for this method.
    This method is called just before key parts of the system are unloaded,
    such as rendersystems being shut down. You should use this hook to free up
    resources and decouple custom objects from the OGRE system, whilst all the
    instances of other plugins (e.g. rendersystems) still exist.
    */
    virtual void shutdown() override
    {
        printf("ReclaimerMain::shutdown()\n");
    }

    /** Perform the final plugin uninstallation sequence.
    @remarks An implementation must be supplied for this method. It must perform
    the cleanup tasks which haven't already been performed in shutdown()
    (e.g. final deletion of custom instances, if you kept them around incase
    the system was reinitialised). At this stage you cannot be sure what other
    plugins are still loaded or active. It must therefore not perform any
    operations that would reference any rendersystem-specific objects - those
    should have been sorted out in the 'shutdown' method.
    */
    virtual void uninstall() override
    {
        printf("ReclaimerMain::uninstall()\n");
    }

    MyGUI::WindowPtr m_mywin;
};


static ReclaimerMain* g_instance = nullptr;


extern "C" void __declspec(dllexport) dllStartPlugin(void)
{
    g_instance = new ReclaimerMain();

    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    printf("dllStartPlugin()\n");

    Ogre::Root::getSingleton().installPlugin(g_instance);
}
extern "C" void __declspec(dllexport) dllStopPlugin(void)
{
    printf("dllStopPlugin()\n");
    
    Ogre::Root::getSingleton().uninstallPlugin(g_instance);
    delete g_instance;
}