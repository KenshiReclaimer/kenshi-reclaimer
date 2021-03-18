set_arch("x64")
set_languages("cxx20")
add_rules("mode.debug", "mode.release")
-- bunch of ogre defines that are made because im too lazy to run cmake on it

add_requires("sol2")

target("OgreMain")
    set_kind("static")
    set_group("third-party")
    add_linkdirs("src/ogre/lib")
    add_links("OgreMain_x64")
    add_headerfiles("src/ogre/include/**.h")
    
    add_includedirs("src/ogre/include", {public=true})
target_end()

target("MyGUIMain")
    set_kind("static")
    set_group("third-party")
    add_headerfiles("src/mygui/include/**.h")
    add_includedirs("src/mygui/include", {public=true})
target_end()

target("Plugin_Reclaimer")
    set_kind("shared")
    add_files("src/**.cpp")
    add_deps("OgreMain", "MyGUIMain")
    add_packages("sol2")

    
    add_linkdirs("src/ogre/lib")
    add_linkdirs("src/mygui/lib")

    add_links("OgreMain_x64")
    add_links("MyGUIEngine_x64")
    
    set_pcxxheader("src/core/include/stdafx.h")

    add_includedirs("src/core/include")
    add_includedirs("src/kenshi/include")
    
    after_build(function (target)
        in_dir = target:targetfile()
        out_dir = os.getenv('KenshiGamePath') .. '\\' .. target:name() .. '.dll'
        print('copying file:')
        print('\tin_dir = ' .. in_dir)
        print('\tout_dir = ' .. out_dir)
        os.cp(in_dir, out_dir)
    end)
target_end()