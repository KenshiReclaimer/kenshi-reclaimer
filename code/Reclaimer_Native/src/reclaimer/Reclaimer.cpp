#include <reclaimer/Reclaimer.h>

#include <ogre/Ogre.h>
#include <ogre/OgrePlugin.h>
#include <ogre/Threading/OgreThreads.h>

#include <mygui/MyGUI.h>

#include <kenshi/Kenshi.h>
#include <kenshi/GameWorld.h>
#include <kenshi/ModInfo.h>

#include <iostream>
#include <string.h>

// dotnet stuff
#pragma comment(lib, "nethost.lib")

#include <coreclr_delegates.h>
#include <nethost.h>
#include <hostfxr.h>

struct ReclaimerNETHost
{
    HMODULE hHostLib;

    // init core
    hostfxr_initialize_for_runtime_config_fn init_fn;
    hostfxr_get_runtime_delegate_fn get_delegate_fn;
    hostfxr_close_fn close_fn;

    // load/run delegates
    load_assembly_and_get_function_pointer_fn load_assembly_and_get_fn_ptr;
    get_function_pointer_fn get_fn_ptr;

    void PrepareHost()
    {

        char_t host_path[MAX_PATH];
        size_t buffer_size = sizeof(host_path) / sizeof(char_t);
        int rc = get_hostfxr_path(host_path, &buffer_size, nullptr);
        if (rc != 0)
            throw new std::runtime_error("hostfxr not found on machine");

        hHostLib = LoadLibraryW(host_path);

        init_fn = (decltype(init_fn))GetProcAddress(hHostLib, "hostfxr_initialize_for_runtime_config");
        get_delegate_fn = (decltype(get_delegate_fn))GetProcAddress(hHostLib, "hostfxr_get_runtime_delegate");
        close_fn = (decltype(close_fn))GetProcAddress(hHostLib, "hostfxr_close");

    }

    void LoadRuntime()
    {

        hostfxr_handle cxt = nullptr;
        int rc = init_fn(L"Reclaimer.runtimeconfig.json", nullptr, &cxt);
        if (rc != 0 || cxt == nullptr)
        {
            std::cerr << "Init failed: " << std::hex << std::showbase << rc << std::endl;
            close_fn(cxt);
            return;
        }

        // Get the load assembly function pointer
        rc = get_delegate_fn(
            cxt,
            hdt_load_assembly_and_get_function_pointer,
            (void**)&load_assembly_and_get_fn_ptr);
        if (rc != 0 || load_assembly_and_get_fn_ptr == nullptr)
            std::cerr << "hdt_load_assembly_and_get_function_pointer delegate failed: " << std::hex << std::showbase << rc << std::endl;


        rc = get_delegate_fn(
            cxt,
            hdt_get_function_pointer,
            (void**)&get_fn_ptr);
        if (rc != 0 || get_fn_ptr == nullptr)
            std::cerr << "hdt_get_function_pointer delegate failed: " << std::hex << std::showbase << rc << std::endl;

        close_fn(cxt);
    }

    template <typename T>
    T LoadAssembly(const std::wstring& path, const std::wstring& type, const std::wstring& method)
    {
        T fn = nullptr;
        load_assembly_and_get_fn_ptr(
            path.c_str(),
            type.c_str(),
            method.c_str(),
            nullptr,
            nullptr,
            (void**)&fn
            );
            return fn;
    }
};


void ReclaimerMain::install()
{
    printf("ReclaimerMain::install()\n");

    auto& game = Kenshi::GetGameWorld();

    printf("[DEBUG] gameWorld = %p\n", &game);


    printf("Loading .NET 5 Runtime...\n");

    dotnet = new ReclaimerNETHost;
    dotnet->PrepareHost();
    dotnet->LoadRuntime();

    printf("Load Reclaimer.Core.dll.. \n");
    auto start_assembly = dotnet->LoadAssembly<component_entry_point_fn>(
        L"Reclaimer.Core.dll",
        L"Reclaimer.Core.Entry, Reclaimer.Core",
        L"Main"
        );

    start_assembly(nullptr, 0);
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