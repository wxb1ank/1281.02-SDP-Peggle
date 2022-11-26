#include <FEHLCD.h>

#include "mechanics.hpp"

#include "menu.hpp"

namespace menu {

Menu::Menu() : pages{&this->gamePage, &this->howToPlayPage, &this->creditsPage} {}

void Menu::run() {
    while (true) {
        this->draw();
        this->step();
    }
}

void Menu::draw() const {
    LCD.Update();
    LCD.SetBackgroundColor(FEHLCD::FEHLCDColor::Black);
    LCD.Clear();

    for (const auto *page : this->pages) {
        page->getRunButton().drawUnpressed();
    }
}

void Menu::step() {
    const auto touch = Position::nextTouch();

    for (auto *page : this->pages) {
        const auto &runButton = page->getRunButton();

        if (runButton.isPressed(touch)) {
            runButton.drawPressed();

            // Wait until the button is no longer pressed.
            while (runButton.isPressed());

            page->run();

            return;
        }
    }
}

} // namespace menu
