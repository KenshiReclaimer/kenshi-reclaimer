#pragma once

namespace Kenshi
{
    struct GameDataContainer
    {
        virtual ~GameDataContainer();
    };

    struct GameDataManager : public GameDataContainer // 0x180 bytes total
    {

    };
}
