/// \file

#pragma once

#include "../page.hpp"

namespace menu {

class CreditsPage final : public Page {
public:
    CreditsPage(float);

    virtual Color getBackgroundColor() const override;

protected:
    virtual void drawContent() const override;
};

} // namespace menu
