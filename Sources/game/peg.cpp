#define _USE_MATH_DEFINES

#include <game.hpp>

#include <FEHLCD.hpp>

#include <cmath>

namespace game {

// Constructor for Peg class
Peg::Peg(const Position center, float radius, const Peg::Color color)
:   center{center}, radius{radius}, color{color}
{}

// returns color of peg
Peg::Color Peg::getColor() const
{
    return color;
}

// Returns radius of peg
float Peg::getRadius() const
{
    return radius;
}

// Returns whther peg is active(1) or inactive(0)
Peg::Status Peg::getStatus() const
{
    return status;
}

void Peg::hit() {
    if (this->status == Status::Unlit) {
        this->status = Status::Lit;
    }
}

void Peg::obliterate() {
    this->status = Status::Obliterated;
}

float Peg::getWidth() const {
    return 2.f * this->radius;
}

float Peg::getHeight() const {
    return 2.f * this->radius;
}

Position Peg::getCenter() const {
    return this->center;
}

bool Peg::deflect(Velocity &vel, Position &pos) const {
    if (this->status == Status::Obliterated)
    {
        return false;
    }
    else
    {
        float xDistance = pos.x - this->center.x;
        float yDistance = pos.y - this->center.y;
        float distance = std::hypot(xDistance, yDistance);

        if(distance <= (this->radius + static_cast<float>(Ball::RADIUS)))
        {
            float collisionAngle = atan(yDistance/xDistance);
            if(xDistance >= 0)
            {
                collisionAngle += M_PI;
            }
            const auto velMag = Obstacle::MOMENTUM_LOSS * vel.getMagnitude();
            vel.x = velMag * cos(collisionAngle);
            vel.y = velMag * sin(collisionAngle);
        }

        return true;
    }
}

void Peg::draw() const {
    const auto x = static_cast<int>(this->center.x);
    const auto y = static_cast<int>(this->center.y);
    const auto radius = static_cast<int>(this->radius);

    switch (this->color) {
        case Peg::Color::Blue:
            switch (this->status) {
                case Status::Unlit:
                    LCD.SetFontColor(::Color::NAVY.encode());
                    LCD.FillCircle(x, y,radius);
                    LCD.SetFontColor(::Color::LIGHTSTEELBLUE.encode());
                    LCD.FillCircle(x - 1, y - 1, 1);
                    LCD.SetFontColor(::Color::ROYALBLUE.encode());
                    LCD.DrawCircle(x, y,radius);
                    break;
                case Status::Lit:
                    LCD.SetFontColor(::Color::DEEPSKYBLUE.encode());
                    LCD.FillCircle(x, y,radius);
                    LCD.SetFontColor(::Color::DODGERBLUE.encode());
                    LCD.DrawCircle(x, y,radius);
                case Status::Obliterated:
                    break;
            }
            break;
        case Peg::Color::Orange:
            switch (this->status) {
                case Status::Unlit:
                    LCD.SetFontColor(::Color::BROWN.encode());
                    LCD.FillCircle(x, y,radius);
                    LCD.SetFontColor(::Color::WHITESMOKE.encode());
                    LCD.FillCircle(x - 1, y - 1, 1);
                    LCD.SetFontColor(::Color::PERU.encode());
                    LCD.DrawCircle(x, y,radius);
                    break;
                case Status::Lit:
                    LCD.SetFontColor(::Color::ORANGE.encode());
                    LCD.FillCircle(x, y,radius);
                    LCD.SetFontColor(::Color::DARKORANGE.encode());
                    LCD.DrawCircle(x, y,radius);
                    break;
                case Status::Obliterated:
                    break;
            }
            break;
    }
}

// PegBoard class functions

// Constructor for the PegBoard class
PegBoard::PegBoard() : pegs{} {}

void PegBoard::push(const Peg peg) {
    this->pegs.push_back(peg);
}

// Draws every peg in the PegBoard class
void PegBoard::draw() const
{
    for(auto &peg : pegs)
    {
        peg.draw();
    }
}

std::vector<Peg> &PegBoard::getPegs() {
    return this->pegs;
}

} // namespace game
