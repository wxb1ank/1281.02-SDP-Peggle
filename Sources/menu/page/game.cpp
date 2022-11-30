#include <menu.hpp>

#include <FEHLCD.hpp>

namespace menu {

GamePage::GamePage(const float centerY) : Page{"Play", centerY, ui::BackgroundView(Color::BLACK)} {}

void GamePage::run() {
    this->game.run();
}

} // namespace menu
