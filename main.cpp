#define _USE_MATH_DEFINES

#include <cstdio>
#include <cmath>
#include <iostream>
#include "FEHLCD.h"
#include "FEHUtility.h"

// Time between screen updates (seconds)
#define TICK_DURATION 0.001

// Acceleration due to gravity
#define GRAVITY_ACCEL 10'000.

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

// Class representing a peg
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

// Class represeting the whole board
class PegBoard
{
    public:
        PegBoard(Peg pegs[100]);
        void drawPegs();
        int getNum();
    private:
        int num_pegs;
        Peg peg_data[100];
};


int main()
{
    // Location of where the player clicks on the screen
    float target_x;
    float target_y;

    // Array of peg locations
    Peg pegs[100];


    // Pegs on the board
    pegs[0] = Peg(5, 200, 5);
    pegs[1] = Peg(15, 200, 5);
    pegs[2] = Peg(25, 200, 5);
    pegs[3] = Peg(35, 200, 5);
    pegs[4] = Peg(45, 200, 5);
    pegs[5] = Peg(55, 200, 5);
    pegs[6] = Peg(65, 200, 5);
    pegs[7] = Peg(75, 200, 5);
    pegs[8] = Peg(85, 200, 5);
    pegs[9] = Peg(95, 200, 5);
    pegs[10] = Peg(105, 200, 5);
    pegs[11] = Peg(115, 200, 5);
    pegs[12] = Peg(125, 200, 5);
    pegs[13] = Peg(135, 200, 5);
    pegs[14] = Peg(145, 200, 5);
    pegs[15] = Peg(155, 200, 5);



    PegBoard board = PegBoard(pegs);
    board.drawPegs();


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
        LCD.Clear(BLACK);
        board.drawPegs();

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
            pegs[i].collisionCheck(x,y,&vx,&vy);
        }
        LCD.DrawCircle((int)x, (int)y, BALL_RADIUS);
        LCD.Update();
    }

    return 0;
}

// Peg class functions

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
PegBoard::PegBoard(Peg pegs[100])
{
    num_pegs = sizeof(pegs);
    for(int i = 0; i < num_pegs; i++)
    {
        peg_data[i] = pegs[i];
    }
}

// Draws every peg in the PegBoard class
void PegBoard::drawPegs()
{
    for(int i = 0; i < num_pegs; i++)
    {
        if(peg_data[i].getStatus() == 1)
        {
            LCD.DrawCircle(peg_data[i].getX(), peg_data[i].getY(),peg_data[i].getRadius());
        }
    }
}

int PegBoard::getNum()
{
    return num_pegs;
}
