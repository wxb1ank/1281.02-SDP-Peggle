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
}

} // namespace menu
