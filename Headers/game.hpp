/// \file

#pragma once

#include <mechanics.hpp>
#include <ui.hpp>

#include <cstdlib>
#include <optional>
#include <vector>

namespace game {

class Obstacle;

/// \author Will Blankemeyer
class Ball final : public ui::View {
public:
    Ball();

    static constexpr size_t RADIUS{3};

    void shootAt(Position target);

    Position &getPos();
    const Position &getPos() const;

    Velocity &getVel();
    const Velocity &getVel() const;

    void tick(float timeElapsed);

    bool isOnScreen() const;

    void checkCollisionWith(const Obstacle &);

    virtual float getWidth() const override;
    virtual float getHeight() const override;
    virtual Position getCenter() const override;

    virtual void draw() const override;

private:
    Position pos;
    Velocity vel;

    void tickX(float timeElapsed);
    void tickY(float timeElapsed);
};

class Obstacle {
public:
    ~Obstacle();

    static constexpr float MOMENTUM_LOSS{-.65f};

    virtual std::optional<Velocity> deflectionTo(const Ball &) const = 0;
};

class Ceiling final : public Obstacle {
public:
    Ceiling();

    virtual std::optional<Velocity> deflectionTo(const Ball &) const override;
};

class LeftWall final : public Obstacle {
public:
    LeftWall();

    virtual std::optional<Velocity> deflectionTo(const Ball &) const override;
};

class RightWall final : public Obstacle {
public:
    RightWall();

    virtual std::optional<Velocity> deflectionTo(const Ball &) const override;
};

extern const Ceiling CEILING;
extern const LeftWall LEFT_WALL;
extern const RightWall RIGHT_WALL;

/// \brief Class representing a peg
///
/// \author Solomon Blair
class Peg : public Obstacle
{
    public:
        Peg();
        Peg(int x_pos, int y_pos, int radius);
        int getX() const;
        int getY() const;
        int getRadius() const;
        int getStatus() const;

        virtual std::optional<Velocity> deflectionTo(const Ball &) const override;

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

    void run();

private:
    PegBoard board;
    ui::BackgroundView background;
};

} // namespace game

using game::Game;
