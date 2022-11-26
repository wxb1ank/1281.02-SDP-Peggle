#pragma once

#include <string>

#include <FEHLCD.h>

#include "../graphics.hpp"
#include "../screen.hpp"

namespace menu {

class Page {
public:
    Page(const std::string name, const float centerY)
        : runButton{name, {Screen::CENTER_X, centerY}, {100., 20.}},
          backButton{"Back", {50., 15.}, {50., 15.}}
    {}

    const gfx::Button &getRunButton() const {
        return this->runButton;
    }

    void run();

    virtual void step() = 0;

private:
    gfx::Button runButton;
    gfx::Button backButton;
};

} // namespace menu
