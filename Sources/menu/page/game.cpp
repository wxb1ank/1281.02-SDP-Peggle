#include <menu.hpp>

#include <FEHLCD.hpp>

namespace menu {

GamePage::GamePage(const float centerY)
:   Page{"Play", centerY}, game{} {}

void GamePage::run(game::Statistics &stats) {
    this->game.run(stats);
}

} // namespace menu
