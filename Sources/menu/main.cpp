#include <menu.hpp>

#include <FEHLCD.hpp>
#include <screen.hpp>

#include <optional>
#include <utility>

namespace menu {

MainMenu::MainMenu()
:   Menu(), title{ui::Label(TITLE_POSITION, "Peggle!", Color::WHITE)}, background{Color::BLACK}
{
    auto &pages = this->getPages();

    const auto start = TITLE_POSITION.y + 50.f;
    const auto end = static_cast<float>(Screen::BOTTOM) - 50.f;
    const auto spacing = (end - start) / 3.f;

    pages.emplace_back(std::make_unique<LevelMenuPage>(
        start
    ));
    pages.emplace_back(std::make_unique<StatsPage>(
        start + spacing
    ));
    pages.emplace_back(std::make_unique<TutorialPage>(
        end - spacing
    ));
    pages.emplace_back(std::make_unique<CreditsPage>(
        end
    ));
}

ui::Button MainMenu::createRunButton(
    const std::string name,
    const float centerY,
    const Color borderColor
) {
    return ui::Button(
        ui::Label(
            Position(static_cast<float>(Screen::CENTER_X), centerY),
            std::move(name),
            Color::WHITE
        ),
        borderColor,
        Color::BLACK,
        BUTTON_SIZE
    );
}

void MainMenu::drawBackground() {
    this->background.getColor().r += 0.1f;
    this->background.draw();
    this->title.draw();
}

} // namespace menu
