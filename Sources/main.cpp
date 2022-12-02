#include <game.hpp>
#include <menu.hpp>

int main() {
    // Keep track of lifetime game statistics.
    game::Statistics stats{};

    // Run the main menu. (This function should not return.)
    MainMenu().run(stats);
}
