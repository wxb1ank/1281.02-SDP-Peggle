#include <FEHLCD.h>

#include "graphics.hpp"

namespace gfx {

bool Button::isPressed() const {
    Position touch;
    if (!LCD.Touch(&touch.x, &touch.y)) {
        return false;
    }

    return this->isPressed(touch);
}

bool Button::isPressed(const Position touch) const {
    if (touch.x < this->getLeftX()) {
        return false;
    }
    if (touch.x > this->getRightX()) {
        return false;
    }

    if (touch.y < this->getTopY()) {
        return false;
    }
    if (touch.y > this->getBottomY()) {
        return false;
    }

    return true;
}

float half(const float f) {
    return f / 2.f;
}

float Button::getLeftX() const {
    return this->center.x - half(this->size.width);
}

float Button::getRightX() const {
    return this->center.x + half(this->size.width);
}

float Button::getTopY() const {
    return this->center.y - half(this->size.height);
}

float Button::getBottomY() const {
    return this->center.y + half(this->size.height);
}

Position Button::getTopLeft() const {
    return { this->getLeftX(), this->getTopY() };
}

Position Button::getTopRight() const {
    return { this->getRightX(), this->getTopY() };
}

Position Button::getBottomLeft() const {
    return { this->getLeftX(), this->getBottomY() };
}

Position Button::getBottomRight() const {
    return { this->getRightX(), this->getBottomY() };
}

void Button::draw() const {
    const auto topLeft = this->getTopLeft();
    LCD.DrawRectangle(
        static_cast<int>(topLeft.x),
        static_cast<int>(topLeft.y),
        static_cast<int>(this->size.width),
        static_cast<int>(this->size.height)
    );

    LCD.WriteAt(this->label.c_str(), static_cast<int>(topLeft.x), static_cast<int>(topLeft.y));
}

} // namespace gfx
