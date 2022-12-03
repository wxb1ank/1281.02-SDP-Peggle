#include <menu.hpp>

namespace menu {

Level Level::five()  {
    Level level{};

    int radius = 5;
    int initialXPosition = 2 * radius;
    int initialYPosition = 10 * radius;
    level.pegRadius = radius;

    for(int i = 0; i < 9; i++)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + 2 * i  * radius, static_cast<float>(initialYPosition) + 4 * i * radius);

    }

    for(int i = 0; i < 9; i++)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + 2 * i  * radius + 25, static_cast<float>(initialYPosition) + 4 * i * radius);

    }

    for(int i = 0; i < 9; i++)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + 2 * i  * radius + 180, static_cast<float>(initialYPosition) + 4 * i * radius);

    }

    for(int i = 0; i < 9; i++)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + 2 * i  * radius + 205, static_cast<float>(initialYPosition) + 4 * i * radius);

    }

    for( int i = 0; i < 16; i++)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + 4 * i  * radius, static_cast<float>(initialYPosition) + 25);
    }

    for( int i = 0; i < 16; i++)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + 4 * i  * radius, static_cast<float>(initialYPosition) + 40);
    }

    for( int i = 0; i < 16; i++)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + 4 * i  * radius, static_cast<float>(initialYPosition) + 125);
    }

    for( int i = 0; i < 16; i++)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + 4 * i  * radius, static_cast<float>(initialYPosition) + 140);
    }


    return level;
}

} // namespace menu
