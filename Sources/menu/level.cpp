#include <menu.hpp>

#include <FEHLCD.hpp>
#include <screen.hpp>

#include <optional>
#include <utility>

namespace menu {

LevelMenu::LevelMenu()
:   Menu(), title{TITLE_POSITION, "Level Select", Color::WHITE}, background{Color::BLACK}
{
    auto &pages = this->getPages();
    pages.emplace_back(std::make_unique<Level1Page>(100.f));
    pages.emplace_back(std::make_unique<Level2Page>(160.f));
    pages.emplace_back(std::make_unique<Level3Page>(220.f));
}

void LevelMenu::drawBackground() {
    this->background.draw();
    this->title.draw();
}

} // namespace menu
