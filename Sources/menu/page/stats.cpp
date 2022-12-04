#include <menu.hpp>

#include <FEHLCD.hpp>

namespace menu {

StatsPage::StatsPage(const float centerY)
:   PageWithBackButton{Page(MainMenu::createRunButton("Stats", centerY, Color::YELLOW))}
{}

void StatsPage::run(game::Statistics &stats) {
    ui::BackgroundView(Color::BLACK).draw();
    ui::MultilineLabel(TITLE_POSITION, "Lifetime\nStatistics", Color::SILVER).draw();

    const auto statLabels = ui::MultilineLabel(
        Position(static_cast<float>(Screen::CENTER_X) - 40.f, static_cast<float>(Screen::CENTER_Y)),
        "Total Wins:\n"
        "Total Score:\n"
        "Top Score:\n"
        "Orange Pegs Hit:\n"
        "Balls Shot:",
        Color::WHITE
    );
    statLabels.draw();

    // TODO
    LCD.WriteAt(static_cast<int>(stats.getWins()), 250, 50);
    LCD.WriteAt(static_cast<int>(stats.getTotalScore()), 250, 70);
    LCD.WriteAt(static_cast<int>(stats.getTopScore()), 250, 90);
    LCD.WriteAt(static_cast<int>(stats.getOrangePegsHit()), 250, 110);
    LCD.WriteAt(static_cast<int>(stats.getBallsShot()), 250, 130);

    while (!this->shouldReturnFromRun());
}

} // namespace menu
