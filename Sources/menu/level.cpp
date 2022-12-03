#include <menu.hpp>

#include <FEHLCD.hpp>
#include <screen.hpp>

#include <array>
#include <optional>
#include <sstream>
#include <utility>

namespace menu {

LevelMenu::LevelMenu()
:   Menu(), title{TITLE_POSITION, "Level Select", Color::WHITE}, background{Color::BLACK}
{
    auto &pages = this->getPages();
    for (unsigned i = 0; i < LEVELS.size(); i++) {
        const auto &level = LEVELS.at(i);

        std::string name;
        if (level.name.has_value()) {
            name = *level.name;
        } else {
            std::stringstream stream{};
            stream << 1 + i;

            name = stream.str();
        }

        pages.emplace_back(std::make_unique<LevelPage>(
            name,
            60.f + (20.f * static_cast<float>(i)),
            level
        ));
    }
}

void LevelMenu::drawBackground() {
    this->title.draw();
}

} // namespace menu
