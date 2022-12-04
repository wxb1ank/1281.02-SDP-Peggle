#include <menu.hpp>

#include <FEHLCD.hpp>

#include <FEHRandom.h>
#include <FEHUtility.h>

namespace menu {

LevelPage::LevelPage(const ui::Button runButton, const game::Level level)
:   Page{runButton}, level{level}
{}

std::string getRandomWinMessage() {
    switch (Random.RandInt() % 3) {
        case 0:
            return "Congratulations, you win!";
        case 1:
            return "Nice job!";
        case 2:
        default:
            return "Way to go!";
    }
}

std::string getRandomLoseMessage() {
    switch (Random.RandInt() % 3) {
        case 0:
            return "Bjorn looks down\nupon you...";
        case 1:
            return "Better luck next time.";
        case 2:
        default:
            return "You've been peggled.";
    }
}

void LevelPage::run(game::Statistics &stats) {
    const auto result = Game().play(stats, this->level);
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
