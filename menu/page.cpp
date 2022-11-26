#include <FEHLCD.h>

#include "page.hpp"

namespace menu {

void Page::run() {
    while (true) {
        this->step();

        this->backButton.draw();
        if (this->backButton.isPressed()) {
            return;
        }

        LCD.Update();
    }
}

} // namespace menu
