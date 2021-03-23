#pragma once

#include <stdafx.h>

namespace Kenshi
{
    struct PlayerInterface
    {
        // FactoryCallbackInterface
        virtual ~PlayerInterface();


        std::string playerFactionName;

    };
}
