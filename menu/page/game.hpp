/// \file

#pragma once

#include <vector>

#include "../page.hpp"

namespace menu {
namespace game {

/// \brief Class representing a peg
///
/// \author Solomon Blair
class Peg
{
    public:
        Peg();
        Peg(int x_pos, int y_pos, int radius);
        void collisionCheck(float x, float y, float * vx, float * vy) const;
        int getX() const;
        int getY() const;
        int getRadius() const;
        int getStatus() const;
    private:
        int x_position, y_position, peg_radius, active;
};

/// \brief Class represeting the whole board
///
/// \author Solomon Blair
class PegBoard
{
    public:
        PegBoard();
        /// \author Will Blankemeyer
        void push(Peg peg);
        void drawPegs() const;
        int getNum() const;
        std::vector<Peg> &getPegs();
    private:
        std::vector<Peg> pegs;
};

/// \author Solomon Blair
class Page final : public menu::Page {
public:
    Page(float);

    virtual Color getBackgroundColor() const override;

protected:
    /// \author Solomon Blair
    virtual void drawContent() const override;

    /// \author Solomon Blair
    virtual menu::Page::StepResult step() override;

private:
    PegBoard board;
};

} // namespace game

using GamePage = game::Page;

} // namespace menu
