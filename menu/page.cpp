#include "../FEHLCD.h"
#include "../screen.hpp"

#include "page.hpp"

namespace menu {

Page::Page(const std::string name, const float centerY)
:   runButton{
        {{static_cast<float>(Screen::CENTER_X), centerY}, name, Color::WHITE},
        {150.f, 22.f},
        Color::BLACK,
        Color::RED
    },
    backButton{{{50.f, 15.f}, "Back", Color::WHITE}, Color::BLACK, Color::BLUE}
{}

Page::~Page() {}

void Page::run() {
    this->draw();

    while (true) {
        LCD.Update();

        switch (this->step()) {
            case Page::StepResult::RedrawAndContinue:
                this->draw();
            case Page::StepResult::Continue:
                break;
            case Page::StepResult::Return:
                return;
        }

        if (this->backButton.isPressed()) {
            this->backButton.drawPressed();

            while (this->backButton.isPressed()) {
                switch (this->step()) {
                    case Page::StepResult::RedrawAndContinue:
                        this->backButton.drawPressed();
                        this->drawContent();
                    case Page::StepResult::Continue:
                        continue;
                    case Page::StepResult::Return:
                        return;
                }
            }

            return;
        }
    }
}

void Page::drawForeground() const {
    this->backButton.draw();
    this->drawContent();
}

float Page::getWidth() const {
    return static_cast<float>(Screen::WIDTH);
}

float Page::getHeight() const {
    return static_cast<float>(Screen::WIDTH);
}

Position Page::getCenter() const {
    return Screen::CENTER;
}

} // namespace menu
