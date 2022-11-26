#pragma once

#include <array>
#include <cstdlib>

#include "graphics.hpp"
#include "mechanics.hpp"
#include "menu/page.hpp"
#include "menu/page/credits.hpp"
#include "menu/page/game.hpp"
#include "menu/page/how_to_play.hpp"

namespace menu {

class Menu {
public:
    Menu() : pages{&this->gamePage, &this->howToPlayPage, &this->creditsPage} {}

    [[noreturn]] void run();

private:
    GamePage gamePage{75.};
    HowToPlayPage howToPlayPage{150.};
    CreditsPage creditsPage{225.};

    std::array<Page *, 3> pages;

    void draw() const;
    void step();
};

} // namespace menu

using menu::Menu;
