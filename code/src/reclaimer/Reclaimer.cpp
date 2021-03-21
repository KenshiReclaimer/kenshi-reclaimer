#include <reclaimer/Reclaimer.h>
#include <reclaimer/ReclaimerVM.h>

#include <ogre/Ogre.h>
#include <ogre/OgrePlugin.h>
#include <ogre/Threading/OgreThreads.h>

#include <mygui/MyGUI.h>

#include <kenshi/Kenshi.h>
#include <kenshi/GameWorld.h>
#include <kenshi/ModInfo.h>

#include <iostream>

#define testthing(x) printf(#x##": %p\n", &##x)
void ReclaimerMain::install()
{
    printf("ReclaimerMain::install()\n");

    auto& game = Kenshi::GetGameWorld();

    printf("[DEBUG] gameWorld = %p\n", &game);

    testthing(game.dataMgr1);
    testthing(game.dataMgr2);
    testthing(game.dataMgr3);
    testthing(game.factionData);
    testthing(game.loadedMods);

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


    printf(" == Mod List == \n");

    auto& game = Kenshi::GetGameWorld();

    printf("loadedMods: %p <count=%d>\n", &game.loadedMods, game.availableMods.size());
    for(Kenshi::ModInfo* v : game.availableMods)
    {
        printf("modName: %s\n", v->modName.c_str());
        printf("filePath: %s\n", v->filePath.c_str());
        printf("fileDir: %s\n", v->fileDir.c_str());
        printf("assetPath: %s\n", v->assetPath.c_str());
        printf("displayName: %s\n", v->displayName.c_str());
        printf("author: %s\n", v->author.c_str());
        printf("\n");
    }


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