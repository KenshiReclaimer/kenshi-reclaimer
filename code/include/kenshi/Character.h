#pragma once
#include <stdafx.h>

#include <OgreVector3.h>

#include "Root.h"

struct GameData;
struct Faction;

struct Character : public RootObject
{
    virtual ~Character();

public:
    uint64_t id;
    Faction* faction;
    std::string name;
    GameData* gameData; // the GameData form that built this character
    Ogre::Vector3 position; // cartesian position of character in world.
};


struct CharacterHuman
{

};