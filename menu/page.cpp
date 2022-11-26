#include <FEHLCD.h>

#include "../screen.hpp"

#include "page.hpp"

namespace menu {

Page::Page(const std::string name, const float centerY)
    : runButton{name, {static_cast<float>(Screen::CENTER_X), centerY}, {150.f, 22.f}},
      backButton{"Back", {50.f, 15.f}}
{}

void Page::run() {
    while (true) {
        this->step();

        this->backButton.drawUnpressed();
        if (this->backButton.isPressed()) {
            return;
        }

        LCD.Update();
    }
}

} // namespace menu
