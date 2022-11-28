/// \file

#pragma once

#include "../page.hpp"

namespace menu {

class StatsPage final : public Page {
public:
    StatsPage(float);

    virtual Color getBackgroundColor() const override;

protected:
    virtual void drawContent() const override;
};

} // namespace menu
