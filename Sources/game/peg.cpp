#define _USE_MATH_DEFINES

#include <game.hpp>

#include <FEHLCD.hpp>

#include <LCDColors.h>

#include <cmath>

namespace game {

// Default constructor for Peg class
Peg::Peg()
{
    x_position = 0;
    y_position = 0;
    peg_radius = 0;
    active = 0;
    color = 0;
}

// Constructor for Peg class
Peg::Peg(int x_pos, int y_pos, int radius, int colorOfPeg)
{
    x_position = x_pos;
    y_position = y_pos;
    peg_radius = radius;
    active = 1;
    color = colorOfPeg; // 0 for blue : 1 for orange
}

// returns color of peg
int Peg::getColor() const
{
    return color;
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

void Peg::setStatus(int status)
{
    this->active = status;
}

void Peg::checkCollisionWith(Velocity &vel, Position &pos, int guide) {
    if(this->getStatus() != 0)
    {
        float xDistance = pos.x - x_position;
        float yDistance = pos.y - y_position;
        float distance = std::hypot(xDistance, yDistance);
    if(distance <= static_cast<float>(peg_radius + Ball::RADIUS))
        {
            float collisionAngle = atan(yDistance/xDistance);
            if(xDistance >= 0)
            {
                collisionAngle += M_PI;
            }
            float velMag = Obstacle::MOMENTUM_LOSS * vel.getMagnitude();
            vel.x = velMag * cos(collisionAngle);
            vel.y = velMag * sin(collisionAngle);
            if(guide == 0)
            {
                this->setStatus(2);
            }

        }
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
        if(peg.getColor() == 0)
        {
            if(peg.getStatus() == 1)
            {
                LCD.SetFontColor(NAVY);
                LCD.FillCircle(peg.getX(), peg.getY(),peg.getRadius());
                LCD.SetFontColor(LIGHTSTEELBLUE);
                LCD.FillCircle(peg.getX() - 1, peg.getY() - 1, 1);
                LCD.SetFontColor(ROYALBLUE);
                LCD.DrawCircle(peg.getX(), peg.getY(),peg.getRadius());
            }
            else if(peg.getStatus() == 2)
            {
                LCD.SetFontColor(DEEPSKYBLUE);
                LCD.FillCircle(peg.getX(), peg.getY(),peg.getRadius());
                LCD.SetFontColor(DODGERBLUE);
                LCD.DrawCircle(peg.getX(), peg.getY(),peg.getRadius());
            }
        }
        else if(peg.getColor() == 1)
        {
            if(peg.getStatus() == 1)
            {
                LCD.SetFontColor(ORANGERED);
                LCD.FillCircle(peg.getX(), peg.getY(),peg.getRadius());
                LCD.SetFontColor(WHITESMOKE);
                LCD.FillCircle(peg.getX() - 1, peg.getY() - 1, 1);
                LCD.SetFontColor(PERU);
                LCD.DrawCircle(peg.getX(), peg.getY(),peg.getRadius());
            }
            else if(peg.getStatus() == 2)
            {
                LCD.SetFontColor(ORANGE);
                LCD.FillCircle(peg.getX(), peg.getY(),peg.getRadius());
                LCD.SetFontColor(DARKORANGE);
                LCD.DrawCircle(peg.getX(), peg.getY(),peg.getRadius());
            }
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
