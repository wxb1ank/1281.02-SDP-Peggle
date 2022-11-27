#include <FEHLCD.h>

#include "font.hpp"

#include "ui.hpp"

namespace ui {

Size::Size(const float width, const float height) : width{width}, height{height} {}

/// \brief Halves the given number.
///
/// \param[in]  f   A number.
/// \return `f` divided by two.
/// \author Will Blankemeyer
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

bool View::contains(const Position pos) const {
    if (pos.x < this->getLeftX()) {
        return false;
    }
    if (pos.x > this->getRightX()) {
        return false;
    }

    if (pos.y < this->getTopY()) {
        return false;
    }
    if (pos.y > this->getBottomY()) {
        return false;
    }

    return true;
}

Label::Label(const Position center, const std::string content, const Color color)
:   center{center},
    content{content},
    color{color}
{}

float Label::getWidth() const {
    return static_cast<float>(Font::WIDTH * this->content.length());
}

float Label::getHeight() const {
    return static_cast<float>(Font::HEIGHT);
}

void Label::draw() const {
    LCD.SetFontColor(this->color);
    LCD.WriteAt(
        this->content.c_str(),
        static_cast<int>(this->getLeftX()),
        static_cast<int>(this->getTopY())
    );
}

Button::Button(const Label label, const Color color)
:   Button{
        label,
        {
            label.getWidth() + Button::DEFAULT_PADDING,
            label.getHeight() + Button::DEFAULT_PADDING
        },
        color,
    }
{}

Button::Button(const Label label, const Size size, const Color color)
:   label{label},
    size{size},
    color{color}
{}

bool Button::isPressed() const {
    const auto touch = Position::currentTouch();
    if (touch.has_value()) {
        return this->contains(*touch);
    } else {
        return false;
    }
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

    LCD.SetFontColor(this->color);
    LCD.DrawRectangle(
        static_cast<int>(topLeft.x),
        static_cast<int>(topLeft.y),
        static_cast<int>(this->size.width),
        static_cast<int>(this->size.height)
    );
}

void Button::fillBorder() const {
    const auto topLeft = this->getTopLeft();

    LCD.SetFontColor(this->color);
    LCD.FillRectangle(
        static_cast<int>(topLeft.x),
        static_cast<int>(topLeft.y),
        static_cast<int>(this->size.width),
        static_cast<int>(this->size.height)
    );
}

} // namespace ui
