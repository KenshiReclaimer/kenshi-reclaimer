add_rules("mode.debug", "mode.release")


target("OgreMain")
    set_kind("static")
    add_links("$(builddir)/src/third-party/ogre/lib/OgreMain_x64.lib")
    add_includedirs("$(builddir)/src/third-party/ogre/include", {public=true})
    add_headerfiles("$(builddir)/src/third-party/ogre/include/**.h")
target_end()

target("Plugin_Reclaimer")
    set_kind("shared")
    add_files("src/**.cpp")
    add_deps("OgreMain")
target_end()