#include <game.hpp>

namespace game {

Level Level::one() {
    Level level{};

    int radius = 5;
    int initialXPosition = 50;
    int initialYPosition = 80;
    level.pegRadius = radius;
    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 12; c++)
        {
            if(r%2 == 0)
            {
                level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + 4 * radius * static_cast<float>(c), static_cast<float>(initialYPosition) + 4 * radius * static_cast<float>(r));
            }
            else
            {
                level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + 4 * radius * static_cast<float>(c) - radius, static_cast<float>(initialYPosition) + 4 * radius * static_cast<float>(r));
            }
        }
    }
    return level;
}

} // namespace game
