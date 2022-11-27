#include <cstdlib>

#include "FEHLCD.h"
#include "mechanics.hpp"
#include "screen.hpp"

#include "menu.hpp"

namespace menu {

StackedLabel::StackedLabel(
    const Position center,
    const std::string content,
    const Color backgroundColor,
    const Color fontColor
) : Label{center, content, backgroundColor, fontColor} {}

StackedLabel::StackedLabel(
    const Position center,
    const std::string content,
    const Color fontColor
) : Label{center, content, fontColor} {}

StackedLabel::~StackedLabel() {}

void StackedLabel::drawForeground() const {
    LCD.SetFontColor(this->getFontColor().encode());
    for (std::size_t i = 0; i < 3; i++) {
        const auto offset = static_cast<float>(i);
        LCD.WriteAt(
            this->getContent().c_str(),
            static_cast<int>(this->getLeftX() + offset),
            static_cast<int>(this->getTopY() + offset)
        );
    }
}

Menu::Menu()
:   title{{static_cast<float>(Screen::CENTER_X), 10.f}, "Peggle!", Color::WHITE},
    pages{
        std::make_unique<GamePage>(75.f),
        std::make_unique<HowToPlayPage>(150.f),
        std::make_unique<CreditsPage>(225.f)
    }
{}

Menu::~Menu() {}

void Menu::run() {
    while (true) {
        LCD.Update();
        this->draw();
        this->processInput();
    }
}

void Menu::drawForeground() const {
    this->title.draw();

    for (const auto &page : this->pages) {
        page->getRunButton().drawUnpressed();
    }
}

void Menu::processInput() {
    // Wait until the next touch.
    const auto touch = Position::nextTouch();

    for (auto &page : this->pages) {
        const auto &runButton = page->getRunButton();

        if (runButton.contains(touch)) {
            runButton.drawPressed();

            // Wait until the button is no longer pressed.
            while (runButton.isPressed());

            page->run();

            return;
        }
    }
}

float Menu::getWidth() const {
    return static_cast<float>(Screen::WIDTH);
}

float Menu::getHeight() const {
    return static_cast<float>(Screen::WIDTH);
}

Position Menu::getCenter() const {
    return Screen::CENTER;
}

Color Menu::getBackgroundColor() const {
    return Color::BLACK;
}

} // namespace menu
