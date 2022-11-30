/// \file
/// \brief The Peggle main menu.

#pragma once

#include <game.hpp>
#include <ui.hpp>

#include <array>
#include <functional>
#include <memory>
#include <string>

/// \brief The Peggle main menu.
///
/// \author Will Blankemeyer
namespace menu {

class Page {
public:
    /// \brief Creates a new page.
    ///
    /// \param[in]  name    The name of this page.
    /// \param[in]  centerY The Y coordinate of the center of the run button.
    /// \param[in]  background
    /// \author Will Blankemeyer
    Page(std::string name, float centerY, ui::BackgroundView background);

    /// \brief Destroys this page.
    ///
    /// \author Will Blankemeyer
    virtual ~Page();

    /// \brief An immutable reference to the main menu button that runs this page.
    ///
    /// \return The run button.
    /// \author Will Blankemeyer
    const ui::Button &getRunButton() const;

    /// \brief Draws this page and responds to input.
    ///
    /// \author Will Blankemeyer
    virtual void run();

protected:
    ui::BackgroundView &getBackground();
    const ui::BackgroundView &getBackground() const;

private:
    /// \brief The button in the main menu that runs this page.
    ///
    /// \author Will Blankemeyer
    ui::Button runButton;
    ui::BackgroundView background;
};

class PageWithBackButton : public Page {
public:
    PageWithBackButton(Page page);

    /// \brief Destroys this page.
    ///
    /// \author Will Blankemeyer
    virtual ~PageWithBackButton();

    /// \brief An immutable reference to the button that returns to the main menu.
    ///
    /// \return The back button.
    /// \author Will Blankemeyer
    const ui::Button &getBackButton() const;

    /// \brief Draws this page and responds to input.
    ///
    /// \author Will Blankemeyer
    virtual void run() final;

protected:
    virtual void drawContent() const;

    enum class StepResult {
        RedrawAndContinue,
        Continue,
        Return,
    };

    virtual StepResult step();

private:
    /// \brief The button drawn on the page that returns control to the main menu.
    ///
    /// \author Will Blankemeyer
    ui::Button backButton;

    void draw(std::function<void(const ui::Button *)>) const;
};

class CreditsPage final : public PageWithBackButton {
public:
    CreditsPage(float);

protected:
    virtual void drawContent() const override;
};

/// \author Will Blankemeyer
class GamePage final : public Page {
public:
    GamePage(float);

    /// \author Will Blankemeyer
    virtual void run() override;

private:
    Game game;
};

class StatsPage final : public PageWithBackButton {
public:
    StatsPage(float);

protected:
    virtual void drawContent() const override;
};

class TutorialPage final : public PageWithBackButton {
public:
    TutorialPage(float);

protected:
    virtual void drawContent() const override;
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

    /// \brief Destroys this main menu.
    ///
    /// \author Will Blankemeyer
    virtual ~Menu();

    /// \brief Draws this menu and responds to input.
    ///
    /// \note This method does not return.
    /// \author Will Blankemeyer
    [[noreturn]] void run();

private:
    ui::StackedLabel title;
    std::array<std::unique_ptr<Page>, 4> pages;
    ui::BackgroundView background;

    void draw();
    void processTouch(Position touch);
};

} // namespace menu

using menu::Menu;
