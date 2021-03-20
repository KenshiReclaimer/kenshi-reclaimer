set_arch("x64")
set_languages("cxx20")
add_rules("mode.debug", "mode.release")
-- bunch of ogre defines that are made because im too lazy to run cmake on it

add_requires("sol2", "boost")

target("Plugin_Reclaimer")
    set_kind("shared")
    add_files("code/src/**.cpp")
    add_packages("sol2", "boost")

    
    add_linkdirs("code/lib")

    add_links("ogre/OgreMain_x64")
    add_links("mygui/MyGUIEngine_x64")
    
    set_pcxxheader("code/include/stdafx.h")

    add_includedirs("code/include")

    after_build(function (target)
        in_dir = target:targetfile()
        out_dir = os.getenv('KenshiGamePath') .. '\\' .. target:name() .. '.dll'
        print('copying file:')
        print('\tin_dir = ' .. in_dir)
        print('\tout_dir = ' .. out_dir)
        os.cp(in_dir, out_dir)
    end)
target_end()