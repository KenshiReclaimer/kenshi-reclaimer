add_rules("mode.debug", "mode.release")

target("Reclaimer")
    set_kind("shared")
    add_files("src/*.cpp")