// This is necessary for the `M_PI` family of macros.
#define _USE_MATH_DEFINES

#include <mechanics.hpp>

#include <FEHLCD.hpp>

#include <cmath>
#include <cstdio>

Vector::Vector() : x{0.f}, y{0.f} {}

Vector::Vector(const float x, const float y) : x{x}, y{y} {}

float Vector::getMagnitude() const {
    return std::hypotf(this->x, this->y);
}

Position::Position(const std::size_t x, const std::size_t y)
:   Vector{static_cast<float>(x), static_cast<float>(y)}
{}

std::optional<Position> Position::getCurrentTouch() {
    Position touch;
    if (LCD.Touch(&touch.x, &touch.y)) {
        return std::optional(touch);
    } else {
        return {};
    }
}

Position Position::getNextTouch() {
    Position touch;
    while (!LCD.Touch(&touch.x, &touch.y));

    return touch;
}

float Position::getAngleTo(const Position pos) const {
    const auto dx = pos.x - this->x;
    const auto dy = pos.y - this->y;

    const auto angle = M_PI_2 - std::atan2(dy, dx);
    printf("%f deg\n", angle * (180. / M_PI));

    return angle;
}

const Acceleration Acceleration::GRAVITY{0.f, 1'000.f};
