#include <menu.hpp>

#include <FEHLCD.hpp>

namespace menu {

Page::Page(const ui::Button runButton) : runButton{runButton} {}

Page::~Page() {}

const ui::Button &Page::getRunButton() const {
    return this->runButton;
}

void Page::run(game::Statistics &) {}

PageWithBackButton::PageWithBackButton(const Page page)
:   Page{page},
    backButton{
        ui::Label(Position(45.f, TITLE_POSITION.y), "Back", Color::BLACK),
        Color::GRAY,
        Color::WHITE
    }
{}

PageWithBackButton::~PageWithBackButton() {}

const ui::Button &PageWithBackButton::getBackButton() const {
    return this->backButton;
}

bool PageWithBackButton::shouldReturnFromRun() const {
    this->backButton.drawUnpressed();
    if (this->backButton.isPressed()) {
        this->backButton.drawPressed();
        LCD.Update();

        while (this->backButton.isPressed());

        return true;
    } else {
        return false;
    }
}

} // namespace menu
