#include <menu.hpp>

#include <FEHLCD.hpp>

namespace menu {

CreditsPage::CreditsPage(const float centerY)
:   PageWithBackButton{Page("Credits", centerY, Color::BLUE), ui::BackgroundView(Color::BLACK)}
{}

CreditsPage::StepResult CreditsPage::step(game::Statistics &) {
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

    return StepResult::Continue;
}

} // namespace menu
