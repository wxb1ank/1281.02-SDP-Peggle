#include <menu.hpp>

#include <FEHLCD.hpp>
#include <game/level.hpp>
#include <screen.hpp>

#include <optional>
#include <utility>

namespace menu {

LevelMenu::LevelMenu()
:   Menu(),
    title{
        Position(static_cast<float>(Screen::CENTER_X), 10.f),
        "Level Select",
        Color::WHITE
    },
    background{Color::BLACK}
{
    auto &pages = this->getPages();
    pages.emplace_back(std::make_unique<LevelPage>("Level 1", 100.f, game::level::make1));
    pages.emplace_back(std::make_unique<LevelPage>("Level 2", 160.f, game::level::make2));
    pages.emplace_back(std::make_unique<LevelPage>("Level 3", 220.f, game::level::make3));
}

void LevelMenu::drawBackground() {
    this->background.draw();
    this->title.draw();
}

} // namespace menu
