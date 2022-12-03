#include <game.hpp>

namespace game {

Level Level::three()  {
    Level level{};

    int radius = 5;
    int initialXPosition = 20;
    int initialYPosition = 80;
    level.pegRadius = radius;
    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 3; c++)
        {
            level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + radius * 4 * c , static_cast<float>(initialYPosition) + radius * 4 * r);
        }
    }

    initialXPosition = 100;
    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 3; c++)
        {
            level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + radius * 4 * c , static_cast<float>(initialYPosition) + radius * 4 * r);
        }
    }

    initialXPosition = 180;
    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 3; c++)
        {
            level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + radius * 4 * c , static_cast<float>(initialYPosition) + radius * 4 * r);
        }
    }

    initialXPosition = 260;
    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 3; c++)
        {
            level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + radius * 4 * c , static_cast<float>(initialYPosition) + radius * 4 * r);
        }
    }




    return level;
}

} // namespace game
