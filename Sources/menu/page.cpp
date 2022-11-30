#include <menu.hpp>

#include <screen.hpp>

namespace menu {

Page::Page(const std::string name, const float centerY)
:   runButton{
        ui::Label(
            Position(static_cast<float>(Screen::CENTER_X), centerY),
            name,
            Color::WHITE
        ),
        Color::RED
    }
{}

Page::~Page() {}

const ui::Button &Page::getRunButton() const {
    return this->runButton;
}

void Page::run() {}

PageWithBackButton::PageWithBackButton(const Page page, const ui::BackgroundView background)
:   Page{page},
    background{background},
    backButton{
        ui::Label(Position(50.f, 15.f), "Back", Color::WHITE),
        Color::BLUE
    }
{}

PageWithBackButton::~PageWithBackButton() {}

const ui::Button &PageWithBackButton::getBackButton() const {
    return this->backButton;
}

void PageWithBackButton::run() {
    this->draw(ui::Button::drawUnpressed);

    while (true) {
        switch (this->step()) {
            case StepResult::RedrawAndContinue:
                this->draw(ui::Button::drawUnpressed);
            case StepResult::Continue:
                break;
            case StepResult::Return:
                return;
        }

        if (this->backButton.isPressed()) {
            this->backButton.drawPressed();
            LCD.Update();

            while (this->backButton.isPressed()) {
                switch (this->step()) {
                    case StepResult::RedrawAndContinue:
                        this->draw(ui::Button::drawPressed);
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

void PageWithBackButton::draw(std::function<void(const ui::Button *)> drawButton) const {
    this->getBackground().draw();
    drawButton(&this->backButton);
    this->drawContent();

    LCD.Update();
}

void PageWithBackButton::drawContent() const {}

PageWithBackButton::StepResult PageWithBackButton::step() {
    return StepResult::Continue;
}

ui::BackgroundView &PageWithBackButton::getBackground() {
    return this->background;
}

const ui::BackgroundView &PageWithBackButton::getBackground() const {
    return this->background;
}

} // namespace menu
