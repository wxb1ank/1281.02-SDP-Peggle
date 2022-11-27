/// \file
/// \brief The Peggle main menu.

#pragma once

#include <array>
#include <memory>

#include "menu/page.hpp"
#include "menu/page/credits.hpp"
#include "menu/page/game.hpp"
#include "menu/page/how_to_play.hpp"
#include "ui.hpp"

/// \brief The Peggle main menu.
///
/// \author Will Blankemeyer
namespace menu {

class StackedLabel : public ui::Label {
public:
    /// \brief Creates a new stacked label.
    ///
    /// \param[in]  center  The position of the center of this label.
    /// \param[in]  content The textual content of this label.
    /// \param[in]  color   The font color. The default is white.
    /// \author Will Blankemeyer
    StackedLabel(Position center, std::string content, Color color = Color::WHITE);

    /// \brief Destroys this label.
    ///
    /// \author Will Blankemeyer
    virtual ~StackedLabel();

    virtual void draw() const override;
};

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
    StackedLabel title;
    std::array<std::unique_ptr<Page>, 3> pages;

    void draw() const;
    void processInput();
};

} // namespace menu

using menu::Menu;
