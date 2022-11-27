// This is necessary for the `M_PI` family of macros.
#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>

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

Color::Color(const unsigned char r, const unsigned char g, const unsigned char b)
:   r{r}, g{g}, b{b}
{}

unsigned Color::encode() const {
    return (static_cast<unsigned>(this->r) << 16) |
           (static_cast<unsigned>(this->g) << 8) |
           static_cast<unsigned>(this->b);
}

unsigned char Color::getValue() const {
    return std::max({this->r, this->g, this->b});
}

unsigned char Color::getMinComp() const {
    return std::min({this->r, this->g, this->b});
}

unsigned char Color::getChroma() const {
    return this->getValue() - this->getMinComp();
}

float Color::getHue() const {
    const auto r = static_cast<float>(this->r);
    const auto g = static_cast<float>(this->g);
    const auto b = static_cast<float>(this->b);

    // See: <https://en.wikipedia.org/wiki/Hue#Defining_hue_in_terms_of_RGB>.
    return std::atan2(std::sqrt(3.f) * (g - b), (2.f * r) - g - b);
}

const Color Color::WHITE{0xff, 0xff, 0xff};
const Color Color::RED{0xff, 0x00, 0x00};
const Color Color::GREEN{0x00, 0xff, 0x00};
const Color Color::BLUE{0x00, 0x00, 0xff};
const Color Color::BLACK{0x00, 0x00, 0x00};
