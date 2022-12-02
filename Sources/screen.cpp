#include <screen.hpp>

#include <cmath>

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
:   r{static_cast<float>(r)}, g{static_cast<float>(g)}, b{static_cast<float>(b)}
{}

const Color Color::WHITE{0xff, 0xff, 0xff};
const Color Color::RED{0xff, 0x00, 0x00};
const Color Color::GREEN{0x00, 0xff, 0x00};
const Color Color::BLUE{0x00, 0x00, 0xff};
const Color Color::BLACK{0x00, 0x00, 0x00};

unsigned Color::encode() const {
    return (static_cast<unsigned>(this->r) << 16) |
           (static_cast<unsigned>(this->g) << 8) |
            static_cast<unsigned>(this->b);
}

float Color::getValue() const {
    // return std::max({this->r, this->g, this->b});
    return 0.f;
}

float Color::getChroma() const {
    return this->getValue() - this->getMinComp();
}

float Color::getHue() const {
    // See: <https://en.wikipedia.org/wiki/Hue#Defining_hue_in_terms_of_RGB>.
    return std::atan2(std::sqrt(3.f) * (this->g - this->b), (2.f * this->r) - this->g - this->b);
}

float Color::getMinComp() const {
    // return std::min({this->r, this->g, this->b});
    return 0.f;
}
