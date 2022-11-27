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
    /// \param[in]  center          The position of the center of this label.
    /// \param[in]  content         The textual content of this label.
    /// \param[in]  backgroundColor The background color.
    /// \param[in]  fontColor       The font color.
    /// \author Will Blankemeyer
    StackedLabel(
        Position center,
        std::string content,
        Color backgroundColor,
        Color fontColor
    );
    /// \brief Creates a new stacked label with an invisible background.
    ///
    /// \param[in]  center          The position of the center of this label.
    /// \param[in]  content         The textual content of this label.
    /// \param[in]  fontColor       The font color.
    /// \author Will Blankemeyer
    StackedLabel(
        Position center,
        std::string content,
        Color fontColor
    );

    /// \brief Destroys this label.
    ///
    /// \author Will Blankemeyer
    virtual ~StackedLabel();

protected:
    virtual void drawForeground() const override;
};

/// \brief The Peggle main menu.
///
/// \author Will Blankemeyer
class Menu : public ui::View {
public:
    /// \brief Creates a new main menu.
    ///
    /// \author Will Blankemeyer
    Menu();

    /// \brief Destroys this main menu.
    ///
    /// \author Will Blankemeyer
    virtual ~Menu();

    /// \brief Draws this menu and responds to input.
    ///
    /// \note This method does not return.
    /// \author Will Blankemeyer
    [[noreturn]] void run();

    virtual float getWidth() const override;
    virtual float getHeight() const override;
    virtual Position getCenter() const override;
    virtual Color getBackgroundColor() const override;

    virtual ui::Visibility getBackgroundVisibility() const final {
        return ui::Visibility::Visible;
    }

    virtual void setBackgroundVisibility(const ui::Visibility _) final {}

protected:
    virtual void drawForeground() const override;

private:
    StackedLabel title;
    std::array<std::unique_ptr<Page>, 3> pages;

    void processInput();
};

} // namespace menu

using menu::Menu;
