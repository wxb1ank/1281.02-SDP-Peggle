#include <FEHLCD.h>

#include "font.hpp"

#include "ui.hpp"

namespace ui {

Size::Size(const float width, const float height) : width{width}, height{height} {}

float half(const float f) {
    return f / 2.f;
}

float View::getLeftX() const {
    return this->getCenter().x - half(this->getWidth());
}

float View::getRightX() const {
    return this->getCenter().x + half(this->getWidth());
}

float View::getTopY() const {
    return this->getCenter().y - half(this->getHeight());
}

float View::getBottomY() const {
    return this->getCenter().y + half(this->getHeight());
}

Position View::getTopLeft() const {
    return { this->getLeftX(), this->getTopY() };
}

Position View::getTopRight() const {
    return { this->getRightX(), this->getTopY() };
}

Position View::getBottomLeft() const {
    return { this->getLeftX(), this->getBottomY() };
}

Position View::getBottomRight() const {
    return { this->getRightX(), this->getBottomY() };
}

Label::Label(const Position center, const std::string content)
    : center{center},
      content{content}
{}

float Label::getWidth() const {
    return static_cast<float>(Font::WIDTH * this->content.length());
}

float Label::getHeight() const {
    return static_cast<float>(Font::HEIGHT);
}

void Label::draw() const {
    LCD.WriteAt(
        this->content.c_str(),
        static_cast<int>(this->getLeftX()),
        static_cast<int>(this->getTopY())
    );
}

Button::Button(const Label label)
    : label{label},
      size{
        label.getWidth() + Button::DEFAULT_PADDING,
        label.getHeight() + Button::DEFAULT_PADDING
      }
{}

Button::Button(const Label label, const Size size)
    : label{label},
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

void Button::drawUnpressed() const {
    this->drawBorder();
    this->label.draw();
}

void Button::drawPressed() const {
    this->fillBorder();
    this->label.draw();
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

} // namespace ui
