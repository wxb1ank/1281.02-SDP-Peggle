#include <menu.hpp>

#include <FEHLCD.hpp>
#include <font.hpp>

#include <optional>

namespace menu {

const ui::Size BUTTON_SIZE{
    160.f,
    static_cast<float>(Font::HEIGHT) + (2.f * ui::Button::DEFAULT_PADDING)
};

const Position TITLE_POSITION{
    static_cast<float>(Screen::CENTER_X),
    static_cast<float>(Screen::MIN_Y + 25.f)
};

const std::array<Level, 7> LEVELS{
    Level::one(),
    Level::two(),
    Level::three(),
    Level::four(),
    Level::five(),
    Level::six(),
    Level::amogus()
};

Menu::Menu() : pages{} {}

Menu::~Menu() {}

void Menu::run(game::Statistics &stats) {
    while (true) {
        this->step(stats);
    }
}

void Menu::step(game::Statistics &stats) {
    // We are careful to get the current touch *before* drawing the background. Unfortunate
    // design decisions in the simulator library led to the `LCD::Touch` function, as well as
    // sleep functions, updating the LCD when called. If the LCD is updated after the background
    // is drawn but before the page buttons are drawn, then a flickering effect will occur,
    // which is visually unpleasant.
    const auto touch = Position::getCurrentTouch();
    // Now we can draw the background.
    this->drawBackground();

    std::optional<Page *> nextPage{};

    for (auto &page : this->pages) {
        const auto &runButton = page->getRunButton();
        if (
            // It is impossible for two buttons to be pressed simultaneously, so if `nextPage`
            // was previously set, we know that the run button of the current page cannot be
            // pressed.
            !nextPage.has_value() &&
            touch.has_value() &&
            // The short-circuiting property of the logical AND in C++ guarantees that `touch`
            // is dereferenced only if it is first determined to contain a value.
            runButton.contains(*touch)
        ) {
            // The run button is pressed.
            runButton.drawPressed();
            nextPage.emplace(page.get());
        } else {
            // The run button is *not* pressed.
            runButton.drawUnpressed();
        }
    }

    // Flush our draw operations by rendering the LCD framebuffer.
    LCD.Update();

    if (nextPage.has_value()) {
        const auto &runButton = (*nextPage)->getRunButton();

        // Wait until the button is no longer pressed.
        while (runButton.isPressed()) {
            // We should probably redraw the background and page buttons here, because the
            // background might be dynamic (which is in fact the case with the main menu), but
            // 99% of people will hold this button for such a short duration that they probably
            // won't notice if the background freezes for a few frames.
        }

        (*nextPage)->run(stats);

        // The screen will be cleared when we draw the background in the next iteration of this
        // loop.
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
