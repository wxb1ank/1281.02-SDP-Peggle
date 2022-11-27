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
        void collisionCheck(float x, float y, float * vx, float * vy);
        int getX();
        int getY();
        int getRadius();
        int getStatus();
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
        void drawPegs();
        int getNum();
    private:
        std::vector<Peg> pegs;
};

/// \author Solomon Blair
class Page : public menu::Page {
public:
    Page(float);

    /// \author Solomon Blair
    virtual void run() final;

private:
    PegBoard board;
};

} // namespace game

using GamePage = game::Page;

} // namespace menu
