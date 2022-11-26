#include "screen.hpp"

const float Screen::MAX_X{static_cast<float>(Screen::WIDTH - 1)};
const float Screen::MAX_Y{static_cast<float>(Screen::HEIGHT - 1)};

const float Screen::CENTER_X{static_cast<float>(Screen::WIDTH / 2)};
const float Screen::CENTER_Y{static_cast<float>(Screen::HEIGHT / 2)};

const Position Screen::TOP_LEFT{0., 0.};
const Position Screen::TOP_RIGHT{Screen::MAX_X, 0.};
const Position Screen::BOTTOM_LEFT{0., Screen::MAX_Y};
const Position Screen::BOTTOM_RIGHT{Screen::MAX_X, Screen::MAX_Y};

const Position Screen::CENTER_LEFT{0., Screen::CENTER_Y};
const Position Screen::CENTER_TOP{Screen::CENTER_X, 0.};
const Position Screen::CENTER_RIGHT{Screen::MAX_X, Screen::CENTER_Y};
const Position Screen::CENTER_BOTTOM{Screen::CENTER_X, Screen::MAX_Y};
const Position Screen::CENTER{Screen::CENTER_X, Screen::CENTER_Y};
