#include <game.hpp>

#include <cassert>
#include <cstdio>

namespace game {

/// \author Solomon Blair
/// \author Will Blankemeyer
static const std::string AMOGUSALIVE{
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

/// \author Solomon Blair
/// \author Will Blankemeyer
static const std::string AMOGUSDEAD{
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

    const auto  initialXPosition = 20.f;
    const auto  initialYPosition = 30.f;
    level.pegRadius = 5.f;

    level.addPegBitmap(Position(initialXPosition, initialYPosition), AMOGUSALIVE);
    level.addPegBitmap(Position(initialXPosition + 160, initialYPosition), AMOGUSDEAD);

    return level;
}

} // namespace game
