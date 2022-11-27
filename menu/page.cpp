#include <FEHLCD.h>

#include "../screen.hpp"

#include "page.hpp"

namespace menu {

Page::Page(const std::string name, const float centerY)
    : runButton{{{static_cast<float>(Screen::CENTER_X), centerY}, name}, {150.f, 22.f}, Color::Red},
      backButton{{{50.f, 15.f}, "Back"}, Color::Blue}
{}

void Page::run() {
    while (true) {
        this->step();

        this->backButton.drawUnpressed();
        if (this->backButton.isPressed()) {
            this->backButton.drawPressed();
            while (this->backButton.isPressed());

            return;
        }

        LCD.Update();
    }
}

} // namespace menu
