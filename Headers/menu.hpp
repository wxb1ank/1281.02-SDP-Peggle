/// \file
/// \brief Peggle UI menus.

#pragma once

#include <game.hpp>
#include <ui.hpp>

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

/// \brief Peggle UI menus.
namespace menu {

/// \brief The standard size of a menu button.
///
/// \author Will Blankemeyer
extern const ui::Size BUTTON_SIZE;
/// \brief The standard position of the center of a title label.
///
/// \author Will Blankemeyer
extern const Position TITLE_POSITION;

/// \brief A controller for a fullscreen view accessible from a menu.
///
/// \author Will Blankemeyer
class Page {
public:
    /// \brief Creates a new page.
    ///
    /// \param[in]  runButton   The button in the menu that runs this page.
    /// \author Will Blankemeyer
    Page(std::string name, float centerY, Color borderColor);

    /// \brief Destroys this page.
    ///
    /// \author Will Blankemeyer
    virtual ~Page();

    /// \brief An immutable reference to the menu button that runs this page.
    ///
    /// \return The run button.
    /// \author Will Blankemeyer
    const ui::Button &getRunButton() const;

    /// \brief Draws this page and responds to input.
    ///
    /// \param[in]  stats   A mutable reference to global game statistics.
    /// \author Will Blankemeyer
    virtual void run(game::Statistics &stats);

private:
    /// \author Will Blankemeyer
    ui::Button runButton;
};

/// \brief A page that provides a back button in its view that returns to the previous menu.
///
/// \author Will Blankemeyer
class PageWithBackButton : public Page {
public:
    /// \brief Creates a new page with a back button.
    ///
    /// \param[in]  page        The page.
    /// \param[in]  background  The background view that is drawn behind the back button.
    /// \author Will Blankemeyer
    PageWithBackButton(Page page, ui::BackgroundView background);

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
    /// \param[in]  stats   A mutable reference to global game statistics.
    /// \author Will Blankemeyer
    virtual void run(game::Statistics &stats) final;

protected:
    /// \brief The result of the `step` method.
    ///
    /// The value of this type dictates control flow in `run`.
    ///
    /// \author Will Blankemeyer
    enum class StepResult {
        /// \brief The background and back button should be redrawn, after which the `step` method
        /// should be called again.
        ///
        /// \author Will Blankemeyer
        RedrawAndContinue,
        /// \brief The `step` method should be called again without redrawing the background or back
        /// button.
        ///
        /// \author Will Blankemeyer
        Continue,
        /// \brief The `run` method should return.
        ///
        /// \author Will Blankemeyer
        Return,
    };

    /// \author Will Blankemeyer
    virtual StepResult step(game::Statistics &stats);

    /// \brief A mutable reference to the background view drawn behind the back button.
    ///
    /// \return The background view.
    /// \author Will Blankemeyer
    ui::BackgroundView &getBackground();
    /// \brief An immutable reference to the background view drawn behind the back button.
    ///
    /// \return The background view.
    /// \author Will Blankemeyer
    const ui::BackgroundView &getBackground() const;

private:
    /// \brief The button drawn on the page that returns control to the main menu.
    ///
    /// \author Will Blankemeyer
    ui::Button backButton;
    /// \author Will Blankemeyer
    ui::BackgroundView background;

    /// \author Will Blankemeyer
    void draw(std::function<void(const ui::Button *)>);
};

/// \brief A page that displays the names of those who created this project.
///
/// \author Will Blankemeyer
class CreditsPage final : public PageWithBackButton {
public:
    /// \brief Creates a new credits page.
    ///
    /// \param[in]  centerY The Y coordinate of the center of the run button.
    /// \author Will Blankemeyer
    CreditsPage(float centerY);

protected:
    /// \author Will Blankemeyer
    virtual StepResult step(game::Statistics &stats);
};

/// \brief A page that lists global game statistics.
///
/// \author Will Blankemeyer
class StatsPage final : public PageWithBackButton {
public:
    /// \brief Creates a new statistics page.
    ///
    /// \param[in]  centerY The Y coordinate of the center of the run button.
    /// \author Will Blankemeyer
    StatsPage(float centerY);

protected:
    /// \author Will Blankemeyer
    virtual StepResult step(game::Statistics &stats) override;
};

/// \brief A page that instructs new users how to play Peggle.
///
/// \author Will Blankemeyer
class TutorialPage final : public PageWithBackButton {
public:
    /// \brief Creates a new tutorial page.
    ///
    /// \param[in]  centerY The Y coordinate of the center of the run button.
    /// \author Will Blankemeyer
    TutorialPage(float centerY);

protected:
    /// \author Will Blankemeyer
    virtual StepResult step(game::Statistics &stats);
};

class LevelPage : public Page {
public:
    LevelPage(std::string name, float centerY, game::Level level);

    virtual void run(game::Statistics &stats) final;

private:
    game::Level level;
};

/// \brief A Peggle menu.
///
/// \author Will Blankemeyer
class Menu {
public:
    Menu();

    /// \brief Destroys this menu.
    ///
    /// \author Will Blankemeyer
    virtual ~Menu();

    [[noreturn]] void run(game::Statistics &stats);

    /// \brief Draws this menu and responds to input.
    ///
    /// \author Will Blankemeyer
    void step(game::Statistics &stats);

protected:
    std::vector<std::unique_ptr<Page>> &getPages();
    const std::vector<std::unique_ptr<Page>> &getPages() const;

    virtual void drawBackground();

private:
    /// \author Will Blankemeyer
    std::vector<std::unique_ptr<Page>> pages;
};

class MainMenu final : public Menu {
public:
    /// \brief Creates a new main menu.
    ///
    /// \author Will Blankemeyer
    MainMenu();

protected:
    virtual void drawBackground() override;

private:
    /// \author Will Blankemeyer
    ui::StackedLabel title;
    /// \author Will Blankemeyer
    ui::BackgroundView background;
};

class LevelMenu final : public Menu {
public:
    /// \brief Creates a new level menu.
    ///
    /// \author Will Blankemeyer
    LevelMenu();

protected:
    virtual void drawBackground() override;

private:
    /// \author Will Blankemeyer
    ui::Label title;
    /// \author Will Blankemeyer
    ui::BackgroundView background;
};

/// \author Will Blankemeyer
class LevelMenuPage final : public PageWithBackButton {
public:
    LevelMenuPage(float centerY);

protected:
    /// \author Will Blankemeyer
    virtual StepResult step(game::Statistics &stats);

protected:
    LevelMenu levelMenu;
};

} // namespace menu

// `menu::Menu` etc. are tedious to write, so consumers can instead write `Menu`.
using menu::Menu;
using menu::MainMenu;
using menu::LevelMenu;
