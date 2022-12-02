#include <menu.hpp>

#include <FEHLCD.hpp>

namespace menu {

TutorialPage::TutorialPage(const float centerY)
:   PageWithBackButton{Page("How to Play", centerY), ui::BackgroundView(Color::BLACK)}
{}

TutorialPage::StepResult TutorialPage::step(game::Statistics &) {
    ui::Label(TITLE_POSITION, "How to Play", Color::SILVER).draw();

    ui::MultilineLabel(
        Position(static_cast<float>(Screen::CENTER_X), static_cast<float>(Screen::CENTER_Y) + 20.f),
        "Tap to shoot the ball.\n"
        "\n"
        "Try to hit al the orange\n"
        "pegs before using all\n"
        "balls.\n"
        "\n"
        "Landing the ball in the\n"
        "bucket returns the ball\n"
        "to you.\n",
        Color::WHITE
    )
    .draw();

    return StepResult::Continue;
}

} // namespace menu
