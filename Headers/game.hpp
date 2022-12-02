/// \file
/// \brief Core game logic.

#pragma once

#include <mechanics.hpp>
#include <ui.hpp>

#include <cstdlib>
#include <optional>
#include <vector>

/// \brief Core game logic.
namespace game {

class Obstacle;
class Peg;

class Statistics {
public:
    Statistics();

    std::size_t getTotalScore() const;
    std::size_t getTopScore() const;
    std::size_t getOrangePegsHit() const;
    std::size_t getBallsShot() const;

    void addScore(std::size_t score);
    void addOrangePegsHit(std::size_t pegsHit);
    void addBallsShot(std::size_t ballsShot);

private:
    std::size_t totalScore;
    std::size_t topScore;
    std::size_t orangePegsHit;
    std::size_t ballsShot;
};

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

    virtual float getWidth() const override;
    virtual float getHeight() const override;
    virtual Position getCenter() const override;

    virtual void draw() const override;
    void drawGuide(std::vector<Peg> &);

private:
    Position pos;
    Velocity vel;

    static void tick(Velocity &vel, Position &pos, float timeElapsed);
    static void tickX(const Velocity &vel, Position &pos, float timeElapsed);
    static void tickY(Velocity &vel, Position &pos, float timeElapsed);
};

struct Deflection {
    Position pos;
    Velocity vel;
};

class Obstacle {
public:
    ~Obstacle();

    static constexpr float MOMENTUM_LOSS{-.90f};

    virtual void checkCollisionWith(Velocity &, Position &, int guide);
};

class Ceiling final : public Obstacle {
public:
    Ceiling();

    virtual void checkCollisionWith(Velocity &, Position &, int guide) override;
};

class LeftWall final : public Obstacle {
public:
    LeftWall();

    virtual void checkCollisionWith(Velocity &, Position &, int guide) override;
};

class RightWall final : public Obstacle {
public:
    RightWall();

    virtual void checkCollisionWith(Velocity &, Position &, int guide) override;
};

extern Ceiling CEILING;
extern LeftWall LEFT_WALL;
extern RightWall RIGHT_WALL;

class Bucket final : public ui::View {
public:
    Bucket();

    void tick();

    virtual float getWidth() const override;
    virtual float getHeight() const override;
    virtual Position getCenter() const override;
    virtual void draw() const override;

private:
    Position center;
    float changeX;

    static const ui::Size SIZE;
};

/// \brief Class representing a peg
///
/// \author Solomon Blair
class Peg : public Obstacle
{
    public:
        Peg();
        Peg(int x_pos, int y_pos, int radius, int colorOfPeg);
        int getX() const;
        int getY() const;
        int getRadius() const;
        int getStatus() const;
        void setStatus(int status);
        int getColor() const;
        virtual void checkCollisionWith(Velocity &, Position &, int guide) override;

    private:
        int x_position, y_position, peg_radius, active, color;
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

    void run(Statistics &stats);

private:
    PegBoard board;
    Bucket bucket;
    ui::BackgroundView background;
};

} // namespace game

// `game::Game` is tedious to write, so consumers can instead write `Game`.
using game::Game;
