#include "../../FEHLCD.h"
#include "../../screen.hpp"

#include "stats.hpp"

namespace menu {

StatsPage::StatsPage(const float centerY) : Page{"Stats", centerY} {}

Color StatsPage::getBackgroundColor() const {
    return Color::BLACK;
}

void StatsPage::drawContent() const {
    LCD.WriteAt("Lifetime Stats", 100, 30);

    LCD.WriteAt("Total Score:     0", 15, 70);
    LCD.WriteAt("Top Score:       0", 15, 90);
    LCD.WriteAt("Orange Pegs Hit: 0", 15, 110);
    LCD.WriteAt("Balls Shot:      0", 15, 130);
}

} // namespace menu
