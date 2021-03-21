#pragma once


namespace Kenshi 
{


    struct GameWorld;
    struct PlayerInterface;
    struct Character;
    struct Building;


    GameWorld& GetGameWorld();
    // GameWorld looks to be an object of all game state, whether its loaded or not.
    // Has things like a list of loaded mods and all the GameData loaded in, probably saves too.

}