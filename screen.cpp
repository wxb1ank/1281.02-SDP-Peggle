#include "screen.hpp"

const Position Screen::TOP_LEFT{Screen::MIN_X, Screen::MIN_Y};
const Position Screen::TOP_RIGHT{Screen::MAX_X, Screen::MIN_Y};
const Position Screen::BOTTOM_LEFT{Screen::MIN_X, Screen::MAX_Y};
const Position Screen::BOTTOM_RIGHT{Screen::MAX_X, Screen::MAX_Y};

const Position Screen::CENTER_LEFT{Screen::MIN_X, Screen::CENTER_Y};
const Position Screen::CENTER_TOP{Screen::CENTER_X, Screen::MIN_Y};
const Position Screen::CENTER_RIGHT{Screen::MAX_X, Screen::CENTER_Y};
const Position Screen::CENTER_BOTTOM{Screen::CENTER_X, Screen::MAX_Y};
const Position Screen::CENTER{Screen::CENTER_X, Screen::CENTER_Y};
