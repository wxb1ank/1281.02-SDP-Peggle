#include <menu.hpp>

#include <screen.hpp>

namespace menu {

Menu::Menu()
:   title{ui::Label(
        Position(static_cast<float>(Screen::CENTER_X), 10.f),
        "Peggle!",
        Color::WHITE
    )},
    pages{
        std::make_unique<GamePage>(75.f),
        std::make_unique<StatsPage>(125.f),
        std::make_unique<TutorialPage>(175.f),
        std::make_unique<CreditsPage>(225.f)
    },
    background{Color::BLACK}
{}

Menu::~Menu() {}

void Menu::run() {
    this->draw();

    while (true) {
        LCD.Update();

        const auto touch = Position::getCurrentTouch();
        if (touch.has_value()) {
            this->processTouch(*touch);
        }
    }
}

void Menu::draw() {
    this->background.draw();
    this->title.draw();

    for (const auto &page : this->pages) {
        page->getRunButton().draw();
    }
}

void Menu::processTouch(const Position touch) {
    for (auto &page : this->pages) {
        const auto &runButton = page->getRunButton();

        if (runButton.contains(touch)) {
            runButton.drawPressed();

            // Wait until the button is no longer pressed.
            while (runButton.isPressed());

            page->run();
            this->draw();

            return;
        }
    }
}

} // namespace menu
