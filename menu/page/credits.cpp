#include "../../FEHLCD.h"
#include "../../screen.hpp"

#include "credits.hpp"

namespace menu {

CreditsPage::CreditsPage(const float centerY) : Page{"Credits", centerY} {}

Color CreditsPage::getBackgroundColor() const {
    return Color::BLACK;
}

void CreditsPage::drawContent() const {
    LCD.WriteAt("Credits", 100, 50);
    LCD.WriteAt("Solomon Blair", 20, 80);
    LCD.WriteAt("Will Blankemeyer", 20, 100);
    LCD.WriteAt("Based on Peggle <3", 80, 130);
}

} // namespace menu
