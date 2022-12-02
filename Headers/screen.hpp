/// \file
/// \brief The FEH Proteus LCD.

#pragma once

#include <mechanics.hpp>

#include <cstdlib>

/// \brief The FEH Proteus LCD.
///
/// \author Will Blankemeyer
class Screen {
public:
    /// \brief The width, in pixels, of the screen.
    ///
    /// \author Will Blankemeyer
    static constexpr std::size_t WIDTH{320};
    /// \brief The height, in pixels, of the screen.
    ///
    /// \author Will Blankemeyer
    static constexpr std::size_t HEIGHT{240};

    /// \brief The X coordinate of the leftmost column of pixels.
    ///
    /// \author Will Blankemeyer
    static constexpr std::size_t MIN_X{0};
    /// \brief The Y coordinate of the topmost row of pixels.
    ///
    /// \author Will Blankemeyer
    static constexpr std::size_t MIN_Y{0};
    /// \brief The X coordinate of the central column of pixels.
    ///
    /// \author Will Blankemeyer
    static constexpr std::size_t CENTER_X{Screen::WIDTH / 2};
    /// \brief The Y coordinate of the central row of pixels.
    ///
    /// \author Will Blankemeyer
    static constexpr std::size_t CENTER_Y{Screen::HEIGHT / 2};
    /// \brief The X coordinate of the rightmost column of pixels.
    ///
    /// \author Will Blankemeyer
    static constexpr std::size_t MAX_X{Screen::WIDTH - 1};
    /// \brief The Y coordinate of the bottommost row of pixels.
    ///
    /// \author Will Blankemeyer
    static constexpr std::size_t MAX_Y{Screen::HEIGHT - 1};

    /// \brief The position of the pixel in the top-left corner.
    ///
    /// \author Will Blankemeyer
    static const Position TOP_LEFT;
    /// \brief The position of the pixel in the top-right corner.
    ///
    /// \author Will Blankemeyer
    static const Position TOP_RIGHT;
    /// \brief The position of the pixel in the bottom-left corner.
    ///
    /// \author Will Blankemeyer
    static const Position BOTTOM_LEFT;
    /// \brief The position of the pixel in the bottom-right corner.
    ///
    /// \author Will Blankemeyer
    static const Position BOTTOM_RIGHT;

    /// \brief The position of the pixel in the center of the leftmost column.
    ///
    /// \author Will Blankemeyer
    static const Position CENTER_LEFT;
    /// \brief The position of the pixel in the center of the topmost row.
    ///
    /// \author Will Blankemeyer
    static const Position CENTER_TOP;
    /// \brief The position of the pixel in the center of the rightmost column.
    ///
    /// \author Will Blankemeyer
    static const Position CENTER_RIGHT;
    /// \brief The position of the pixel in the center of the bottommost row.
    ///
    /// \author Will Blankemeyer
    static const Position CENTER_BOTTOM;
    /// \brief The position of the pixel in the center of the screen.
    ///
    /// \author Will Blankemeyer
    static const Position CENTER;
};

/// \brief The color of a pixel.
///
/// \author Will Blankemeyer
struct Color {
    /// \author Will Blankemeyer
    Color(unsigned char r, unsigned char g, unsigned char b);

    /// \author Will Blankemeyer
    float r;
    /// \author Will Blankemeyer
    float g;
    /// \author Will Blankemeyer
    float b;

    /// \author Will Blankemeyer
    static const Color WHITE;
    /// \author Will Blankemeyer
    static const Color RED;
    /// \author Will Blankemeyer
    static const Color GREEN;
    /// \author Will Blankemeyer
    static const Color BLUE;
    /// \author Will Blankemeyer
    static const Color BLACK;

    /// \author Will Blankemeyer
    unsigned encode() const;

    /// \author Will Blankemeyer
    float getValue() const;
    /// \author Will Blankemeyer
    float getChroma() const;
    /// \author Will Blankemeyer
    float getHue() const;

private:
    /// \author Will Blankemeyer
    float getMinComp() const;
};