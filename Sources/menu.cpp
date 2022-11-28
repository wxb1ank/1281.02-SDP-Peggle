#include <menu.hpp>

#include <screen.hpp>

namespace menu {

Menu::Menu()
:   title{ui::Label(
        Position(static_cast<float>(Screen::CENTER_X), 10.f),
        "Peggle!",
        ui::Background(),
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
    while (true) {
        LCD.Update();
        this->draw();
        this->processInput();
    }
}

ui::Background &Menu::getBackground() {
    return this->background;
}

const ui::Background &Menu::getBackground() const {
    return this->background;
}

void Menu::drawForeground() const {
    this->title.draw();

    for (const auto &page : this->pages) {
        page->getRunButton().drawUnpressed();
    }
}

void Menu::processInput() {
    // Wait until the next touch.
    const auto touch = Position::getNextTouch();

    for (auto &page : this->pages) {
        const auto &runButton = page->getRunButton();

        if (runButton.contains(touch)) {
            runButton.drawPressed();

            // Wait until the button is no longer pressed.
            while (runButton.isPressed());

            page->run();

            return;
        }
    }
}

} // namespace menu
