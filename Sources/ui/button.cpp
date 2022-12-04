#include <ui.hpp>

#include <FEHLCD.hpp>

#include <cassert>
#include <functional>

namespace ui {

Button::Button(const Label label, const Color borderColor, const Color backgroundColor)
:   Button{
        label,
        borderColor,
        backgroundColor,
        Size(Button::pad(label.getWidth()), Button::pad(label.getHeight()))
    }
{}

Button::Button(
    const Label label,
    const Color borderColor,
    const Color backgroundColor,
    const Size size
)
:   label{label}, borderColor{borderColor}, backgroundColor{backgroundColor}, size{size}
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

Color &Button::getBackgroundColor() {
    return this->backgroundColor;
}

const Color &Button::getBackgroundColor() const {
    return this->backgroundColor;
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

/// \brief Draws a vertical line at the given X coordinate and Y coordinates.
///
/// \param[in]  x       The X coordinate.
/// \param[in]  top     The top Y coordinate.
/// \param[in]  bottom  The bottom Y coordinate.
/// \author Will Blankemeyer
static void drawVerticalBorderLine(const float x, const float top, const float bottom) {
    LCD.DrawVerticalLine(
        static_cast<int>(x),
        static_cast<int>(top + Button::BORDER_RADIUS),
        static_cast<int>(bottom - Button::BORDER_RADIUS)
    );
}

/// \brief Draws two vertical lines of equal length at the given X and Y coordinates.
///
/// \param[in]  left    The X coordinate of the left line.
/// \param[in]  right   The X coordinate of the right line.
/// \param[in]  top     The top Y coordinate.
/// \param[in]  bottom  The bottom Y coordinate.
/// \author Will Blankemeyer
static void drawVerticalBorderLines(
    const float left,
    const float right,
    const float top,
    const float bottom
) {
    drawVerticalBorderLine(left, top, bottom);
    drawVerticalBorderLine(right, top, bottom);
}

/// \brief Draws a horizontal line at the given Y coordinate and X coordinates.
///
/// \param[in]  y       The Y coordinate.
/// \param[in]  left    The left X coordinate.
/// \param[in]  right   The right X coordinate.
/// \author Will Blankemeyer
static void drawHorizontalBorderLine(const float y, const float left, const float right) {
    LCD.DrawHorizontalLine(
        static_cast<int>(y),
        static_cast<int>(left + Button::BORDER_RADIUS),
        static_cast<int>(right - Button::BORDER_RADIUS)
    );
}

/// \brief Draws two horizontal lines of equal length at the given X and Y coordinates.
///
/// \param[in]  left    The left X coordinate.
/// \param[in]  right   The right X coordinate.
/// \param[in]  top     The Y coordinate of the top line.
/// \param[in]  bottom  The Y coordinate of the bottom line.
/// \author Will Blankemeyer
static void drawHorizontalBorderLines(
    const float left,
    const float right,
    const float top,
    const float bottom
) {
    drawHorizontalBorderLine(top, left, right);
    drawHorizontalBorderLine(bottom, left, right);
}

/// \brief Draws the border of a button.
///
/// \param[in]  left    The left X coordinate of the button.
/// \param[in]  right   The right X coordinate of the button.
/// \param[in]  top     The top Y coordinate of the button.
/// \param[in]  bottom  The bottom Y coordinate of the button.
/// \author Will Blankemeyer
static void drawBorderLines(
    const float left,
    const float right,
    const float top,
    const float bottom
) {
    drawVerticalBorderLines(left, right, top, bottom);
    drawHorizontalBorderLines(left, right, top, bottom);
}

/// \brief A function that draws a circle.
///
/// This function may either fill in the circle with a solid color or only draw the outline.
///
/// \author Will Blankemeyer
using DrawCircleFunction = std::function<void(int, int, int)>;

/// \brief Draws a circle of radius `Button::BORDER_RADIUS` at the given position.
///
/// \param[in]  draw    The draw function.
/// \param[in]  center  The position of the center of the circle.
/// \author Will Blankemeyer
static void drawBorderCircle(const DrawCircleFunction &draw, const Position center) {
    draw(
        static_cast<int>(center.x),
        static_cast<int>(center.y),
        static_cast<int>(Button::BORDER_RADIUS)
    );
}

/// \brief Draws the top-left border circle of a button.
///
/// \param[in]  draw    The draw function.
/// \param[in]  left    The left X coordinate of the button.
/// \param[in]  top     The top Y coordinate of the button.
/// \author Will Blankemeyer
static void drawTopLeftBorderCircle(
    const DrawCircleFunction &draw,
    const float left,
    const float top
) {
    drawBorderCircle(draw, Position((left + Button::BORDER_RADIUS), (top + Button::BORDER_RADIUS)));
}

/// \brief Draws the top-right border circle of a button.
///
/// \param[in]  draw    The draw function.
/// \param[in]  right   The right X coordinate of the button.
/// \param[in]  top     The top Y coordinate of the button.
/// \author Will Blankemeyer
static void drawTopRightBorderCircle(
    const DrawCircleFunction &draw,
    const float right,
    const float top
) {
    drawBorderCircle(
        draw,
        Position((right - Button::BORDER_RADIUS), (top + Button::BORDER_RADIUS))
    );
}

/// \brief Draws the bottom-left border circle of a button.
///
/// \param[in]  draw    The draw function.
/// \param[in]  left    The left X coordinate of the button.
/// \param[in]  bottom  The bottom Y coordinate of the button.
/// \author Will Blankemeyer
static void drawBottomLeftBorderCircle(
    const DrawCircleFunction &draw,
    const float left,
    const float bottom
) {
    drawBorderCircle(
        draw,
        Position((left + Button::BORDER_RADIUS), (bottom - Button::BORDER_RADIUS))
    );
}

/// \brief Draws the bottom-right border circle of a button.
///
/// \param[in]  draw    The draw function.
/// \param[in]  right   The right X coordinate of the button.
/// \param[in]  bottom  The bottom Y coordinate of the button.
/// \author Will Blankemeyer
static void drawBottomRightBorderCircle(
    const DrawCircleFunction &draw,
    const float right,
    const float bottom
) {
    drawBorderCircle(
        draw,
        Position((right - Button::BORDER_RADIUS), (bottom - Button::BORDER_RADIUS))
    );
}

/// \brief Draws the four border circles of a button.
///
/// \param[in]  draw    The draw function.
/// \param[in]  left    The left X coordinate of the button.
/// \param[in]  right   The right X coordinate of the button.
/// \param[in]  top     The top Y coordinate of the button.
/// \param[in]  bottom  The bottom Y coordinate of the button.
/// \author Will Blankemeyer
static void drawBorderCircles(
    const DrawCircleFunction draw,
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

/// \brief Draws a filled rectangle of the given size at the given position.
///
/// \param[in]  center  The position of the center of the rectangle.
/// \param[in]  size    The size of the rectangle.
/// \author Will Blankemeyer
static void fillRectangle(const Position center, const Size size) {
    LCD.FillRectangle(
        static_cast<int>(center.x),
        static_cast<int>(center.y),
        static_cast<int>(size.width),
        static_cast<int>(size.height)
    );
}

/// \brief Returns the given side dimension of a button border excluding the rounded corners.
///
/// \param[in]  dim The dimension (e.g., width, height).
/// \return The 'straight' form of the dimension.
/// \author Will Blankemeyer
static float getStraightDim(const float dim) {
    return dim - (2.f * Button::BORDER_RADIUS);
}

/// \brief Draws two filled rectangles within a button to hide the inner arcs of the border circles.
///
/// \param[in]  left    The left X coordinate of the button.
/// \param[in]  right   The right X coordinate of the button.
/// \param[in]  top     The top Y coordinate of the button.
/// \param[in]  bottom  The bottom Y coordinate of the button.
/// \author Will Blankemeyer
static void fixBorderCircles(
    const float left,
    const float right,
    const float top,
    const float bottom
) {
    const auto width = right - left;
    assert(width >= 0);
    const auto height = bottom - top;
    assert(height >= 0);

    // These rectangles will form a plus '+' shape (or the Rammstein logo, if you're into that). The
    // horizontal bar covers the bottoms of the top-left and top-right border circles as well as the
    // tops of the bottom-left and bottom-right border circles, while the vertical bar covers the
    // right sides of the top-left and bottom-left border circles as well as the left sides of the
    // top-right and bottom-right border circles.

    // Draw the horizontal bar.
    fillRectangle(
        Position(left + 1.f, top + Button::BORDER_RADIUS),
        Size(width - 1.f, getStraightDim(height))
    );
    // Draw the vertical bar.
    fillRectangle(
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

    const auto borderColor = this->borderColor.encode();
    const auto backgroundColor = this->backgroundColor.encode();

    // We begin by drawing the straight sides of the border.
    LCD.SetFontColor(borderColor);
    drawBorderLines(left, right, top, bottom);
    // Next, we draw the border circles. We need to also fill in the circles with the background
    // color because `fixBorderCircles` won't do that for us.
    LCD.SetFontColor(backgroundColor);
    drawBorderCircles(std::bind(&FEHLCD::FillCircle, &LCD, _1, _2, _3), left, right, top, bottom);
    LCD.SetFontColor(borderColor);
    drawBorderCircles(std::bind(&FEHLCD::DrawCircle, &LCD, _1, _2, _3), left, right, top, bottom);
    // Finally, we fill in the body of the button with the background color.
    LCD.SetFontColor(backgroundColor);
    fixBorderCircles(left, right, top, bottom);
}

void Button::fillBorder() const {
    using namespace std::placeholders;

    const auto left = this->getLeftX();
    const auto right = this->getRightX();
    const auto top = this->getTopY();
    const auto bottom = this->getBottomY();

    // The process here is similar to `drawBorder` but considerably simpler.

    // We don't use the background color at all, so we can set the font color to be the border color
    // and be done with that.
    LCD.SetFontColor(this->borderColor.encode());
    drawBorderLines(left, right, top, bottom);
    drawBorderCircles(std::bind(&FEHLCD::FillCircle, &LCD, _1, _2, _3), left, right, top, bottom);
    // Finally, we fill in the body of the button with the border color.
    fixBorderCircles(left, right, top, bottom);
}

} // namespace ui
