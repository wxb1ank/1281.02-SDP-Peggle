#include <FEHLCD.h>

#include "../screen.hpp"

#include "page.hpp"

namespace menu {

Page::Page(const std::string name, const float centerY)
    : runButton{{{static_cast<float>(Screen::CENTER_X), centerY}, name}, {150.f, 22.f}},
      backButton{{{50.f, 15.f}, "Back"}}
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
