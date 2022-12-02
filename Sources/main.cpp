#include <game.hpp>
#include <menu.hpp>

int main() {
    game::Statistics stats{};

    // Run the main menu.
    MainMenu().run(stats);
}
