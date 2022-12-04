#include <menu.hpp>

namespace menu {

TutorialPage::TutorialPage(const float centerY)
:   PageWithBackButton{Page(MainMenu::createRunButton("How to Play", centerY, Color::GREEN))}
{}

void TutorialPage::run(game::Statistics &) {
    ui::BackgroundView(Color::BLACK).draw();
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

    while (!this->shouldReturnFromRun());
}

} // namespace menu
