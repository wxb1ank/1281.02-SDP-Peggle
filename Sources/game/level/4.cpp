#define _USE_MATH_DEFINES

#include <game.hpp>

#include <cmath>

namespace game {

Level Level::four() {
    Level level{};

    int radius = 5;
    int initialXPosition = 160;
    int initialYPosition = 100;
    level.pegRadius = radius;
    float circleRadius = 50.;

    for(float i = 0.; i < 2 * M_PI; i += M_PI / 12)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + circleRadius * cosf(i), static_cast<float>(initialYPosition) + circleRadius * sinf(i));

    }

    initialXPosition = 160 - 2 * circleRadius;
    for(float i = 0.; i < 2 * M_PI; i += M_PI / 12)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + circleRadius * cosf(i), static_cast<float>(initialYPosition) + circleRadius * sinf(i));

    }

    initialXPosition = 160 + 2 * circleRadius;
    for(float i = 0.; i < 2 * M_PI; i += M_PI / 12)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + circleRadius * cosf(i), static_cast<float>(initialYPosition) + circleRadius * sinf(i));

    }

    initialXPosition = 160 - circleRadius;
    initialYPosition = 100 + circleRadius;
    for(float i = 0.; i < 2 * M_PI; i += M_PI / 12)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + circleRadius * cosf(i), static_cast<float>(initialYPosition) + circleRadius * sinf(i));

    }

    initialXPosition = 160 + circleRadius;
    initialYPosition = 100 + circleRadius;
    for(float i = 0.; i < 2 * M_PI; i += M_PI / 12)
    {
        level.pegPositions.emplace_back(static_cast<float>(initialXPosition) + circleRadius * cosf(i), static_cast<float>(initialYPosition) + circleRadius * sinf(i));

    }

    return level;
}

} // namespace game
