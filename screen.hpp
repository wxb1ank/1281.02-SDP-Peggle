#pragma once

#include <cstdlib>

#include "mechanics.hpp"

class Screen {
public:
    static constexpr std::size_t WIDTH{320};
    static constexpr std::size_t HEIGHT{240};

    static constexpr std::size_t MIN_X{0};
    static constexpr std::size_t MIN_Y{0};
    static constexpr std::size_t CENTER_X{Screen::WIDTH / 2};
    static constexpr std::size_t CENTER_Y{Screen::HEIGHT / 2};
    static constexpr std::size_t MAX_X{Screen::WIDTH - 1};
    static constexpr std::size_t MAX_Y{Screen::HEIGHT - 1};

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
