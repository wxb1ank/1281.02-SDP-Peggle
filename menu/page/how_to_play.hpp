#pragma once

#include "../page.hpp"

namespace menu {

class HowToPlayPage : public Page {
public:
    HowToPlayPage(float);

    virtual void step();
};

} // namespace menu
