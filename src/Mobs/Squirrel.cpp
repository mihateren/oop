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
    int maxMoveDistance = this->getMoveDistance();

    std::vector<Point> validPositions;

    for (int dx = -maxMoveDistance; dx <= maxMoveDistance; ++dx)
    {
        for (int dy = -maxMoveDistance; dy <= maxMoveDistance; ++dy)
        {
            if (dx == 0 && dy == 0)
                continue;

            int newX = x + dx;
            int newY = y + dy;

            if (newX >= 0 && newX < fieldSize &&
                newY >= 0 && newY < fieldSize)
            {
                std::shared_ptr<NPC> npcAtNewPos = battlefield->getNPC(newX, newY);
                if (!npcAtNewPos)
                {
                    validPositions.emplace_back(newX, newY);
                }
            }
        }
    }

    if (!validPositions.empty())
    {
        Point chosenPosition = validPositions[rand() % validPositions.size()];
        int newX = chosenPosition.x;
        int newY = chosenPosition.y;

        try
        {
            std::shared_ptr<NPC> self_shared_ptr = shared_from_this();

            {

                battlefield->removeNPC(x, y);
                battlefield->placeNPC(self_shared_ptr, newX, newY);
            }

            this->setPosition(newX, newY);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception in Squirrel::move(): " << e.what() << std::endl;
        }
    }
}
