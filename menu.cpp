#include <cstdlib>

#include "FEHLCD.h"
#include "mechanics.hpp"
#include "screen.hpp"

#include "menu.hpp"

namespace menu {

StackedLabel::StackedLabel(const Position center, const std::string content, const Color color)
:   Label{center, content, color}
{}

StackedLabel::~StackedLabel() {}

void StackedLabel::draw() const {
    LCD.SetFontColor(this->getColor().encode());
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
:   title{{static_cast<float>(Screen::CENTER_X), 10.f}, "Peggle!"},
    pages{
        std::make_unique<GamePage>(75.f),
        std::make_unique<HowToPlayPage>(150.f),
        std::make_unique<CreditsPage>(225.f)
    }
{}

void Menu::run() {
    while (true) {
        this->draw();
        this->processInput();
    }
}

void Menu::draw() const {
    LCD.Update();
    LCD.Clear(Color::BLACK.encode());

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

} // namespace menu
