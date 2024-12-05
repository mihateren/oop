#include "Logger/FileListener.hpp"

FileListener::FileListener()
{
    logFile.open("log.txt", std::ios::app);
}

FileListener::~FileListener()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

void FileListener::onDamageReceived(const NPC &defender, int damage, const NPC &attacker)
{
    logFile << defender.getType() << " получает " << damage << " урона от " << attacker.getType() << ". ХП: " << defender.getHP() << std::endl;
}

void FileListener::onDead(const NPC &npc)
{
    logFile << npc.getType() << " умер." << std::endl;
}

void FileListener::onGameStart(Battlefield &battlefield)
{
    auto &field = battlefield.getField();

    for (int i = 0; i < battlefield.getFieldSize(); ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            if (field[i][j] != nullptr)
            {
                logFile << field[i][j]->getType();
                logFile << field[i][j]->getPosition();
                logFile << std::endl;
            }
        }
    }

    logFile << "Бой начался!" << std::endl;
}

void FileListener::onTurnStart(int turn)
{
    logFile << "Ход " << turn << std::endl;
}

void FileListener::onGameEnd()
{
    logFile << "Бой завершён!" << std::endl;
    logFile << "=============================" << std::endl;
}