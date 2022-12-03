/// \file
/// \brief The Peggle user interface (UI).

#pragma once

#include <mechanics.hpp>
#include <screen.hpp>

#include <cstdlib>
#include <string>
#include <vector>

/// \brief The Peggle user interface (UI).
///
/// This library was loosely influenced by Apple's *UIKit*. It is lighter than a traditonal MVC
/// design but retains the essential `View` class.
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
    Size(std::size_t width, std::size_t height);
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

/// \brief A view that fills the entire screen.
///
/// This class offers optimized implementations of basic `View` methods for views that are always
/// the same size as the screen.
///
/// \author Will Blankemeyer
class FullscreenView : public View {
public:
    /// \brief Destroys this fullscreen view.
    ///
    /// \author Will Blankemeyer
    virtual ~FullscreenView();

    /// \author Will Blankemeyer
    virtual float getWidth() const final;
    /// \author Will Blankemeyer
    virtual float getHeight() const final;
    /// \author Will Blankemeyer
    virtual Position getCenter() const final;

    /// \author Will Blankemeyer
    virtual float getLeftX() const final;
    /// \author Will Blankemeyer
    virtual float getRightX() const final;
    /// \author Will Blankemeyer
    virtual float getTopY() const final;
    /// \author Will Blankemeyer
    virtual float getBottomY() const final;

    /// \author Will Blankemeyer
    virtual Position getTopLeft() const final;
    /// \author Will Blankemeyer
    virtual Position getTopRight() const final;
    /// \author Will Blankemeyer
    virtual Position getBottomLeft() const final;
    /// \author Will Blankemeyer
    virtual Position getBottomRight() const final;
};

/// \brief A fullscreen view that draws a rectangle filled with a single color.
///
/// \author Will Blankemeyer
class BackgroundView final : public FullscreenView {
public:
    /// \brief Creates a new background view of the given color.
    ///
    /// \param[in]  color   The initial color.
    /// \author Will Blankemeyer
    BackgroundView(Color color);

    /// \brief A mutable reference to the background color.
    ///
    /// \return The color.
    /// \author Will Blankemeyer
    Color &getColor();
    /// \brief An immutable reference to the background color.
    ///
    /// \return The color.
    /// \author Will Blankemeyer
    const Color &getColor() const;

    /// \author Will Blankemeyer
    virtual void draw() const override;

private:
    /// \author Will Blankemeyer
    Color color;
};

/// \brief A single line of text.
///
/// \author Will Blankemeyer
class Label : public View {
public:
    /// \brief Creates a new label.
    ///
    /// \param[in]  center      The initial position of the center of this label.
    /// \param[in]  content     The initial textual content of this label.
    /// \param[in]  fontColor   The initial font color.
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

    /// \brief A mutable reference to the font color.
    ///
    /// \return The font color.
    /// \author Will Blankemeyer
    Color &getFontColor();
    /// \brief An immutable reference to the font color.
    ///
    /// \return The font color.
    /// \author Will Blankemeyer
    const Color &getFontColor() const;

    /// \author Will Blankemeyer
    virtual float getWidth() const override;
    /// \author Will Blankemeyer
    virtual float getHeight() const override;
    /// \author Will Blankemeyer
    virtual Position getCenter() const override;
    /// \author Will Blankemeyer
    virtual void draw() const override;

private:
    /// \author Will Blankemeyer
    Position center;
    /// \author Will Blankemeyer
    std::string content;
    /// \author Will Blankemeyer
    Color fontColor;
};

/// \brief A collection of labels stacked upon each other to emulate 3D depth.
///
/// \author Will Blankemeyer
class StackedLabel : public ui::Label {
public:
    /// \brief Creates a new stacked label from the given label.
    ///
    /// \param[in]  label   The label to stack.
    /// \author Will Blankemeyer
    StackedLabel(Label label);

    /// \brief Destroys this stacked label.
    ///
    /// \author Will Blankemeyer
    virtual ~StackedLabel();

    /// \author Will Blankemeyer
    virtual void draw() const override;
};

/// \brief One or more lines of text.
///
/// \author Will Blankemeyer
class MultilineLabel : public ui::View {
public:
    /// \brief Creates a new multiline label.
    ///
    /// \param[in]  center      The initial position of the center of this multiline label.
    /// \param[in]  content     The initial textual content of this multiline label.
    /// \param[in]  fontColor   The initial font color.
    /// \author Will Blankemeyer
    MultilineLabel(
        Position center,
        std::string content,
        Color fontColor
    );

    /// \brief Destroys this multiline label.
    ///
    /// \author Will Blankemeyer
    virtual ~MultilineLabel();

    /// \author Will Blankemeyer
    virtual float getWidth() const override;
    /// \author Will Blankemeyer
    virtual float getHeight() const override;
    /// \author Will Blankemeyer
    virtual Position getCenter() const override;
    /// \author Will Blankemeyer
    virtual void draw() const override;

private:
    /// \author Will Blankemeyer
    Position center;
    /// \author Will Blankemeyer
    Color fontColor;
    /// \author Will Blankemeyer
    std::vector<std::string> lines;
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
    /// \param[in]  label           The button label.
    /// \param[in]  borderColor     The border color.
    /// \param[in]  backgroundColor The background color.
    /// \author Will Blankemeyer
    Button(Label label, Color borderColor, Color backgroundColor);
    /// \brief Creates a new button.
    ///
    /// \param[in]  label           The button label.
    /// \param[in]  borderColor     The border color.
    /// \param[in]  backgroundColor The background color.
    /// \param[in]  size            The size of the button.
    /// \author Will Blankemeyer
    Button(Label label, Color borderColor, Color backgroundColor, Size size);

    /// \brief Destroys this button.
    ///
    /// \author Will Blankemeyer
    virtual ~Button();

    /// \brief The distance, in pixels, between the boundaries of a label and those of the
    /// containing button if constructed with default padding.
    ///
    /// \author Will Blankemeyer
    static constexpr float DEFAULT_PADDING{5.f};

    /// \brief The radius, in pixels, of the rounded corners of this button.
    ///
    /// \author Will Blankemeyer
    static constexpr float BORDER_RADIUS{5.f};

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

    /// \brief A mutable reference to the border color.
    ///
    /// \return The border color.
    /// \author Will Blankemeyer
    Color &getBorderColor();
    /// \brief An immutable reference to the border color.
    ///
    /// \return The border color.
    /// \author Will Blankemeyer
    const Color &getBorderColor() const;

    /// \brief A mutable reference to the background color.
    ///
    /// \return The background color.
    /// \author Will Blankemeyer
    Color &getBackgroundColor();
    /// \brief An immutable reference to the background color.
    ///
    /// \return The background color.
    /// \author Will Blankemeyer
    const Color &getBackgroundColor() const;

    /// \brief Determines if this button is currently pressed.
    ///
    /// \return Whether or not this button is pressed.
    /// \warning This method updates the LCD.
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

    /// \brief Returns an extension of the given dimension by `DEFAULT_PADDING`.
    ///
    /// \param[in]  dim The dimension to pad (e.g., width, height).
    /// \return The padded dimension.
    /// \author Will Blankemeyer
    static float pad(float dim);

    /// \author Will Blankemeyer
    virtual Size getSize() const override;
    /// \author Will Blankemeyer
    virtual float getWidth() const override;
    /// \author Will Blankemeyer
    virtual float getHeight() const override;
    /// \author Will Blankemeyer
    virtual Position getCenter() const override;
    /// \author Will Blankemeyer
    virtual void draw() const override;

private:
    /// \author Will Blankemeyer
    Label label;
    /// \author Will Blankemeyer
    Color borderColor;
    /// \author Will Blankemeyer
    Color backgroundColor;
    /// \author Will Blankemeyer
    Size size;

    /// \author Will Blankemeyer
    void drawBorder() const;
    /// \author Will Blankemeyer
    void fillBorder() const;
};

} // namespace ui
