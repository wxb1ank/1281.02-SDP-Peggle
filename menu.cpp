#include <FEHLCD.h>

#include "mechanics.hpp"

#include "menu.hpp"

namespace menu {

void Menu::run() {
    while (true) {
        LCD.SetBackgroundColor(FEHLCD::FEHLCDColor::Black);
        LCD.Clear();
        this->draw();
        this->step();
        LCD.Update();
    }
}

void Menu::draw() const {
    for (const auto page : this->pages) {
        page->getRunButton().draw();
    }
}

void Menu::step() {
    const auto touch = Position::touch();

    for (auto page : this->pages) {
        const auto &runButton = page->getRunButton();

        if (runButton.isPressed(touch)) {
            // Wait until the button is no longer pressed.
            while (runButton.isPressed());

            page->run();

            return;
        }
    }
}

} // namespace menu
