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
    background{background}
{}

Page::~Page() {}

const ui::Button &Page::getRunButton() const {
    return this->runButton;
}

void Page::run() {}

ui::Background &Page::getBackground() {
    return this->background;
}

const ui::Background &Page::getBackground() const {
    return this->background;
}

void Page::drawForeground() const {}

PageWithBackButton::PageWithBackButton(const Page page)
:   Page{page},
    backButton{
        ui::Label(Position(50.f, 15.f), "Back", ui::Background(), Color::WHITE),
        ui::Background(Color::BLACK),
        Color::BLUE
    }
{}

PageWithBackButton::~PageWithBackButton() {}

const ui::Button &PageWithBackButton::getBackButton() const {
    return this->backButton;
}

void PageWithBackButton::run() {
    this->draw();

    while (true) {
        LCD.Update();

        switch (this->step()) {
            case StepResult::RedrawAndContinue:
                this->draw();
            case StepResult::Continue:
                break;
            case StepResult::Return:
                return;
        }

        if (this->backButton.isPressed()) {
            this->backButton.drawPressed();

            while (this->backButton.isPressed()) {
                switch (this->step()) {
                    case StepResult::RedrawAndContinue:
                        this->backButton.drawPressed();
                        this->drawContent();
                    case StepResult::Continue:
                        continue;
                    case StepResult::Return:
                        return;
                }
            }

            return;
        }
    }
}

void PageWithBackButton::drawForeground() const {
    this->backButton.draw();
    this->drawContent();
}

void PageWithBackButton::drawContent() const {}

PageWithBackButton::StepResult PageWithBackButton::step() {
    return StepResult::Continue;
}

} // namespace menu
