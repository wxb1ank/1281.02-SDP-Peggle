#include <FEHLCD.h>

#include "../../screen.hpp"

#include "credits.hpp"

namespace menu {

CreditsPage::CreditsPage(const float centerY) : Page{"Credits", centerY} {}

void CreditsPage::step() {
    LCD.Clear();
    LCD.WriteAt("Credits", 100, 50);
}

} // namespace menu
