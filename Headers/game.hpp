/// \file

#pragma once

#include <vector>

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

class Game {
public:
    Game();

    void step();

private:
    PegBoard board;
};

} // namespace game

using game::Game;
