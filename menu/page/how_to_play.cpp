#include <FEHLCD.h>

#include "../../screen.hpp"

#include "how_to_play.hpp"

namespace menu {

HowToPlayPage::HowToPlayPage(const float centerY) : Page{"How to Play", centerY} {}

void HowToPlayPage::step() {
    LCD.Clear();
    LCD.WriteAt("How to Play", 100, 50);
}

} // namespace menu
