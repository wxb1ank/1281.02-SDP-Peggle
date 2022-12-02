#include <menu.hpp>

#include <FEHLCD.hpp>
#include <screen.hpp>

#include <optional>
#include <utility>

namespace menu {

Menu::Menu() : pages{} {}

Menu::~Menu() {}

void Menu::run(game::Statistics &stats) {
    while (true) {
        // Fun fact: `LCD::Touch` redraws the screen (???). This has unfortunate consequences.
        // Because of this, it is essential that we get the current touch---and, by extension,
        // redraw the screen (ugh)---*before* we clear the screen. Otherwise, if we get the touch
        // after clearing then the menu will be drawn incompletely (without the page buttons).
        // Because we're in a loop, that equates to a nasty flickering effect that no one wants to
        // see.
        const auto touch = Position::getCurrentTouch();

        this->drawBackground();

        std::optional<Page *> nextPage{};

        for (auto &page : this->pages) {
            const auto &runButton = page->getRunButton();
            if (!nextPage.has_value() && touch.has_value() && runButton.contains(*touch)) {
                runButton.drawPressed();
                nextPage.emplace(page.get());
            } else {
                runButton.drawUnpressed();
            }
        }

        // Finally, we can properly call `LCD::Update`.
        LCD.Update();

        if (nextPage.has_value()) {
            // Wait until the button is no longer pressed.
            while ((*nextPage)->getRunButton().isPressed());

            (*nextPage)->run(stats);
        }
    }
}

std::vector<std::unique_ptr<Page>> &Menu::getPages() {
    return this->pages;
}

const std::vector<std::unique_ptr<Page>> &Menu::getPages() const {
    return this->pages;
}

void Menu::drawBackground() {}

} // namespace menu
