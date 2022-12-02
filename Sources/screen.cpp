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

Color::Color(const unsigned rgb)
: Color(static_cast<char>(rgb >> 16), static_cast<char>(rgb >> 8), static_cast<char>(rgb))
{}

Color::Color(const unsigned char r, const unsigned char g, const unsigned char b)
:   r{static_cast<float>(r)}, g{static_cast<float>(g)}, b{static_cast<float>(b)}
{}

unsigned Color::encode() const {
    return (static_cast<unsigned>(this->r) << 16) |
           (static_cast<unsigned>(this->g) << 8) |
            static_cast<unsigned>(this->b);
}

float Color::getValue() const {
    // I'm having difficulty passing an initializer list of three floats to `std::max`, so I've
    // broken it into two calls.
    return std::max(std::max(this->r, this->g), this->b);
}

float Color::getChroma() const {
    return this->getValue() - this->getMinComp();
}

float Color::getHue() const {
    // Source: <https://en.wikipedia.org/wiki/Hue#Defining_hue_in_terms_of_RGB>.
    return std::atan2(std::sqrt(3.f) * (this->g - this->b), (2.f * this->r) - this->g - this->b);
}

float Color::getMinComp() const {
    // See `Color::getValue`.
    return std::min(std::min(this->r, this->g), this->b);
}

const Color Color::BLACK{0x000000u};
const Color Color::NAVY{0x000080u};
const Color Color::DARKBLUE{0x00008Bu};
const Color Color::MEDIUMBLUE{0x0000CDu};
const Color Color::BLUE{0x0000FFu};
const Color Color::DARKGREEN{0x006400u};
const Color Color::GREEN{0x008000u};
const Color Color::TEAL{0x008080u};
const Color Color::DARKCYAN{0x008B8Bu};
const Color Color::DEEPSKYBLUE{0x00BFFFu};
const Color Color::DARKTURQUOISE{0x00CED1u};
const Color Color::MEDIUMSPRINGGREEN{0x00FA9Au};
const Color Color::LIME{0x00FF00u};
const Color Color::SPRINGGREEN{0x00FF7Fu};
const Color Color::AQUA{0x00FFFFu};
const Color Color::CYAN{0x00FFFFu};
const Color Color::MIDNIGHTBLUE{0x191970u};
const Color Color::DODGERBLUE{0x1E90FFu};
const Color Color::LIGHTSEAGREEN{0x20B2AAu};
const Color Color::FORESTGREEN{0x228B22u};
const Color Color::SEAGREEN{0x2E8B57u};
const Color Color::DARKSLATEGRAY{0x2F4F4Fu};
const Color Color::LIMEGREEN{0x32CD32u};
const Color Color::MEDIUMSEAGREEN{0x3CB371u};
const Color Color::TURQUOISE{0x40E0D0u};
const Color Color::ROYALBLUE{0x4169E1u};
const Color Color::STEELBLUE{0x4682B4u};
const Color Color::DARKSLATEBLUE{0x483D8Bu};
const Color Color::MEDIUMTURQUOISE{0x48D1CCu};
const Color Color::INDIGO{0x4B0082u};
const Color Color::DARKOLIVEGREEN{0x556B2Fu};
const Color Color::CADETBLUE{0x5F9EA0u};
const Color Color::CORNFLOWERBLUE{0x6495EDu};
const Color Color::GRAY{0x666666u};
const Color Color::MEDIUMAQUAMARINE{0x66CDAAu};
const Color Color::DIMGRAY{0x696969u};
const Color Color::SLATEBLUE{0x6A5ACDu};
const Color Color::OLIVEDRAB{0x6B8E23u};
const Color Color::SLATEGRAY{0x708090u};
const Color Color::LIGHTSLATEGRAY{0x778899u};
const Color Color::MEDIUMSLATEBLUE{0x7B68EEu};
const Color Color::LAWNGREEN{0x7CFC00u};
const Color Color::CHARTREUSE{0x7FFF00u};
const Color Color::AQUAMARINE{0x7FFFD4u};
const Color Color::MAROON{0x800000u};
const Color Color::PURPLE{0x800080u};
const Color Color::OLIVE{0x808000u};
const Color Color::SKYBLUE{0x87CEEBu};
const Color Color::LIGHTSKYBLUE{0x87CEFAu};
const Color Color::BLUEVIOLET{0x8A2BE2u};
const Color Color::DARKRED{0x8B0000u};
const Color Color::DARKMAGENTA{0x8B008Bu};
const Color Color::SADDLEBROWN{0x8B4513u};
const Color Color::DARKSEAGREEN{0x8FBC8Fu};
const Color Color::LIGHTGREEN{0x90EE90u};
const Color Color::MEDIUMPURPLE{0x9370DBu};
const Color Color::DARKVIOLET{0x9400D3u};
const Color Color::PALEGREEN{0x98FB98u};
const Color Color::DARKORCHID{0x9932CCu};
const Color Color::YELLOWGREEN{0x9ACD32u};
const Color Color::SIENNA{0xA0522Du};
const Color Color::BROWN{0xA52A2Au};
const Color Color::DARKGRAY{0xA9A9A9u};
const Color Color::LIGHTBLUE{0xADD8E6u};
const Color Color::GREENYELLOW{0xADFF2Fu};
const Color Color::PALETURQUOISE{0xAFEEEEu};
const Color Color::LIGHTSTEELBLUE{0xB0C4DEu};
const Color Color::POWDERBLUE{0xB0E0E6u};
const Color Color::FIREBRICK{0xB22222u};
const Color Color::DARKGOLDENROD{0xB8860Bu};
const Color Color::MEDIUMORCHID{0xBA55D3u};
const Color Color::SCARLET{0xBB0000u};
const Color Color::ROSYBROWN{0xBC8F8Fu};
const Color Color::DARKKHAKI{0xBDB76Bu};
const Color Color::SILVER{0xC0C0C0u};
const Color Color::MEDIUMVIOLETRED{0xC71585u};
const Color Color::INDIANRED{0xCD5C5Cu};
const Color Color::PERU{0xCD853Fu};
const Color Color::CHOCOLATE{0xD2691Eu};
const Color Color::TAN{0xD2B48Cu};
const Color Color::LIGHTGRAY{0xD3D3D3u};
const Color Color::THISTLE{0xD8BFD8u};
const Color Color::ORCHID{0xDA70D6u};
const Color Color::GOLDENROD{0xDAA520u};
const Color Color::PALEVIOLETRED{0xDB7093u};
const Color Color::CRIMSON{0xDC143Cu};
const Color Color::GAINSBORO{0xDCDCDCu};
const Color Color::PLUM{0xDDA0DDu};
const Color Color::BURLYWOOD{0xDEB887u};
const Color Color::LIGHTCYAN{0xE0FFFFu};
const Color Color::LAVENDER{0xE6E6FAu};
const Color Color::DARKSALMON{0xE9967Au};
const Color Color::VIOLET{0xEE82EEu};
const Color Color::PALEGOLDENROD{0xEEE8AAu};
const Color Color::LIGHTCORAL{0xF08080u};
const Color Color::KHAKI{0xF0E68Cu};
const Color Color::ALICEBLUE{0xF0F8FFu};
const Color Color::HONEYDEW{0xF0FFF0u};
const Color Color::AZURE{0xF0FFFFu};
const Color Color::SANDYBROWN{0xF4A460u};
const Color Color::WHEAT{0xF5DEB3u};
const Color Color::BEIGE{0xF5F5DCu};
const Color Color::WHITESMOKE{0xF5F5F5u};
const Color Color::MINTCREAM{0xF5FFFAu};
const Color Color::GHOSTWHITE{0xF8F8FFu};
const Color Color::SALMON{0xFA8072u};
const Color Color::ANTIQUEWHITE{0xFAEBD7u};
const Color Color::LINEN{0xFAF0E6u};
const Color Color::LIGHTGOLDENRODYELLOW{0xFAFAD2u};
const Color Color::OLDLACE{0xFDF5E6u};
const Color Color::RED{0xFF0000u};
const Color Color::FUCHSIA{0xFF0080u};
const Color Color::MAGENTA{0xFF00FFu};
const Color Color::DEEPPINK{0xFF1493u};
const Color Color::ORANGERED{0xFF4500u};
const Color Color::TOMATO{0xFF6347u};
const Color Color::HOTPINK{0xFF69B4u};
const Color Color::CORAL{0xFF7F50u};
const Color Color::DARKORANGE{0xFF8C00u};
const Color Color::LIGHTSALMON{0xFFA07Au};
const Color Color::ORANGE{0xFFA500u};
const Color Color::LIGHTPINK{0xFFB6C1u};
const Color Color::PINK{0xFFC0CBu};
const Color Color::GOLD{0xFFD700u};
const Color Color::PEACHPUFF{0xFFDAB9u};
const Color Color::NAVAJOWHITE{0xFFDEADu};
const Color Color::MOCCASIN{0xFFE4B5u};
const Color Color::BISQUE{0xFFE4C4u};
const Color Color::MISTYROSE{0xFFE4E1u};
const Color Color::BLANCHEDALMOND{0xFFEBCDu};
const Color Color::PAPAYAWHIP{0xFFEFD5u};
const Color Color::LAVENDERBLUSH{0xFFF0F5u};
const Color Color::SEASHELL{0xFFF5EEu};
const Color Color::CORNSILK{0xFFF8DCu};
const Color Color::LEMONCHIFFON{0xFFFACDu};
const Color Color::FLORALWHITE{0xFFFAF0u};
const Color Color::SNOW{0xFFFAFAu};
const Color Color::YELLOW{0xFFFF00u};
const Color Color::LIGHTYELLOW{0xFFFFE0u};
const Color Color::IVORY{0xFFFFF0u};
const Color Color::WHITE{0xFFFFFFu};
