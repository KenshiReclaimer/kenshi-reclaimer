#pragma once

#include "util/lektor.h"

#include "GameDataManager.h"

struct Renderer;
struct PhysicsActual;
struct ModInfo;

struct GameWorld
{
    virtual ~GameWorld();

    float unk1, unk2;
    Renderer* renderingEngine;
    PhysicsActual* physicsEngine;
    GameDataManager manager1;
    GameDataManager manager2;
    GameDataManager manager3;
};