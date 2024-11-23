#pragma once

#include <memory>
#include <stdexcept>
#include "Mobs/NPC.hpp"
#include "Mobs/Orc.hpp"
#include "Mobs/Squirrel.hpp"
#include "Mobs/Druid.hpp"

enum class NPCType
{
    Orc,
    Squirrel,
    Druid
};

class NPCFactory
{
public:
    std::shared_ptr<NPC> createNPC(NPCType type) const
    {
        switch (type)
        {
        case NPCType::Orc:
            return std::make_shared<Orc>();
        case NPCType::Squirrel:
            return std::make_shared<Squirrel>();
        case NPCType::Druid:
            return std::make_shared<Druid>();
        default:
            return nullptr;
        }
    }

    std::shared_ptr<NPC> createNPC(NPCType type, int x, int y) const
    {
        switch (type)
        {
        case NPCType::Orc:
            return std::make_shared<Orc>(100, 5, 40, x, y);
        case NPCType::Squirrel:
            return std::make_shared<Squirrel>(10, 1, 0, x, y);
        case NPCType::Druid:
            return std::make_shared<Druid>(80, 10, 30, x, y);
        default:
            return nullptr;
        }
    }
};