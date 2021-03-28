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
#include <cassert>

struct ReclaimerNETHost
{
    HMODULE hHostLib;

    // init core
    hostfxr_initialize_for_runtime_config_fn init_fn;
    hostfxr_initialize_for_dotnet_command_line_fn init_cmdln_fn;
    hostfxr_get_runtime_delegate_fn get_delegate_fn;
    hostfxr_get_runtime_properties_fn get_runtime_properties_fn;
    hostfxr_get_runtime_property_value_fn get_runtime_property_value_fn;
    hostfxr_set_runtime_property_value_fn set_runtime_property_value_fn;
    hostfxr_set_error_writer_fn set_error_writer_fn;
    hostfxr_close_fn close_fn;

    // load/run delegates
    load_assembly_and_get_function_pointer_fn load_assembly_and_get_fn_ptr;
    get_function_pointer_fn get_fn_ptr;

    hostfxr_handle cxt = nullptr;

    std::wstring trusted_platform;

    static void ErrorWriter(const char_t* msg)
    {
        wprintf(L"[DOTNET ERROR] %s\n", msg);
    }


    void PrepareHost()
    {

        char_t host_path[MAX_PATH];
        size_t buffer_size = sizeof(host_path) / sizeof(char_t);
        int rc = get_hostfxr_path(host_path, &buffer_size, nullptr);
        if (rc != 0)
            throw new std::runtime_error("hostfxr not found on machine");

        hHostLib = LoadLibraryW(host_path);

        init_fn = (decltype(init_fn))GetProcAddress(hHostLib, "hostfxr_initialize_for_runtime_config");
        init_cmdln_fn = (decltype(init_cmdln_fn))GetProcAddress(hHostLib, "hostfxr_initialize_for_dotnet_command_line");
        get_delegate_fn = (decltype(get_delegate_fn))GetProcAddress(hHostLib, "hostfxr_get_runtime_delegate");


        get_runtime_properties_fn = (decltype(get_runtime_properties_fn))GetProcAddress(hHostLib, "hostfxr_get_runtime_properties");
        get_runtime_property_value_fn = (decltype(get_runtime_property_value_fn))GetProcAddress(hHostLib, "hostfxr_get_runtime_property_value");
        set_runtime_property_value_fn = (decltype(set_runtime_property_value_fn))GetProcAddress(hHostLib, "hostfxr_set_runtime_property_value");

        set_error_writer_fn = (decltype(set_error_writer_fn))GetProcAddress(hHostLib, "hostfxr_set_error_writer");

        close_fn = (decltype(close_fn))GetProcAddress(hHostLib, "hostfxr_close");

        set_error_writer_fn(ErrorWriter);
    }

    void LoadRuntime()
    {
        int rc;

        rc = init_fn(L"Reclaimer.runtimeconfig.json", nullptr, &cxt);
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

    }

    void PrintRuntime()
    {
        const char_t* keys[0x100];
        const char_t* values[0x100];
        size_t count = 0x100;

        get_runtime_properties_fn(
            cxt,
            &count,
            (const char_t**)keys,
            (const char_t**)values
        );

        std::cout << " ====== .NET Runtime Properties ======= " << std::endl;
        for (size_t i = 0; i < count; i++) {
            std::wcout << std::wstring(keys[i]) << ": \t" << std::wstring(values[i]) << std::endl;
        }
    }

    template <typename T>
    T LoadAssembly(const std::wstring& path, const std::wstring& type, const std::wstring& method, const std::wstring& dlgate = std::wstring())
    {
        T fn = nullptr;
        int rc = load_assembly_and_get_fn_ptr(
            path.c_str(),
            type.c_str(),
            method.c_str(),
            dlgate.empty() ? nullptr: dlgate.c_str(),
            nullptr,
            (void**)&fn
        );
        assert(rc == 0 && "LoadAssembly: Cant load assembly");
        return fn;
    }

    template<typename T>
    T GetMethod(const std::wstring& type, const std::wstring& method, const std::wstring& dlgate = std::wstring())
    {
        T fn = nullptr;
        int rc = get_fn_ptr(type.c_str(), method.c_str(), dlgate.empty() ? nullptr : dlgate.c_str(), nullptr, nullptr, (void**)&fn);
        assert(rc == 0 && "GetMethod: Cant load ");
        return fn;
    }


    void CloseHostResolver()
    {
        close_fn(cxt);
    }

};


using ReclaimerEntryFn = void();


void ReclaimerMain::install()
{
    printf("ReclaimerMain::install()\n");

    auto& game = Kenshi::GetGameWorld();

    printf("[DEBUG] gameWorld = %p\n", &game);


    printf("Loading .NET 5 Runtime...\n");

    dotnet = new ReclaimerNETHost;
    dotnet->PrepareHost();
    dotnet->LoadRuntime();
    dotnet->CloseHostResolver();

    printf("Load Reclaimer.Core.dll.. \n");
    auto install_assembly = dotnet->LoadAssembly<ReclaimerEntryFn*>(
        L"Reclaimer.Core.dll",
        L"Reclaimer.Core.ReclaimerEntry, Reclaimer.Core",
        L"Install",
        L"Reclaimer.Core.ReclaimerEntryFn, Reclaimer.Core"
        );

    install_assembly();
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
    auto init_assembly = dotnet->LoadAssembly<ReclaimerEntryFn*>(
        L"Reclaimer.Core.dll",
        L"Reclaimer.Core.ReclaimerEntry, Reclaimer.Core",
        L"Initialize",
        L"Reclaimer.Core.ReclaimerEntryFn, Reclaimer.Core"
        );
    init_assembly();
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
    auto shutdown_assembly = dotnet->LoadAssembly<ReclaimerEntryFn*>(
        L"Reclaimer.Core.dll",
        L"Reclaimer.Core.ReclaimerEntry, Reclaimer.Core",
        L"Shutdown",
        L"Reclaimer.Core.ReclaimerEntryFn, Reclaimer.Core"
        );
    shutdown_assembly();
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
    auto uninstall_assembly = dotnet->LoadAssembly<ReclaimerEntryFn*>(
        L"Reclaimer.Core.dll",
        L"Reclaimer.Core.ReclaimerEntry, Reclaimer.Core",
        L"Uninstall",
        L"Reclaimer.Core.ReclaimerEntryFn, Reclaimer.Core"
        );
    uninstall_assembly();
}