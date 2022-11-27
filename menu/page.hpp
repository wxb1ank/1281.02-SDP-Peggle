/// \file

#pragma once

#include <string>

#include <FEHLCD.h>

#include "../ui.hpp"

namespace menu {

class Page {
public:
    /// \brief Creates a new page.
    ///
    /// \param[in]  name    The name of this page.
    /// \param[in]  centerY The Y coordinate of the center of the run button.
    /// \author Will Blankemeyer
    Page(std::string name, float centerY);

    /// \brief An immutable reference to the main menu button that runs this page.
    ///
    /// \return The run button.
    /// \author Will Blankemeyer
    const ui::Button &getRunButton() const {
        return this->runButton;
    }

    void run();

    virtual void step() = 0;

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
