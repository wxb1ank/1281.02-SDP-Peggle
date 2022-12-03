#include <menu.hpp>

namespace menu {

LevelMenuPage::LevelMenuPage(const float centerY)
:   PageWithBackButton{Page("Play", centerY, Color::RED), Color::BLACK}, levelMenu{}
{}

LevelMenuPage::StepResult LevelMenuPage::step(game::Statistics &stats) {
    this->levelMenu.step(stats);

    return StepResult::RedrawAndContinue;
}

} // namespace menu
