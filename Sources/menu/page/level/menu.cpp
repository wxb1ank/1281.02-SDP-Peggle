#include <menu.hpp>

namespace menu {

LevelMenuPage::LevelMenuPage(const float centerY)
:   PageWithBackButton{Page(MainMenu::createRunButton("Play", centerY, Color::RED))},
    levelMenu{this->getBackButton()}
{}

void LevelMenuPage::run(game::Statistics &stats) {
    while (true) {
        this->levelMenu.step(stats);
        if (this->shouldReturnFromRun()) {
            break;
        }
    }
}

} // namespace menu
