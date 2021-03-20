#pragma once

#include <stdafx.h>
namespace Kenshi
{
    struct GameData;
    struct Character;

    struct MedicalSystem
    /*
        Houses health, bodypart, armor, etc data. Anything that hurts or heals is tracked here.
        In Character class (might be CharacterHuman).
    */
    {
        struct HealthPartStatus // total 0x88 bytes
        /*
            A limb, blood, oil, hunger arent here, just head/arms/legs/other appendages.
        */
        {
            GameData* data;
            uint64_t type; // ? unsure, different for different limbs, but not unique
            MedicalSystem* medical;
            Character* character;
            uint64_t unknown[3]; // theres some boolean flags in the last int in this group
            float unknown1; // currently 80, some hidden stat for limb health?
            float unknown2; // currently 1, some regeneration stat?
            float health; // the current health of the limb.
            float unknown3;
        };
    };
}
