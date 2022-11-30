/// \file
/// \brief The Peggle user interface (UI).

#pragma once

#include <mechanics.hpp>
#include <screen.hpp>

#include <cstdlib>
#include <string>

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
    /// \brief Destroys this view.
    ///
    /// \author Will Blankemeyer
    virtual ~View();

    /// \brief The size of this view.
    ///
    /// \return The size.
    /// \author Will Blankemeyer
    virtual Size getSize() const;

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
    virtual float getLeftX() const;
    /// \brief The X coordinate of the right boundary of this view.
    ///
    /// \return The rightmost X coordinate.
    /// \author Will Blankemeyer
    virtual float getRightX() const;
    /// \brief The Y coordinate of the top boundary of this view.
    ///
    /// \return The topmost Y coordinate.
    /// \author Will Blankemeyer
    virtual float getTopY() const;
    /// \brief The Y coordinate of the bottom boundary of this view.
    ///
    /// \return The bottommost Y coordinate.
    /// \author Will Blankemeyer
    virtual float getBottomY() const;

    /// \brief The position of the top-left corner of this view.
    ///
    /// \return The top-left position.
    /// \author Will Blankemeyer
    virtual Position getTopLeft() const;
    /// \brief The position of the top-right corner of this view.
    ///
    /// \return The top-right position.
    /// \author Will Blankemeyer
    virtual Position getTopRight() const;
    /// \brief The position of the bottom-left corner of this view.
    ///
    /// \return The bottom-left position.
    /// \author Will Blankemeyer
    virtual Position getBottomLeft() const;
    /// \brief The position of the bottom-right corner of this view.
    ///
    /// \return The bottom-right position.
    /// \author Will Blankemeyer
    virtual Position getBottomRight() const;

    /// \brief Determines if the given position is contained within the boundaries of this view.
    ///
    /// \param[in]  Pos The position.
    /// \return Whether or not this view contains the given position.
    /// \author Will Blankemeyer
    bool contains(Position pos) const;

    /// \brief Draws this view to the screen.
    ///
    /// \author Will Blankemeyer
    virtual void draw() const = 0;
};

class FullscreenView : public View {
public:
    virtual ~FullscreenView();

    virtual float getWidth() const final;
    virtual float getHeight() const final;
    virtual Position getCenter() const final;

    virtual float getLeftX() const final;
    virtual float getRightX() const final;
    virtual float getTopY() const final;
    virtual float getBottomY() const final;

    virtual Position getTopLeft() const final;
    virtual Position getTopRight() const final;
    virtual Position getBottomLeft() const final;
    virtual Position getBottomRight() const final;
};

class BackgroundView final : public FullscreenView {
public:
    BackgroundView(Color color);

    virtual ~BackgroundView();

    Color &getColor();
    const Color &getColor() const;

    virtual void draw() const override;

private:
    Color color;
};

/// \brief A single line of text.
///
/// \author Will Blankemeyer
class Label : public View {
public:
    /// \brief Creates a new label.
    ///
    /// \param[in]  center          The position of the center of this label.
    /// \param[in]  content         The textual content of this label.
    /// \param[in]  fontColor       The font color.
    /// \author Will Blankemeyer
    Label(
        Position center,
        std::string content,
        Color fontColor
    );

    /// \brief Destroys this label.
    ///
    /// \author Will Blankemeyer
    virtual ~Label();

    /// \brief A mutable reference to the textual content of this label.
    ///
    /// \return The content.
    /// \author Will Blankemeyer
    std::string &getContent();
    /// \brief An immutable reference to the textual content of this label.
    ///
    /// \return The content.
    /// \author Will Blankemeyer
    const std::string &getContent() const;

    /// \brief The font color.
    ///
    /// \return The font color.
    /// \author Will Blankemeyer
    Color &getFontColor();
    const Color &getFontColor() const;

    virtual float getWidth() const override;
    virtual float getHeight() const override;
    virtual Position getCenter() const override;

    virtual void draw() const override;

private:
    Position center;
    std::string content;
    Color fontColor;
};

class StackedLabel : public ui::Label {
public:
    /// \brief Creates a new stacked label.
    ///
    /// \author Will Blankemeyer
    StackedLabel(Label label);

    /// \brief Destroys this label.
    ///
    /// \author Will Blankemeyer
    virtual ~StackedLabel();

    virtual void draw() const override;
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
    /// \param[in]  label       The button label.
    /// \param[in]  borderColor The border color.
    /// \author Will Blankemeyer
    Button(Label label, Color borderColor);

    /// \brief Destroys this button.
    ///
    /// \author Will Blankemeyer
    virtual ~Button();

    /// \brief The distance, in pixels, between the boundaries of a label and those of the
    /// containing button if constructed with default padding.
    ///
    /// \author Will Blankemeyer
    static constexpr float DEFAULT_PADDING{5.f};

    /// \brief A mutable reference to the contained label.
    ///
    /// \return The label.
    /// \author Will Blankemeyer
    Label &getLabel();
    /// \brief An immutable reference to the contained label.
    ///
    /// \return The label.
    /// \author Will Blankemeyer
    const Label &getLabel() const;

    Color &getBorderColor();
    const Color &getBorderColor() const;

    virtual Size getSize() const override;
    virtual float getWidth() const override;
    virtual float getHeight() const override;
    virtual Position getCenter() const override;

    /// \brief Determines if this button is currently pressed.
    ///
    /// \return Whether or not this button is pressed.
    /// \author Will Blankemeyer
    bool isPressed() const;

    virtual void draw() const override;

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
    Color borderColor;

    float pad(float dim) const;

    void drawBorder() const;
    void fillBorder() const;
};

} // namespace ui
