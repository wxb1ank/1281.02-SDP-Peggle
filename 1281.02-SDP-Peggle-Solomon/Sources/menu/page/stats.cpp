#include <menu.hpp>

#include <FEHLCD.hpp>

namespace menu {

StatsPage::StatsPage(const float centerY)
: PageWithBackButton{Page("Stats", centerY), ui::BackgroundView(Color::BLACK)}
{}

StatsPage::StepResult StatsPage::step(game::Statistics &stats) {
    LCD.WriteAt("Lifetime Stats", 100, 30);

    LCD.WriteAt("Total Score:", 15, 70);
    LCD.WriteAt("Top Score:", 15, 90);
    LCD.WriteAt("Orange Pegs Hit:", 15, 110);
    LCD.WriteAt("Balls Shot:", 15, 130);

    LCD.WriteAt(static_cast<int>(stats.getTotalScore()), 250, 70);
    LCD.WriteAt(static_cast<int>(stats.getTopScore()), 250, 90);
    LCD.WriteAt(static_cast<int>(stats.getOrangePegsHit()), 250, 110);
    LCD.WriteAt(static_cast<int>(stats.getBallsShot()), 250, 130);

    return StepResult::Continue;
}

} // namespace menu
