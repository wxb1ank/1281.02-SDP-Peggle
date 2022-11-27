// This is necessary for the `M_PI` family of macros.
#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <optional>

#include "FEHLCD.h"

#include "mechanics.hpp"

Vector::Vector() : x{0.f}, y{0.f} {}

Vector::Vector(const float x, const float y) : x{x}, y{y} {}

float Vector::getMagnitude() const {
    return std::abs(std::hypotf(this->x, this->y));
}

std::optional<Position> Position::currentTouch() {
    Position touch;
    if (LCD.Touch(&touch.x, &touch.y)) {
        return {touch};
    } else {
        return {};
    }
}

Position::Position(const std::size_t x, const std::size_t y)
:   Vector{static_cast<float>(x), static_cast<float>(y)}
{}

Position Position::nextTouch() {
    Position touch;
    while (!LCD.Touch(&touch.x, &touch.y));

    return touch;
}

float Position::angleTo(const Position other) const {
    const auto dx = other.x - this->x;
    const auto dy = other.y - this->y;

    const auto angle = M_PI_2 - std::atan2(dx, dy);
    printf("%f deg\n", angle * (180. / M_PI));

    return angle;
}

const Acceleration Acceleration::GRAVITY{0.f, -200'000.f};
