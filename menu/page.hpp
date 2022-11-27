#pragma once

#include <string>

#include <FEHLCD.h>

#include "../ui.hpp"

namespace menu {

class Page {
public:
    Page(std::string, float);

    const ui::Button &getRunButton() const {
        return this->runButton;
    }

    void run();

    virtual void step() = 0;

private:
    ui::Button runButton;
    ui::Button backButton;
};

} // namespace menu
