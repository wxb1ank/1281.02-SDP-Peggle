/// \file

#pragma once

#include <functional>
#include <string>

#include "../FEHLCD.h"
#include "../ui.hpp"

namespace menu {

class Page : public ui::View {
public:
    /// \brief Creates a new page.
    ///
    /// \param[in]  name    The name of this page.
    /// \param[in]  centerY The Y coordinate of the center of the run button.
    /// \author Will Blankemeyer
    Page(std::string name, float centerY);

    /// \brief Destroys this page.
    ///
    /// \author Will Blankemeyer
    virtual ~Page();

    /// \brief An immutable reference to the main menu button that runs this page.
    ///
    /// \return The run button.
    /// \author Will Blankemeyer
    const ui::Button &getRunButton() const {
        return this->runButton;
    }

    /// \brief An immutable reference to the button that returns to the main menu.
    ///
    /// \return The back button.
    /// \author Will Blankemeyer
    const ui::Button &getBackButton() const {
        return this->backButton;
    }

    /// \brief Draws this page and responds to input.
    ///
    /// \author Will Blankemeyer
    void run();

    virtual float getWidth() const override;
    virtual float getHeight() const override;
    virtual Position getCenter() const override;

    virtual ui::Visibility getBackgroundVisibility() const final {
        return ui::Visibility::Visible;
    }

    virtual void setBackgroundVisibility(const ui::Visibility _) final {}

protected:
    virtual void drawForeground() const final;
    virtual void drawContent() const = 0;

    enum class StepResult {
        RedrawAndContinue,
        Continue,
        Return,
    };

    virtual StepResult step() {
        return StepResult::Continue;
    }

private:
    /// \brief The button in the main menu that runs this page.
    ///
    /// \author Will Blankemeyer
    ui::Button runButton;
    /// \brief The button drawn on the page that returns control to the main menu.
    ///
    /// \author Will Blankemeyer
    ui::Button backButton;
};

} // namespace menu
