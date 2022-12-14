#include <menu.hpp>

#include <FEHLCD.hpp>
#include <screen.hpp>

#include <array>
#include <optional>
#include <utility>

namespace menu {

LevelMenu::LevelMenu(const ui::Button &backButton)
:   Menu{},
    title{TITLE_POSITION, "Level Select", Color::WHITE},
    background{Color::BLACK},
    backButton{backButton}
{
    auto &pages = this->getPages();
    for (std::size_t i = 0; i < game::Level::ALL.size(); i++) {
        const auto &level = game::Level::ALL.at(i);

        std::string name;
        if (level.name.has_value()) {
            name = *level.name;
        } else {
            name = std::to_string(1 + i);
        }

        pages.emplace_back(std::make_unique<LevelPage>(
            MainMenu::createRunButton(
                name,
                60.f + (25.f * static_cast<float>(i)),
                Color::BLUEVIOLET
            ),
            level
        ));
    }
}

void LevelMenu::drawBackground() {
    this->background.draw();
    this->title.draw();
    this->backButton.drawUnpressed();
}

} // namespace menu
