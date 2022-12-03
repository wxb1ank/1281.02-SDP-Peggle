#include <menu.hpp>

#include <FEHLCD.hpp>
#include <game.hpp>

#include <FEHRandom.h>
#include <FEHUtility.h>

#include <algorithm>

namespace menu {

LevelPage::LevelPage(const std::string name, const float centerY, const Level level)
:   Page{name, centerY, Color::RED}, level{level}
{}

std::string getRandomWinMessage() {
    switch (Random.RandInt() % 3) {
        case 0:
            return "Congratulations, you win!";
        case 1:
            return "Nice job!";
        case 2:
            return "Way to go!";
    }
}

std::string getRandomLoseMessage() {
    switch (Random.RandInt() % 3) {
        case 0:
            return "Bjorn looks down\nupon you...";
        case 1:
            return "Better luck next time.";
        default:
            return "You've been peggled.";
    }
}

void LevelPage::run(game::Statistics &stats) {
    auto pegsToPlace = this->level.pegPositions.size();
    auto orangePegsToPlace = std::min(this->level.orangePegCount, pegsToPlace);

    game::PegBoard board{};
    for (auto pegPos : this->level.pegPositions) {
        int color;

        if((Random.RandInt()%pegsToPlace) * 1. / pegsToPlace < orangePegsToPlace * 1. / pegsToPlace)
        {
            color = 1;
            orangePegsToPlace -= 1;
        }
        else{
            color = 0;
        }
        board.push(game::Peg(pegPos.x, pegPos.y, this->level.pegRadius, color));
        pegsToPlace -= 1;
    }

    const auto result = Game().run(stats, board);
    ui::BackgroundView(Color::BLUE).draw();

    switch (result) {
        case Game::Result::Win:
            ui::MultilineLabel(Screen::CENTER, getRandomWinMessage(), Color::GREEN).draw();
            break;
        case Game::Result::Loss:
            ui::MultilineLabel(Screen::CENTER, getRandomLoseMessage(), Color::RED).draw();
            break;
    }

    LCD.Update();
    Sleep(5.f);
}

} // namespace menu
