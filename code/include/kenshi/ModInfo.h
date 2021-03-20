#pragma once

#include <stdafx.h>
#include <lektor.h>

struct ModInfo
{
    std::string modName; // 0x00
    std::string filePath; // 0x28 // full path with filename
    std::string fileDir; // 0x50 // full path without filename
    long idk; // is 256
    std::string assetPath; // 0x80 // path within the mod file? looks like an "extraction path" for the game to use
    std::string displayName; // 0xA8
    std::string author; // 0xD0
    std::string description; // 0x100
    lektor<std::string> unk1, unk2;
};