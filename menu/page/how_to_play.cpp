#include "../../FEHLCD.h"
#include "../../screen.hpp"

#include "how_to_play.hpp"

namespace menu {

HowToPlayPage::HowToPlayPage(const float centerY) : Page{"How to Play", centerY} {}

Color HowToPlayPage::getBackgroundColor() const {
    return Color::BLACK;
}

void HowToPlayPage::drawContent() const {
    LCD.WriteAt("How to Play", 100, 30);

    LCD.WriteAt("Tap to shoot the ball.",15, 70);

    LCD.WriteAt("Try to hit all the orange",15, 100);
    LCD.WriteAt("pegs before using",15, 120);
    LCD.WriteAt("all balls.",15, 140);

    LCD.WriteAt("Landing the ball",15,170);
    LCD.WriteAt("in the bucket",15,190);
    LCD.WriteAt("returns the ball to you.",15,210);
}

} // namespace menu
