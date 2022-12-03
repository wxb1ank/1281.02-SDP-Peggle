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

    /// \author Will Blankemeyer
    static constexpr std::size_t LEFT{Screen::MIN_X};
    /// \author Will Blankemeyer
    static constexpr std::size_t RIGHT{Screen::MAX_X};
    /// \author Will Blankemeyer
    static constexpr std::size_t TOP{Screen::MIN_Y};
    /// \author Will Blankemeyer
    static constexpr std::size_t BOTTOM{Screen::MAX_Y};

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
/// This type provides all CSS colors as static data members. With `Color::<name>.encode()`, they
/// are a drop-in hygienic replacement for the color macros offered by `LCDColors.h`.
///
/// As is seen in the `getValue`, `getChroma`, and `getHue` methods, we were originally intending to
/// use this type for more---ultimately, we wanted a `shiftHue` function that could be called in a
/// loop to produce a rainbow effect---but unforunately, we didn't have enough time to implement it.
///
/// \author Will Blankemeyer
struct Color {
    /// \author Will Blankemeyer
    Color(unsigned rgb);
    /// \author Will Blankemeyer
    Color(unsigned char r, unsigned char g, unsigned char b);

    /// \brief The red component.
    ///
    /// \author Will Blankemeyer
    float r;
    /// \brief The green component.
    ///
    /// \author Will Blankemeyer
    float g;
    /// \brief The blue component.
    ///
    /// \author Will Blankemeyer
    float b;

    /// \brief Returns this color encoded in RGB8 format.
    ///
    /// The result of this method may be passed directly to `LCD::SetFontColor` and
    /// `LCD::SetBackgroundColor`.
    ///
    /// \return The RGB8 encoding of this color.
    /// \author Will Blankemeyer
    unsigned encode() const;

    /// \brief The maximum component value.
    ///
    /// \return The value, or maximum component.
    /// \author Will Blankemeyer
    float getValue() const;
    /// \brief The range in component values.
    ///
    /// \return The chroma, or range.
    /// \author Will Blankemeyer
    float getChroma() const;
    /// \brief The hue.
    ///
    /// \return The hue.
    /// \author Will Blankemeyer
    float getHue() const;

private:
    /// \brief The minimum component value.
    ///
    /// \return The minimum component.
    /// \author Will Blankemeyer
    float getMinComp() const;

public:
    /// \author Will Blankemeyer
    static const Color BLACK;
    /// \author Will Blankemeyer
    static const Color NAVY;
    /// \author Will Blankemeyer
    static const Color DARKBLUE;
    /// \author Will Blankemeyer
    static const Color MEDIUMBLUE;
    /// \author Will Blankemeyer
    static const Color BLUE;
    /// \author Will Blankemeyer
    static const Color DARKGREEN;
    /// \author Will Blankemeyer
    static const Color GREEN;
    /// \author Will Blankemeyer
    static const Color TEAL;
    /// \author Will Blankemeyer
    static const Color DARKCYAN;
    /// \author Will Blankemeyer
    static const Color DEEPSKYBLUE;
    /// \author Will Blankemeyer
    static const Color DARKTURQUOISE;
    /// \author Will Blankemeyer
    static const Color MEDIUMSPRINGGREEN;
    /// \author Will Blankemeyer
    static const Color LIME;
    /// \author Will Blankemeyer
    static const Color SPRINGGREEN;
    /// \author Will Blankemeyer
    static const Color AQUA;
    /// \author Will Blankemeyer
    static const Color CYAN;
    /// \author Will Blankemeyer
    static const Color MIDNIGHTBLUE;
    /// \author Will Blankemeyer
    static const Color DODGERBLUE;
    /// \author Will Blankemeyer
    static const Color LIGHTSEAGREEN;
    /// \author Will Blankemeyer
    static const Color FORESTGREEN;
    /// \author Will Blankemeyer
    static const Color SEAGREEN;
    /// \author Will Blankemeyer
    static const Color DARKSLATEGRAY;
    /// \author Will Blankemeyer
    static const Color LIMEGREEN;
    /// \author Will Blankemeyer
    static const Color MEDIUMSEAGREEN;
    /// \author Will Blankemeyer
    static const Color TURQUOISE;
    /// \author Will Blankemeyer
    static const Color ROYALBLUE;
    /// \author Will Blankemeyer
    static const Color STEELBLUE;
    /// \author Will Blankemeyer
    static const Color DARKSLATEBLUE;
    /// \author Will Blankemeyer
    static const Color MEDIUMTURQUOISE;
    /// \author Will Blankemeyer
    static const Color INDIGO;
    /// \author Will Blankemeyer
    static const Color DARKOLIVEGREEN;
    /// \author Will Blankemeyer
    static const Color CADETBLUE;
    /// \author Will Blankemeyer
    static const Color CORNFLOWERBLUE;
    /// \author Will Blankemeyer
    static const Color GRAY;
    /// \author Will Blankemeyer
    static const Color MEDIUMAQUAMARINE;
    /// \author Will Blankemeyer
    static const Color DIMGRAY;
    /// \author Will Blankemeyer
    static const Color SLATEBLUE;
    /// \author Will Blankemeyer
    static const Color OLIVEDRAB;
    /// \author Will Blankemeyer
    static const Color SLATEGRAY;
    /// \author Will Blankemeyer
    static const Color LIGHTSLATEGRAY;
    /// \author Will Blankemeyer
    static const Color MEDIUMSLATEBLUE;
    /// \author Will Blankemeyer
    static const Color LAWNGREEN;
    /// \author Will Blankemeyer
    static const Color CHARTREUSE;
    /// \author Will Blankemeyer
    static const Color AQUAMARINE;
    /// \author Will Blankemeyer
    static const Color MAROON;
    /// \author Will Blankemeyer
    static const Color PURPLE;
    /// \author Will Blankemeyer
    static const Color OLIVE;
    /// \author Will Blankemeyer
    static const Color SKYBLUE;
    /// \author Will Blankemeyer
    static const Color LIGHTSKYBLUE;
    /// \author Will Blankemeyer
    static const Color BLUEVIOLET;
    /// \author Will Blankemeyer
    static const Color DARKRED;
    /// \author Will Blankemeyer
    static const Color DARKMAGENTA;
    /// \author Will Blankemeyer
    static const Color SADDLEBROWN;
    /// \author Will Blankemeyer
    static const Color DARKSEAGREEN;
    /// \author Will Blankemeyer
    static const Color LIGHTGREEN;
    /// \author Will Blankemeyer
    static const Color MEDIUMPURPLE;
    /// \author Will Blankemeyer
    static const Color DARKVIOLET;
    /// \author Will Blankemeyer
    static const Color PALEGREEN;
    /// \author Will Blankemeyer
    static const Color DARKORCHID;
    /// \author Will Blankemeyer
    static const Color YELLOWGREEN;
    /// \author Will Blankemeyer
    static const Color SIENNA;
    /// \author Will Blankemeyer
    static const Color BROWN;
    /// \author Will Blankemeyer
    static const Color DARKGRAY;
    /// \author Will Blankemeyer
    static const Color LIGHTBLUE;
    /// \author Will Blankemeyer
    static const Color GREENYELLOW;
    /// \author Will Blankemeyer
    static const Color PALETURQUOISE;
    /// \author Will Blankemeyer
    static const Color LIGHTSTEELBLUE;
    /// \author Will Blankemeyer
    static const Color POWDERBLUE;
    /// \author Will Blankemeyer
    static const Color FIREBRICK;
    /// \author Will Blankemeyer
    static const Color DARKGOLDENROD;
    /// \author Will Blankemeyer
    static const Color MEDIUMORCHID;
    /// \author Will Blankemeyer
    static const Color SCARLET;
    /// \author Will Blankemeyer
    static const Color ROSYBROWN;
    /// \author Will Blankemeyer
    static const Color DARKKHAKI;
    /// \author Will Blankemeyer
    static const Color SILVER;
    /// \author Will Blankemeyer
    static const Color MEDIUMVIOLETRED;
    /// \author Will Blankemeyer
    static const Color INDIANRED;
    /// \author Will Blankemeyer
    static const Color PERU;
    /// \author Will Blankemeyer
    static const Color CHOCOLATE;
    /// \author Will Blankemeyer
    static const Color TAN;
    /// \author Will Blankemeyer
    static const Color LIGHTGRAY;
    /// \author Will Blankemeyer
    static const Color THISTLE;
    /// \author Will Blankemeyer
    static const Color ORCHID;
    /// \author Will Blankemeyer
    static const Color GOLDENROD;
    /// \author Will Blankemeyer
    static const Color PALEVIOLETRED;
    /// \author Will Blankemeyer
    static const Color CRIMSON;
    /// \author Will Blankemeyer
    static const Color GAINSBORO;
    /// \author Will Blankemeyer
    static const Color PLUM;
    /// \author Will Blankemeyer
    static const Color BURLYWOOD;
    /// \author Will Blankemeyer
    static const Color LIGHTCYAN;
    /// \author Will Blankemeyer
    static const Color LAVENDER;
    /// \author Will Blankemeyer
    static const Color DARKSALMON;
    /// \author Will Blankemeyer
    static const Color VIOLET;
    /// \author Will Blankemeyer
    static const Color PALEGOLDENROD;
    /// \author Will Blankemeyer
    static const Color LIGHTCORAL;
    /// \author Will Blankemeyer
    static const Color KHAKI;
    /// \author Will Blankemeyer
    static const Color ALICEBLUE;
    /// \author Will Blankemeyer
    static const Color HONEYDEW;
    /// \author Will Blankemeyer
    static const Color AZURE;
    /// \author Will Blankemeyer
    static const Color SANDYBROWN;
    /// \author Will Blankemeyer
    static const Color WHEAT;
    /// \author Will Blankemeyer
    static const Color BEIGE;
    /// \author Will Blankemeyer
    static const Color WHITESMOKE;
    /// \author Will Blankemeyer
    static const Color MINTCREAM;
    /// \author Will Blankemeyer
    static const Color GHOSTWHITE;
    /// \author Will Blankemeyer
    static const Color SALMON;
    /// \author Will Blankemeyer
    static const Color ANTIQUEWHITE;
    /// \author Will Blankemeyer
    static const Color LINEN;
    /// \author Will Blankemeyer
    static const Color LIGHTGOLDENRODYELLOW;
    /// \author Will Blankemeyer
    static const Color OLDLACE;
    /// \author Will Blankemeyer
    static const Color RED;
    /// \author Will Blankemeyer
    static const Color FUCHSIA;
    /// \author Will Blankemeyer
    static const Color MAGENTA;
    /// \author Will Blankemeyer
    static const Color DEEPPINK;
    /// \author Will Blankemeyer
    static const Color ORANGERED;
    /// \author Will Blankemeyer
    static const Color TOMATO;
    /// \author Will Blankemeyer
    static const Color HOTPINK;
    /// \author Will Blankemeyer
    static const Color CORAL;
    /// \author Will Blankemeyer
    static const Color DARKORANGE;
    /// \author Will Blankemeyer
    static const Color LIGHTSALMON;
    /// \author Will Blankemeyer
    static const Color ORANGE;
    /// \author Will Blankemeyer
    static const Color LIGHTPINK;
    /// \author Will Blankemeyer
    static const Color PINK;
    /// \author Will Blankemeyer
    static const Color GOLD;
    /// \author Will Blankemeyer
    static const Color PEACHPUFF;
    /// \author Will Blankemeyer
    static const Color NAVAJOWHITE;
    /// \author Will Blankemeyer
    static const Color MOCCASIN;
    /// \author Will Blankemeyer
    static const Color BISQUE;
    /// \author Will Blankemeyer
    static const Color MISTYROSE;
    /// \author Will Blankemeyer
    static const Color BLANCHEDALMOND;
    /// \author Will Blankemeyer
    static const Color PAPAYAWHIP;
    /// \author Will Blankemeyer
    static const Color LAVENDERBLUSH;
    /// \author Will Blankemeyer
    static const Color SEASHELL;
    /// \author Will Blankemeyer
    static const Color CORNSILK;
    /// \author Will Blankemeyer
    static const Color LEMONCHIFFON;
    /// \author Will Blankemeyer
    static const Color FLORALWHITE;
    /// \author Will Blankemeyer
    static const Color SNOW;
    /// \author Will Blankemeyer
    static const Color YELLOW;
    /// \author Will Blankemeyer
    static const Color LIGHTYELLOW;
    /// \author Will Blankemeyer
    static const Color IVORY;
    /// \author Will Blankemeyer
    static const Color WHITE;
};
