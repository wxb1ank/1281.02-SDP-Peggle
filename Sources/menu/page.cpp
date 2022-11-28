#include <menu.hpp>

#include <screen.hpp>

namespace menu {

Page::Page(const std::string name, const float centerY, const ui::Background background)
:   runButton{
        ui::Label(
            Position(static_cast<float>(Screen::CENTER_X), centerY),
            name,
            ui::Background(),
            Color::WHITE
        ),
        ui::Background(Color::BLACK),
        Color::RED
    },
    backButton{
        ui::Label(Position(50.f, 15.f), "Back", ui::Background(), Color::WHITE),
        ui::Background(Color::BLACK),
        Color::BLUE
    },
    background{background}
{}

Page::~Page() {}

const ui::Button &Page::getRunButton() const {
    return this->runButton;
}

const ui::Button &Page::getBackButton() const {
    return this->backButton;
}

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

ui::Background &Page::getBackground() {
    return this->background;
}

const ui::Background &Page::getBackground() const {
    return this->background;
}

void Page::drawForeground() const {
    this->backButton.draw();
    this->drawContent();
}

} // namespace menu
