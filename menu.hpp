/// \file
/// \brief The Peggle main menu.

#pragma once

#include <array>
#include <memory>

#include "menu/page.hpp"
#include "menu/page/credits.hpp"
#include "menu/page/game.hpp"
#include "menu/page/how_to_play.hpp"

/// \brief The Peggle main menu.
///
/// \author Will Blankemeyer
namespace menu {

/// \brief The Peggle main menu.
///
/// \author Will Blankemeyer
class Menu {
public:
    /// \brief Creates a new main menu.
    ///
    /// \author Will Blankemeyer
    Menu();

    /// \brief Draws this menu and responds to input.
    ///
    /// \note This method does not return.
    /// \author Will Blankemeyer
    [[noreturn]] void run();

private:
    std::array<std::unique_ptr<Page>, 3> pages;

    void draw() const;
    void processInput();
};

} // namespace menu

using menu::Menu;
