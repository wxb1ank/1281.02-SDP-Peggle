#include <menu.hpp>

#include <FEHLCD.hpp>

namespace menu {

GamePage::GamePage(const float centerY) : Page{"Play", centerY, ui::Background(Color::BLACK)} {}

void GamePage::drawContent() const {}

Page::StepResult GamePage::step() {
    this->game.step();

    return Page::StepResult::RedrawAndContinue;
}

} // namespace menu
