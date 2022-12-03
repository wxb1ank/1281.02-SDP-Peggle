#include <menu.hpp>

#include <cassert>
#include <cstdio>

namespace menu {

static const char AMOGUSALIVE[]{
    "000000111111\n"
    "0000010000001\n"
    "00001000000001\n"
    "00010000111111\n"
    "000100010000001\n"
    "0001001000000001\n"
    "0111001000000001\n"
    "1001001000000001\n"
    "100100010000001\n"
    "100100001111111\n"
    "100100000000001\n"
    "100100000000001\n"
    "100100000000001\n"
    "100100000000001\n"
    "100100000000001\n"
    "011100000000001\n"
    "000100011110001\n"
    "000100010010001\n"
    "000100010010001\n"
    "000011100001110"
};

static const char AMOGUSDEAD[]{
    "\n"
    "\n"
    "\n"
    "\n"
    "\n"
    "00011011\n"
    "001101011\n"
    "001000001\n"
    "00010001\n"
    "001110111\n"
    "0100101001111\n"
    "10110001101001\n"
    "10000000001001\n"
    "10000000001001\n"
    "10000000001001\n"
    "10000000001001\n"
    "10000000001110\n"
    "10011110001000\n"
    "10010001001000\n"
    "01100000110000\n"
};

Level Level::amogus()  {
    Level level{};
    level.name = "amogus";

    int radius = 5;
    int initialXPosition = 20;
    int initialYPosition = 30;
    level.pegRadius = radius;

    drawPixelArt(radius, initialXPosition,initialYPosition,level,AMOGUSALIVE,sizeof(AMOGUSALIVE));
    drawPixelArt(radius, initialXPosition + 160, initialYPosition, level, AMOGUSDEAD, sizeof(AMOGUSDEAD));

    return level;
};

} // namespace menu
