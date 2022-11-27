/// \file
/// \brief The Peggle user interface (UI).

#pragma once

#include <cstdlib>
#include <string>

#include "mechanics.hpp"
#include "screen.hpp"

/// \brief The Peggle user interface (UI).
namespace ui {

/// \brief The width and height of a `View`.
///
/// \author Will Blankemeyer
struct Size {
    /// \brief Creates a new `Size`.
    ///
    /// \param[in]  width   The width, in pixels.
    /// \param[in]  height  The height, in pixels.
    /// \author Will Blankemeyer
    Size(float width, float height);

    /// \brief The width, in pixels.
    ///
    /// \author Will Blankemeyer
    float width;
    /// \brief The height, in pixels.
    ///
    /// \author Will Blankemeyer
    float height;
};

/// \brief A UI element.
///
/// \author Will Blankemeyer
class View {
public:
    /// \brief The size of this view.
    ///
    /// \return The size.
    /// \author Will Blankemeyer
    virtual Size getSize() const {
        return {this->getWidth(), this->getHeight()};
    }

    /// \brief The width of this view.
    ///
    /// This method is provided in addition to `getSize` because it may be implemented more
    /// efficiently in some `View` subclasses.
    ///
    /// \return The width, in pixels.
    /// \author Will Blankemeyer
    virtual float getWidth() const = 0;
    /// \brief The height of this view.
    ///
    /// This method is provided in addition to `getSize` because it may be implemented more
    /// efficiently in some `View` subclasses.
    ///
    /// \return The height, in pixels.
    /// \author Will Blankemeyer
    virtual float getHeight() const = 0;
    /// \brief The position of the center of this view.
    ///
    /// \return The central position.
    /// \author Will Blankemeyer
    virtual Position getCenter() const = 0;

    /// \brief The X coordinate of the left boundary of this view.
    ///
    /// \return The leftmost X coordinate.
    /// \author Will Blankemeyer
    float getLeftX() const;
    /// \brief The X coordinate of the right boundary of this view.
    ///
    /// \return The rightmost X coordinate.
    /// \author Will Blankemeyer
    float getRightX() const;
    /// \brief The Y coordinate of the top boundary of this view.
    ///
    /// \return The topmost Y coordinate.
    /// \author Will Blankemeyer
    float getTopY() const;
    /// \brief The Y coordinate of the bottom boundary of this view.
    ///
    /// \return The bottommost Y coordinate.
    /// \author Will Blankemeyer
    float getBottomY() const;

    /// \brief The position of the top-left corner of this view.
    ///
    /// \return The top-left position.
    /// \author Will Blankemeyer
    Position getTopLeft() const;
    /// \brief The position of the top-right corner of this view.
    ///
    /// \return The top-right position.
    /// \author Will Blankemeyer
    Position getTopRight() const;
    /// \brief The position of the bottom-left corner of this view.
    ///
    /// \return The bottom-left position.
    /// \author Will Blankemeyer
    Position getBottomLeft() const;
    /// \brief The position of the bottom-right corner of this view.
    ///
    /// \return The bottom-right position.
    /// \author Will Blankemeyer
    Position getBottomRight() const;

    /// \brief Determines if the given position is contained within the boundaries of this view.
    ///
    /// \param[in]  pos The position.
    /// \return Whether or not this view contains the given position.
    /// \author Will Blankemeyer
    bool contains(Position pos) const;
};

/// \brief A single line of text.
///
/// \author Will Blankemeyer
class Label : public View {
public:
    /// \brief Creates a new label.
    ///
    /// \param[in]  center  The position of the center of this label.
    /// \param[in]  content The textual content of this label.
    /// \param[in]  color   The font color. The default is white.
    /// \author Will Blankemeyer
    Label(Position center, std::string content, Color color = Color::White);

    /// \brief A mutable reference to the textual content of this label.
    ///
    /// \return The content.
    /// \author Will Blankemeyer
    std::string &getContent() {
        return this->content;
    }

    /// \brief An immutable reference to the textual content of this label.
    ///
    /// \return The content.
    /// \author Will Blankemeyer
    const std::string &getContent() const {
        return this->content;
    }

    /// \brief The font color.
    ///
    /// \return The font color.
    /// \author Will Blankemeyer
    Color getColor() const {
        return this->color;
    }

    /// \brief Sets the font color.
    ///
    /// \param[in]  color   The new font color.
    /// \author Will Blankemeyer
    void setColor(const Color color) {
        this->color = color;
    }

    virtual float getWidth() const override;
    virtual float getHeight() const override;

    virtual Position getCenter() const override {
        return this->center;
    }

    /// \brief Draws this label to the screen.
    ///
    /// \warning This method mutates the global font color of the LCD.
    /// \author Will Blankemeyer
    void draw() const;

private:
    Position center;
    std::string content;
    Color color;
};

/// \brief A pushbutton containing a label.
///
/// \author Will Blankemeyer
class Button : public View {
public:
    /// \brief Creates a new button with default padding.
    ///
    /// The size of this button is determined by adding `DEFAULT_PADDING` to the size of the
    /// contained label.
    ///
    /// \param[in]  label   The button label.
    /// \param[in]  color   The border color. The default is white.
    /// \author Will Blankemeyer
    Button(Label label, Color color = Color::White);
    /// \brief Creates a new button.
    ///
    /// \param[in]  label   The button label.
    /// \param[in]  size    The size of the button.
    /// \param[in]  color   The border color. The default is white.
    /// \author Will Blankemeyer
    Button(Label label, Size size, Color color = Color::White);

    /// \brief The distance, in pixels, between the boundaries of a label and those of the
    /// containing button if constructed with default padding.
    ///
    /// \author Will Blankemeyer
    static constexpr float DEFAULT_PADDING{5.f};

    /// \brief A mutable reference to the contained label.
    ///
    /// \return The label.
    /// \author Will Blankemeyer
    Label &getLabel() {
        return this->label;
    }

    /// \brief An immutable reference to the contained label.
    ///
    /// \return The label.
    /// \author Will Blankemeyer
    const Label &getLabel() const {
        return this->label;
    }

    virtual Size getSize() const override {
        return this->size;
    }

    virtual float getWidth() const override {
        return this->size.width;
    }

    virtual float getHeight() const override {
        return this->size.height;
    }

    virtual Position getCenter() const override {
        return this->label.getCenter();
    }

    /// \brief Determines if this button is currently pressed.
    ///
    /// \return Whether or not this button is pressed.
    /// \author Will Blankemeyer
    bool isPressed() const;

    /// \brief Draws this button, in its unpressed state, to the screen.
    ///
    /// \warning This method mutates the global font color of the LCD.
    /// \author Will Blankemeyer
    void drawUnpressed() const;
    /// \brief Draws this lbutton, in its pressed state, to the screen.
    ///
    /// \warning This method mutates the global font color of the LCD.
    /// \author Will Blankemeyer
    void drawPressed() const;

private:
    Label label;
    Size size;
    Color color;

    void drawBorder() const;
    void fillBorder() const;
};

} // namespace ui
