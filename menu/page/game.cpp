#define _USE_MATH_DEFINES

#include <cstdio>
#include <cmath>
#include <iostream>

#include <FEHUtility.h>

#include "../../FEHLCD.h"
#include "../../screen.hpp"

#include "game.hpp"

// Acceleration due to gravity
#define GRAVITY_ACCEL 5.

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
#define INIT_VELOCITY 50.

// Momentum lost to a collision
#define MOMENTUM_LOSS -.65

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
void Peg::collisionCheck(float x, float y, float * vx, float * vy) const
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
        float v = sqrt(powf(*vx,2) + powf(*vy,2));
        *vx = MOMENTUM_LOSS * v * cos(collision_angle);
        *vy = MOMENTUM_LOSS * v * sin(collision_angle);
        printf("Y: %f\nX: %f\n", *vy,*vx);
    }
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

Page::Page(const float centerY) : menu::Page{"Game", centerY}, board{} {
    // Pegs on the board
    for (unsigned x = 5; x < 160; x += 10) {
        board.push({x, 200 - x, 5});
    }
}

Color Page::getBackgroundColor() const {
    return Color::BLACK;
}

void Page::drawContent() const {
    board.drawPegs();
}

menu::Page::StepResult Page::step() {
    int ballsRemaining = 10;

    while (ballsRemaining > 0) {
        LCD.Clear(Color::BLACK.encode());
        this->board.drawPegs();
        LCD.WriteAt(ballsRemaining, 15, 15);

        // Location of where the player clicks on the screen
        float target_x;
        float target_y;

        // Shoots ball upon LCD.Touch returning a true value
        while (!LCD.Touch(&target_x, &target_y));

        // Sets (0,0) to be at (160,0)
        target_x -= ((float)WIDTH / 2.);

        float target_angle = M_PI_2 - atanf(target_x / target_y);

        //printf("x:%f\ny:%f\n",target_x,target_y);
        // Sets the initial position of the ball at (160,0)
        float x = (float)WIDTH / 2.;
        float y = 0.;
        // Uses the angle to find the initial velocities in the x and y directions
        float time_to_target = hypotf(target_x,target_y)/INIT_VELOCITY;
        float vx = target_x/time_to_target;
        float vy = (target_y+GRAVITY_ACCEL/2*pow(time_to_target,2))/time_to_target;

        printf("\nTime to target: %f\nTarget X: %f\n Target Y: %f\n Target angle: %f\n",time_to_target, target_x,target_y, target_angle * 180./M_PI);

        // SOMETHING WRONG WITH TIME
        // SOMETHING WRONG WITH TIME
        // SOMETHING WRONG WITH TIME
        // SOMETHING WRONG WITH TIME
        // SOMETHING WRONG WITH TIME
        // SOMETHING WRONG WITH TIME

        double lastTime = TimeNow();
        float tick_duration = 1./30.;
        // Updates the position of the ball after each tick based on the balls velocity and gravity
        while ((y + BALL_RADIUS) <= static_cast<float>(Screen::MAX_Y)) {
            LCD.Clear(Color::BLACK.encode());
            this->board.drawPegs();
            LCD.WriteAt(ballsRemaining, 15, 15);

            //double newTime = TimeNow();
            //double tick_duration = newTime - lastTime;
            //double lastTime = newTime;

            x += vx*tick_duration;

            vy += GRAVITY_ACCEL*tick_duration;
            y += vy*tick_duration;

            if (y < MIN_BALL_Y) {
                y = MIN_BALL_Y;
                vy = MOMENTUM_LOSS*vy;
            }

            if (x < MIN_BALL_X) {
                x = MIN_BALL_X;
                vx = MOMENTUM_LOSS*vx;
            } else if (x > MAX_BALL_X) {
                x = MAX_BALL_X;
                vx = MOMENTUM_LOSS*vx;
            }

            for(auto &peg : this->board.getPegs())
            {
                peg.collisionCheck(x,y,&vx,&vy);
            }
            LCD.DrawCircle((int)x, (int)y, BALL_RADIUS);
            LCD.Update();
        }

        ballsRemaining -=1;
    }

    return menu::Page::StepResult::Return;
}



} // namespace game
} // namespace menu
