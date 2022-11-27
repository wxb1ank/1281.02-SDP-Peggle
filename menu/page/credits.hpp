/// \file

#pragma once

#include "../page.hpp"

namespace menu {

class CreditsPage : public Page {
public:
    CreditsPage(float);

    virtual void run() final;
};

} // namespace menu
