#include "../../include/Logger/ConsoleListener.hpp"

void ConsoleListener::onDamageReceived(const NPC &defender, int damage, const NPC &attacker)
{
    std::cout << defender.getType() << " получает " << damage << " урона от " << attacker.getType() << ". ХП: " << defender.getHP() << std::endl;
}

void ConsoleListener::onDead(const NPC &npc)
{
    std::cout << npc.getType() << " умер." << std::endl;
}

void ConsoleListener::onGameStart(Battlefield &battlefield)
{
    auto &field = battlefield.getField();

    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            if (field[i][j] != nullptr)
            {
                std::cout << field[i][j]->getType();
                field[i][j]->getPosition().print();
                std::cout << std::endl;
            }
        }
    }

    std::cout << "Бой начался!" << std::endl;
}

void ConsoleListener::onTurnStart(int turn)
{
    std::cout << "Ход " << turn << std::endl;
}

void ConsoleListener::onGameEnd()
{
    std::cout << "Бой завершён!" << std::endl;
}