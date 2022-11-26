#pragma once

#include <cstdlib>

#include "mechanics.hpp"

class Screen {
public:
    static constexpr std::size_t WIDTH{320};
    static constexpr std::size_t HEIGHT{240};

    static const float MAX_X;
    static const float MAX_Y;

    static const float CENTER_X;
    static const float CENTER_Y;

    static const Position TOP_LEFT;
    static const Position TOP_RIGHT;
    static const Position BOTTOM_LEFT;
    static const Position BOTTOM_RIGHT;

    static const Position CENTER_LEFT;
    static const Position CENTER_TOP;
    static const Position CENTER_RIGHT;
    static const Position CENTER_BOTTOM;
    static const Position CENTER;
};
