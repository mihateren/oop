#pragma once

#include <memory>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
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
    std::shared_ptr<NPC> createNPC(NPCType type) const;

    std::shared_ptr<NPC> createNPC(NPCType type, int x, int y) const;

    std::vector<std::shared_ptr<NPC>> createNPCFromFile(const std::string &filename) const;

private:
    NPCType stringToNPCType(const std::string &typeStr) const;
};
