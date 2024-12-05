#include "Mobs/Squirrel.hpp"
#include "Mobs/Visitors/BattleVisitor.hpp"
#include "Battlefield/Battlefield.hpp"

void Squirrel::accept(BattleVisitor &battleVisitor, const NPC &attacker)
{
    battleVisitor.visit(attacker, *this);
}

void Squirrel::move(Battlefield *battlefield)
{
    int x = this->getPosition().x;
    int y = this->getPosition().y;

    int fieldSize = battlefield->getFieldSize();

    std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    std::vector<std::pair<int, int>> validDirections;

    for (const auto &[dx, dy] : directions)
    {
        int newX = x + dx;
        int newY = y + dy;

        if (newX >= 0 && newX < fieldSize &&
            newY >= 0 && newY < fieldSize &&
            battlefield->getNPC(newX, newY) == nullptr)
        {
            validDirections.emplace_back(newX, newY);
        }
    }

    if (!validDirections.empty())
    {
        std::pair<int, int> chosenDirection = validDirections[rand() % validDirections.size()];
        int newX = chosenDirection.first;
        int newY = chosenDirection.second;

        battlefield->removeNPC(x, y);
        battlefield->placeNPC(std::shared_ptr<Squirrel>(this), newX, newY);
    }
}