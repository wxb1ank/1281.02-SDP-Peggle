/// \file

#pragma once

#include "../page.hpp"

namespace menu {

class HowToPlayPage final : public Page {
public:
    HowToPlayPage(float);

    virtual Color getBackgroundColor() const override;

protected:
    virtual void drawContent() const override;
};

} // namespace menu
