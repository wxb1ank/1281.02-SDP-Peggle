#include <menu.hpp>

#include <FEHLCD.hpp>

namespace menu {

CreditsPage::CreditsPage(const float centerY)
:   PageWithBackButton{Page("Credits", centerY), ui::BackgroundView(Color::BLACK)}
{}

CreditsPage::StepResult CreditsPage::step(game::Statistics &) {
    LCD.WriteAt("Credits", 100, 50);

    LCD.WriteAt("Solomon Blair", 20, 80);
    LCD.WriteAt("Will Blankemeyer", 20, 100);
    LCD.WriteAt("Based on Peggle <3", 80, 130);

    return StepResult::Continue;
}

} // namespace menu