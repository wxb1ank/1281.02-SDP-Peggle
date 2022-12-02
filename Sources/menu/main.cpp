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
    pages.emplace_back(std::make_unique<LevelMenuPage>(75.f));
    pages.emplace_back(std::make_unique<StatsPage>(125.f));
    pages.emplace_back(std::make_unique<TutorialPage>(175.f));
    pages.emplace_back(std::make_unique<CreditsPage>(225.f));
}

void MainMenu::drawBackground() {
    this->background.getColor().r += 0.1f;
    this->background.draw();
    this->title.draw();
}

} // namespace menu
