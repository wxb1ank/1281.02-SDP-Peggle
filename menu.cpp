#include <FEHLCD.h>

#include "mechanics.hpp"
#include "screen.hpp"

#include "menu.hpp"

namespace menu {

Menu::Menu()
:   pages{
        std::make_unique<GamePage>(75.),
        std::make_unique<HowToPlayPage>(150.),
        std::make_unique<CreditsPage>(225.)
    }
{}

void Menu::run() {
    while (true) {
        this->draw();
        this->processInput();
    }
}

void Menu::draw() const {
    LCD.Update();
    LCD.Clear(Color::Black);

    for (const auto &page : this->pages) {
        page->getRunButton().drawUnpressed();
    }
}

void Menu::processInput() {
    // Wait until the next touch.
    const auto touch = Position::nextTouch();

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
