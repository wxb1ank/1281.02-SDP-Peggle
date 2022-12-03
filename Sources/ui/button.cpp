#include <ui.hpp>

#include <FEHLCD.hpp>

#include <functional>

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

float Button::pad(const float dim) {
    return dim + (2.f * Button::DEFAULT_PADDING);
}

static void drawVerticalBorderLine(const float x, const float top, const float bottom) {
    LCD.DrawVerticalLine(
        static_cast<int>(x),
        static_cast<int>(top + Button::BORDER_RADIUS),
        static_cast<int>(bottom - Button::BORDER_RADIUS)
    );
}

static void drawVerticalBorderLines(
    const float left,
    const float right,
    const float top,
    const float bottom
) {
    drawVerticalBorderLine(left, top, bottom);
    drawVerticalBorderLine(right, top, bottom);
}

static void drawHorizontalBorderLine(const float y, const float left, const float right) {
    LCD.DrawHorizontalLine(
        static_cast<int>(y),
        static_cast<int>(left + Button::BORDER_RADIUS),
        static_cast<int>(right - Button::BORDER_RADIUS)
    );
}

static void drawHorizontalBorderLines(
    const float left,
    const float right,
    const float top,
    const float bottom
) {
    drawHorizontalBorderLine(top, left, right);
    drawHorizontalBorderLine(bottom, left, right);
}

static void drawBorderLines(
    const float left,
    const float right,
    const float top,
    const float bottom
) {
    drawVerticalBorderLines(left, right, top, bottom);
    drawHorizontalBorderLines(left, right, top, bottom);
}

static void drawBorderCircle(
    const std::function<void(int, int, int)> &draw,
    const float x,
    const float y
) {
    draw(
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(Button::BORDER_RADIUS)
    );
}

static void drawTopLeftBorderCircle(
    const std::function<void(int, int, int)> &draw,
    const float left,
    const float top
) {
    drawBorderCircle(draw, (left + Button::BORDER_RADIUS), (top + Button::BORDER_RADIUS));
}

static void drawTopRightBorderCircle(
    const std::function<void(int, int, int)> &draw,
    const float right,
    const float top
) {
    drawBorderCircle(draw, (right - Button::BORDER_RADIUS), (top + Button::BORDER_RADIUS));
}

static void drawBottomLeftBorderCircle(
    const std::function<void(int, int, int)> &draw,
    const float left,
    const float bottom
) {
    drawBorderCircle(draw, (left + Button::BORDER_RADIUS), (bottom - Button::BORDER_RADIUS));
}

static void drawBottomRightBorderCircle(
    const std::function<void(int, int, int)> &draw,
    const float right,
    const float bottom
) {
    drawBorderCircle(draw, (right - Button::BORDER_RADIUS), (bottom - Button::BORDER_RADIUS));
}

static void drawBorderCircles(
    const std::function<void(int, int, int)> draw,
    const float left,
    const float right,
    const float top,
    const float bottom
) {
    drawTopLeftBorderCircle(draw, left, top);
    drawTopRightBorderCircle(draw, right, top);
    drawBottomLeftBorderCircle(draw, left, bottom);
    drawBottomRightBorderCircle(draw, right, bottom);
}

static void drawRectangle(const Position center, const Size size) {
    LCD.FillRectangle(
        static_cast<int>(center.x),
        static_cast<int>(center.y),
        static_cast<int>(size.width),
        static_cast<int>(size.height)
    );
}

static float getStraightDim(const float dim) {
    return dim - (2.f * Button::BORDER_RADIUS);
}

static void fixBorderCircles(
    const Color color,
    const float left,
    const float right,
    const float top,
    const float bottom
) {
    LCD.SetFontColor(color.encode());

    const auto width = right - left;
    const auto height = bottom - top;

    drawRectangle(
        Position(left + 1.f, top + Button::BORDER_RADIUS),
        Size(width - 1.f, getStraightDim(height))
    );
    drawRectangle(
        Position(left + Button::BORDER_RADIUS, top + 1.f),
        Size(getStraightDim(width), height - 1.f)
    );
}

void Button::drawBorder() const {
    using namespace std::placeholders;

    const auto left = this->getLeftX();
    const auto right = this->getRightX();
    const auto top = this->getTopY();
    const auto bottom = this->getBottomY();

    LCD.SetFontColor(this->borderColor.encode());
    drawBorderLines(left, right, top, bottom);
    LCD.SetFontColor(Color::BLACK.encode());
    drawBorderCircles(std::bind(&FEHLCD::FillCircle, &LCD, _1, _2, _3), left, right, top, bottom);
    LCD.SetFontColor(this->borderColor.encode());
    drawBorderCircles(std::bind(&FEHLCD::DrawCircle, &LCD, _1, _2, _3), left, right, top, bottom);
    fixBorderCircles(Color::BLACK, left, right, top, bottom);
}

void Button::fillBorder() const {
    using namespace std::placeholders;

    const auto left = this->getLeftX();
    const auto right = this->getRightX();
    const auto top = this->getTopY();
    const auto bottom = this->getBottomY();

    LCD.SetFontColor(this->borderColor.encode());
    drawBorderLines(left, right, top, bottom);
    drawBorderCircles(std::bind(&FEHLCD::FillCircle, &LCD, _1, _2, _3), left, right, top, bottom);
    fixBorderCircles(this->borderColor, left, right, top, bottom);
}

} // namespace ui
