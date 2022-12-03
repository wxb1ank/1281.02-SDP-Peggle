#include <menu.hpp>

namespace menu {

Level Level::two() {
    Level level{};
    int radius = 5;
    int initialXPositionBig = 160;
    int initialYPositionBig = 80;
    level.pegRadius = radius;
    int numPegsRow = -1;
    for(int r = 0; r < 7; r++)
    {
        numPegsRow += 2;
        for(int i = 0; i < numPegsRow; i++)
        {
            level.pegPositions.emplace_back(static_cast<float>(initialXPositionBig) - 4 * r * radius + 4 * i * radius, static_cast<float>(initialYPositionBig) + 4 * r * radius);

        }
    }

    numPegsRow = 9;
    int initialXPositionLeft = 0;
    int initialYPositionLeft = 60;
    for(int r = 0; r < 4; r++)
    {
        numPegsRow -= 2;
        for(int i = numPegsRow; i > 0; i--)
        {
            level.pegPositions.emplace_back(static_cast<float>(initialXPositionLeft) + 4 * r * radius + 4 * i * radius, static_cast<float>(initialYPositionLeft) + 4 * r * radius);
        }
    }

    numPegsRow = 9;
    int initialXPositionRight = 160;
    int initialYPositionRight = 60;
    for(int r = 0; r < 4; r++)
    {
        numPegsRow -= 2;
        for(int i = numPegsRow; i > 0; i--)
        {
            level.pegPositions.emplace_back(static_cast<float>(initialXPositionRight) + 4 * r * radius + 4 * i * radius, static_cast<float>(initialYPositionRight) + 4 * r * radius);
        }
    }




    return level;
};

} // namespace menu
