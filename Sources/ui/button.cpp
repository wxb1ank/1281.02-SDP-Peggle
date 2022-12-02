#include <ui.hpp>

#include <FEHLCD.hpp>

namespace ui {

Button::Button(const Label label, const Color borderColor)
:   Button{label, borderColor, Size(Button::pad(label.getWidth()), Button::pad(label.getHeight()))}
{}

Button::Button(const Label label, const Color borderColor, const Size size)
:   label{label}, borderColor{borderColor}, size{size}
{}

Button::~Button() {}

Label &Button::getLabel() {
    return this->label;
}

const Label &Button::getLabel() const {
    return this->label;
}

Color &Button::getBorderColor() {
    return this->borderColor;
}

const Color &Button::getBorderColor() const {
    return this->borderColor;
}

Size Button::getSize() const {
    return this->size;
}

float Button::getWidth() const {
    return this->size.width;
}

float Button::getHeight() const {
    return this->size.height;
}

Position Button::getCenter() const {
    return this->label.getCenter();
}

bool Button::isPressed() const {
    const auto touch = Position::getCurrentTouch();
    if (touch.has_value()) {
        return this->contains(*touch);
    } else {
        return false;
    }
}

void Button::draw() const {
    if (this->isPressed()) {
        this->drawPressed();
    } else {
        this->drawUnpressed();
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

float Button::pad(const float dim) const {
    return dim + (2.f * Button::DEFAULT_PADDING);
}

void Button::drawBorder() const {
    const auto topLeft = this->getTopLeft();

    LCD.SetFontColor(this->borderColor.encode());
    LCD.DrawRectangle(
        static_cast<int>(topLeft.x),
        static_cast<int>(topLeft.y),
        static_cast<int>(this->size.width),
        static_cast<int>(this->size.height)
    );
}

void Button::fillBorder() const {
    const auto topLeft = this->getTopLeft();

    LCD.SetFontColor(this->borderColor.encode());
    LCD.FillRectangle(
        static_cast<int>(topLeft.x),
        static_cast<int>(topLeft.y),
        static_cast<int>(this->size.width),
        static_cast<int>(this->size.height)
    );
}

} // namespace ui
