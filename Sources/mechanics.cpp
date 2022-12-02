// This is necessary for the `M_PI` family of macros.
#define _USE_MATH_DEFINES

#include <mechanics.hpp>

#include <FEHLCD.hpp>

#include <cmath>

Vector::Vector() : x{0.f}, y{0.f} {}

Vector::Vector(const std::size_t x, const std::size_t y)
:   x{static_cast<float>(x)}, y{static_cast<float>(y)}
{}

Vector::Vector(const float x, const float y) : x{x}, y{y} {}

float Vector::getMagnitude() const {
    // If we imagine `this->x` and `this->y` as vectors such that `this->x` begins at the origin and
    // `this->y` begins at the end of `this->x`, then we see that a right angle is formed. From
    // this, we can construct a right triangle with side lengths of the magnitudes of `this->x` and
    // `this->y` such that the hypotenuse is the magnitude of a vector from the origin to the end of
    // `this->y`.
    return std::hypotf(std::abs(this->x), std::abs(this->y));
}

std::optional<Position> Position::getCurrentTouch() {
    Position touch{};
    // Note: this updates the LCD.
    if (LCD.Touch(&touch.x, &touch.y)) {
        return std::optional(touch);
    } else {
        return {};
    }
}

Position Position::getNextTouch() {
    Position touch{};
    // Note: this updates the LCD.
    while (!LCD.Touch(&touch.x, &touch.y));

    return touch;
}

float Position::getAngleTo(const Position pos) const {
    const auto dx = pos.x - this->x;
    const auto dy = pos.y - this->y;

    // TODO: Is this correct for any angle?
    return static_cast<float>(M_PI_2) - std::atan2(dy, dx);
}
