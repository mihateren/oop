#pragma once

#include <memory>
#include <stdexcept>
#include "NPC.hpp"
#include "Mobs/Orc.hpp"
#include "Mobs/Squirrel.hpp"
#include "Mobs/Druid.hpp"

enum class NPCType
{
    Orc,
    Squirrel,
    Druid
};

class NPCFabric
{
public:
    std::unique_ptr<NPC> createNPC(NPCType type) const
    {
        switch (type)
        {
        case NPCType::Orc:
            return std::make_unique<Orc>();
        case NPCType::Squirrel:
            return std::make_unique<Squirrel>();
        case NPCType::Druid:
            return std::make_unique<Druid>();
        default:
            throw std::invalid_argument("Unknown NPC type");
        }
    }
};