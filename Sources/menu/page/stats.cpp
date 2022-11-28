#include <menu.hpp>

#include <FEHLCD.hpp>

namespace menu {

StatsPage::StatsPage(const float centerY)
: PageWithBackButton{Page("Stats", centerY, ui::Background(Color::BLACK))}
{}

void StatsPage::drawContent() const {
    LCD.WriteAt("Lifetime Stats", 100, 30);

    LCD.WriteAt("Total Score:     0", 15, 70);
    LCD.WriteAt("Top Score:       0", 15, 90);
    LCD.WriteAt("Orange Pegs Hit: 0", 15, 110);
    LCD.WriteAt("Balls Shot:      0", 15, 130);
}

} // namespace menu
