/// \file
/// \brief The FEH Proteus LCD font.

#pragma once

#include <cstdlib>

/// \brief The FEH Proteus LCD font.
///
/// A cursory reading of the simulator LCD library suggests that strings are written as
/// left-to-right monospaced sequences of characters, which are 12 pixels wide and 17 pixels tall,
/// that are not grid-aligned and may be placed at any arbitrary position. Unfortunately, this does
/// not capture the full picture.
///
/// The Proteus LCD font is actually stored as an array of 5x7 pixel character bitmaps. When drawn
/// to the screen, each character is then doubled in size to encompass a 10x14 pixel area. The
/// aforementioned 12x17 pixel size arises from vertical and horizontal padding; obstensibly, each
/// character is left-padded by 2 pixels and bottom-padded by 3. As such, all strings written by
/// `LCD::WriteAt` have left margins of 2 pixels and bottom margins of 3 pixels, and internal
/// horizontal padding of 2 pixels. These facts must be accounted for when aligning text labels with
/// other UI elements, and so constants representing character width, height, margins, and padding
/// are provided as static data members of this class.
///
/// \author Will Blankemeyer
class Font {
public:
    /// \brief The width, in pixels, of a single character.
    ///
    /// \author Will Blankemeyer
    static constexpr std::size_t WIDTH{10};
    /// \brief The height, in pixels, of a single character.
    ///
    /// \author Will Blankemeyer
    static constexpr std::size_t HEIGHT{14};

    static constexpr std::size_t LEFT_MARGIN{2};
    static constexpr std::size_t BOTTOM_MARGIN{3};

    static constexpr std::size_t HORI_PADDING{2};
};
