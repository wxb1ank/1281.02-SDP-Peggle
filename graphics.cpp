#include <FEHLCD.h>

#include "font.hpp"

#include "graphics.hpp"

namespace gfx {

Button::Button(const std::string label, const Position center)
    : label{label},
      center{center},
      size{
        static_cast<float>(Font::widthOf(label)) + Button::DEFAULT_PADDING,
        static_cast<float>(Font::HEIGHT) + Button::DEFAULT_PADDING
      }
{}

Button::Button(const std::string label, const Position center, const Size size)
    : label{label},
      center{center},
      size{size}
{}

bool Button::isPressed() const {
    const auto touch = Position::currentTouch();
    if (touch.has_value()) {
        return this->isPressed(*touch);
    } else {
        return false;
    }
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

void Button::drawUnpressed() const {
    this->drawBorder();
    this->drawLabel();
}

void Button::drawPressed() const {
    this->fillBorder();
    this->drawLabel();
}

void Button::drawBorder() const {
    const auto topLeft = this->getTopLeft();
    LCD.DrawRectangle(
        static_cast<int>(topLeft.x),
        static_cast<int>(topLeft.y),
        static_cast<int>(this->size.width),
        static_cast<int>(this->size.height)
    );
}

void Button::fillBorder() const {
    const auto topLeft = this->getTopLeft();
    LCD.FillRectangle(
        static_cast<int>(topLeft.x),
        static_cast<int>(topLeft.y),
        static_cast<int>(this->size.width),
        static_cast<int>(this->size.height)
    );
}

void Button::drawLabel() const {
    LCD.WriteAt(
        this->label.c_str(),
        static_cast<int>(this->labelLeft()),
        static_cast<int>(this->labelTop())
    );
}

float Button::labelLeft() const {
    const auto labelWidth = static_cast<float>(Font::widthOf(this->label));
    const auto padding = (this->size.width - labelWidth) / 2.f;

    return this->getLeftX() + padding;
}

float Button::labelTop() const {
    const auto labelHeight = static_cast<float>(Font::HEIGHT);
    const auto padding = (this->size.height - labelHeight) / 2.f;

    return this->getTopY() + padding;
}

} // namespace gfx
