#define _USE_MATH_DEFINES

#include <cstdio>
#include <cmath>
#include <iostream>

#include <FEHLCD.h>
#include <FEHUtility.h>

#include "../../screen.hpp"

#include "game.hpp"

// Time between screen updates (seconds)
#define TICK_DURATION 0.001

// Acceleration due to gravity
#define GRAVITY_ACCEL 200'000.

// Radius of the ball
#define BALL_RADIUS 3

// Boundaries of screen and ball location
#define MIN_BALL_Y ((float)BALL_RADIUS)
#define MAX_BALL_Y (((float)HEIGHT - 1.0) - (float)BALL_RADIUS)
#define MIN_BALL_X ((float)BALL_RADIUS)
#define MAX_BALL_X (((float)WIDTH - 1.0) - (float)BALL_RADIUS)
#define WIDTH  320
#define HEIGHT 240

// Initial velocity of ball after being shot
#define INIT_VELOCITY 2'500.

// Momentum lost to a collision
#define MOMENTUM_LOSS -1.001

namespace menu {
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

// Checks if the ball collides with a peg
void Peg::collisionCheck(float x, float y, float * vx, float * vy)
{
    float xDistance = x - x_position;
    float yDistance = y - y_position;
    float distance = sqrt(powf(xDistance,2) + powf(yDistance,2));
    if(distance <= (peg_radius + BALL_RADIUS))
    {
        float collision_angle = atan(yDistance/xDistance);
        if(xDistance >= 0)
        {
            collision_angle += M_PI;
        }
        printf("%f\n",collision_angle * 180 / M_PI);
        float v = sqrt(powf(*vx,2) + powf(*vy,2));
        *vx = MOMENTUM_LOSS * v * cos(collision_angle);
        *vy = MOMENTUM_LOSS * v * sin(collision_angle);
    }
}
// Returns x position of peg
int Peg::getX()
{
    return x_position;
}

// Returns y position of peg
int Peg::getY()
{
    return y_position;
}

// Returns radius of peg
int Peg::getRadius()
{
    return peg_radius;
}

// Returns whther peg is active(1) or inactive(0)
int Peg::getStatus()
{
    return active;
}

// PegBoard class functions

// Constructor for the PegBoard class
PegBoard::PegBoard() : pegs{} {}

void PegBoard::push(const Peg peg) {
    this->pegs.push_back(peg);
}

// Draws every peg in the PegBoard class
void PegBoard::drawPegs()
{
    for(auto &peg : pegs)
    {
        if(peg.getStatus() == 1)
        {
            LCD.DrawCircle(peg.getX(), peg.getY(),peg.getRadius());
        }
    }
}

int PegBoard::getNum()
{
    return pegs.size();
}

Page::Page(const float centerY) : menu::Page{"Game", centerY}, board{} {
    // Pegs on the board
    for (unsigned x = 5; x < 160; x += 5) {
        board.push({x, 200, 5});
    }
}

void Page::run() {
    LCD.Clear(Color::Black);
    this->board.drawPegs();

    // Location of where the player clicks on the screen
    float target_x;
    float target_y;

    // Shoots ball upon LCD.Touch returning a true value
    while (!LCD.Touch(&target_x, &target_y));

    // Sets (0,0) to be at (160,0)
    target_x -= ((float)WIDTH / 2.);
    //printf("x:%f\ny:%f\n",target_x,target_y);

    // Finds the angle at which the ball is shot
    float angle = -1.*atanf(target_x / target_y) + M_PI_2;
    //printf("Angle: %f\n", angle * (180. / M_PI));

    // Uses the angle to find the initial velocities in the x and y directions
    float vx = INIT_VELOCITY*cos(angle);
    float vy = INIT_VELOCITY*sin(angle);

    // Sets the initial position of the ball at (160,0)
    float x = (float)WIDTH / 2.;
    float y = 0.;

    // Updates the position of the ball after each tick based on the balls velocity and gravity
    while (true) {
        LCD.Clear(Color::Black);
        this->board.drawPegs();

        x += vx*TICK_DURATION;

        vy += GRAVITY_ACCEL*TICK_DURATION;
        y += vy*TICK_DURATION;

        if (y < MIN_BALL_Y) {
            y = MIN_BALL_Y;
            vy = MOMENTUM_LOSS*vy;
        } else if(y > MAX_BALL_Y)
        {
            y = MAX_BALL_Y;
            vy = MOMENTUM_LOSS*vy;
        }

        if (x < MIN_BALL_X) {
            x = MIN_BALL_X;
            vx = MOMENTUM_LOSS*vx;
        } else if (x > MAX_BALL_X) {
            x = MAX_BALL_X;
            vx = MOMENTUM_LOSS*vx;
        }

        for(int i = 0; i < board.getNum(); i++)
        {
            // pegs[i].collisionCheck(x,y,&vx,&vy);
        }
        LCD.DrawCircle((int)x, (int)y, BALL_RADIUS);
        LCD.Update();
    }
}

} // namespace game
} // namespace menu
