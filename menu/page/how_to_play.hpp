/// \file

#pragma once

#include "../page.hpp"

namespace menu {

class HowToPlayPage : public Page {
public:
    HowToPlayPage(float);

    virtual void run() final;
};

} // namespace menu
