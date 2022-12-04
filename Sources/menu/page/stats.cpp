#include <menu.hpp>

#include <FEHLCD.hpp>

#include <sstream>

namespace menu {

StatsPage::StatsPage(const float centerY)
:   PageWithBackButton{Page(MainMenu::createRunButton("Stats", centerY, Color::YELLOW))}
{}

void StatsPage::run(game::Statistics &stats) {
    ui::BackgroundView(Color::BLACK).draw();
    ui::MultilineLabel(TITLE_POSITION, "Lifetime\nStatistics", Color::SILVER).draw();

    std::stringstream content{};
    content << "Wins:            " << stats.getWins() << '\n';
    content << "Total Score:     " << stats.getTotalScore() << '\n';
    content << "Top Score:       " << stats.getTopScore() << '\n';
    content << "Orange Pegs Hit: " << stats.getOrangePegsHit() << '\n';
    content << "Balls Shot:      " << stats.getBallsShot();
    ui::MultilineLabel(Screen::CENTER, content.str(), Color::WHITE).draw();

    while (!this->shouldReturnFromRun());
}

} // namespace menu
