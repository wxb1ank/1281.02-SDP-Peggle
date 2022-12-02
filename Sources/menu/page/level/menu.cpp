#include <menu.hpp>

namespace menu {

LevelMenuPage::LevelMenuPage(const float centerY) : Page{"Play", centerY} {}

void LevelMenuPage::run(game::Statistics &stats) {
    LevelMenu().run(stats);
}

} // namespace menu
