#pragma once

#include <string>

#include <FEHLCD.h>

#include "../graphics.hpp"

namespace menu {

class Page {
public:
    Page(std::string, float);

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
