#include <Reclaimer.h>

#include <Ogre.h>
#include <OgrePlugin.h>
#include <Threading/OgreThreads.h>

#include <MyGUI.h>
#include <Kenshi.h>
#include <ReclaimerVM.h>


void ReclaimerMain::install()
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
void ReclaimerMain::initialise()
{
    printf("ReclaimerMain::initialise()\n");
    m_vm = new ReclaimerVM();
    m_vm->StartREPL();
}

/** Perform any tasks the plugin needs to perform when the system is shut down.
@remarks An implementation must be supplied for this method.
This method is called just before key parts of the system are unloaded,
such as rendersystems being shut down. You should use this hook to free up
resources and decouple custom objects from the OGRE system, whilst all the
instances of other plugins (e.g. rendersystems) still exist.
*/
void ReclaimerMain::shutdown()
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
void ReclaimerMain::uninstall()
{
    printf("ReclaimerMain::uninstall()\n");
}