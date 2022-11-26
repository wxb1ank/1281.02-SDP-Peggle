#include "font.hpp"

std::size_t Font::widthOf(const std::string &s) {
    return Font::WIDTH * s.length();
}
