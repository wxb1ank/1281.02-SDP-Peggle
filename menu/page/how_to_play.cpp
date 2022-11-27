#include "../../FEHLCD.h"
#include "../../screen.hpp"

#include "how_to_play.hpp"

namespace menu {

HowToPlayPage::HowToPlayPage(const float centerY) : Page{"How to Play", centerY} {}

Color HowToPlayPage::getBackgroundColor() const {
    return Color::BLACK;
}

void HowToPlayPage::drawContent() const {
    LCD.WriteAt("How to Play", 100, 50);
}

} // namespace menu
