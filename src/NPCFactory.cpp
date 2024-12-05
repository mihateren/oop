#include "NPCFactory.hpp"

std::shared_ptr<NPC> NPCFactory::createNPC(NPCType type) const
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

std::shared_ptr<NPC> NPCFactory::createNPC(NPCType type, int x, int y) const
{
    switch (type)
    {
    case NPCType::Orc:
        return std::make_shared<Orc>(100, 20, 10, 40, x, y);
    case NPCType::Squirrel:
        return std::make_shared<Squirrel>(100, 15, 5, 20, x, y);
    case NPCType::Druid:
        return std::make_shared<Druid>(100, 10, 15, 30, x, y);
    default:
        return nullptr;
    }
}

std::vector<std::shared_ptr<NPC>> NPCFactory::createNPCFromFile(const std::string &filename) const
{
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Не удалось открыть файл");
        }

        std::vector<std::shared_ptr<NPC>> npcs;

        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string typeStr;
            int x, y;

            ss >> typeStr >> x >> y;

            NPCType type = stringToNPCType(typeStr);

            if (x < 0 || x > 100 || y < 0 || y > 100)
            {
                throw std::out_of_range("Координаты должны быть в пределах от 0 до 100");
            }

            npcs.push_back(createNPC(type, x, y));
        }

        return npcs;
    }
}

NPCType NPCFactory::stringToNPCType(const std::string &typeStr) const
{
    if (typeStr == "Orc")
        return NPCType::Orc;
    else if (typeStr == "Squirrel")
        return NPCType::Squirrel;
    else if (typeStr == "Druid")
        return NPCType::Druid;
    else
        throw std::invalid_argument("Неизвестный тип NPC: " + typeStr);
}