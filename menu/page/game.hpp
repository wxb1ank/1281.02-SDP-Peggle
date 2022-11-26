#pragma once

#include "../page.hpp"

namespace menu {

class GamePage : public Page {
public:
    GamePage(float);

    virtual void step();
};

} // namespace menu
