#include <menu.hpp>

#include <FEHLCD.hpp>

namespace menu {

CreditsPage::CreditsPage(const float centerY)
:   PageWithBackButton{Page(MainMenu::createRunButton("Credits", centerY, Color::BLUE))}
{}

void CreditsPage::run(game::Statistics &) {
    ui::BackgroundView(Color::BLACK).draw();
    ui::Label(TITLE_POSITION, "Credits", Color::SILVER).draw();

    const auto namesLabel = ui::MultilineLabel(
        Screen::CENTER,
        "Solomon Blair\n"
        "Will Blankemeyer",
        Color::WHITE
    );
    namesLabel.draw();

    ui::Label(
        Position(static_cast<float>(Screen::CENTER_X), namesLabel.getBottomY() + 20.f),
        "Based on Peggle <3",
        Color::PINK
    )
    .draw();

    while (!this->shouldReturnFromRun());
}

} // namespace menu
