#define _USE_MATH_DEFINES

#include <game.hpp>

#include <cmath>

namespace game {

// Default constructor for Peg class
Peg::Peg()
{
    x_position = 0;
    y_position = 0;
    peg_radius = 0;
    active = 0;
}

// Constructor for Peg class
Peg::Peg(int x_pos, int y_pos, int radius)
{
    x_position = x_pos;
    y_position = y_pos;
    peg_radius = radius;
    active = 1;
}

// Returns x position of peg
int Peg::getX() const
{
    return x_position;
}

// Returns y position of peg
int Peg::getY() const
{
    return y_position;
}

// Returns radius of peg
int Peg::getRadius() const
{
    return peg_radius;
}

// Returns whther peg is active(1) or inactive(0)
int Peg::getStatus() const
{
    return active;
}

std::optional<Velocity> Peg::deflectionTo(const Ball &ball) const {
    const auto pos = ball.getPos();
    auto vel = ball.getVel();

    float xDistance = pos.x - x_position;
    float yDistance = pos.y - y_position;
    float distance = sqrt(powf(xDistance,2) + powf(yDistance,2));
    if(distance <= static_cast<float>(peg_radius + Ball::RADIUS))
    {
        float collision_angle = atan(yDistance/xDistance);
        if(xDistance >= 0)
        {
            collision_angle += M_PI;
        }
        float v = sqrt(powf(vel.x,2) + powf(vel.y,2));
        vel.x = Obstacle::MOMENTUM_LOSS * v * cos(collision_angle);
        vel.y = Obstacle::MOMENTUM_LOSS * v * sin(collision_angle);
        printf("Y: %f\nX: %f\n", vel.y,vel.x);

        return std::optional(vel);
    }
    else
    {
        return {};
    }
}

// PegBoard class functions

// Constructor for the PegBoard class
PegBoard::PegBoard() : pegs{} {}

void PegBoard::push(const Peg peg) {
    this->pegs.push_back(peg);
}

// Draws every peg in the PegBoard class
void PegBoard::drawPegs() const
{
    for(auto &peg : pegs)
    {
        if(peg.getStatus() == 1)
        {
            LCD.DrawCircle(peg.getX(), peg.getY(),peg.getRadius());
        }
    }
}

int PegBoard::getNum() const
{
    return pegs.size();
}

std::vector<Peg> &PegBoard::getPegs() {
    return this->pegs;
}

} // namespace game
