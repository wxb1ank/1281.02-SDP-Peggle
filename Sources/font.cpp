#include <font.hpp>

#include <string>

std::size_t Font::getWidthOf(const std::string &s) {
    const auto length = s.length();

    switch (length) {
        case 0:
            return 0;
        case 1:
            return Font::WIDTH;
        default:
            return (
                ((Font::WIDTH + Font::HORI_PADDING) * length)
                // Horizontal padding only applies between characters, so we counted one too many.
                - Font::HORI_PADDING
            );
    };
}
