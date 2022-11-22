#define _USE_MATH_DEFINES

#include <cstdio>
#include <cmath>

#include "FEHLCD.h"
#include "FEHUtility.h"

#define TICK_DURATION 0.001

#define GRAVITY_ACCEL 200'000.

#define BALL_RADIUS 10

#define MIN_BALL_Y ((float)BALL_RADIUS)
#define MAX_BALL_Y (((float)HEIGHT - 1.0) - (float)BALL_RADIUS)
#define MIN_BALL_X ((float)BALL_RADIUS)
#define MAX_BALL_X (((float)WIDTH - 1.0) - (float)BALL_RADIUS)
#define WIDTH  320
#define HEIGHT 240

#define INIT_VELOCITY 10'000.

int main()
{
    float target_x;
    float target_y;

    while (!LCD.Touch(&target_x, &target_y));

    target_x -= ((float)WIDTH / 2.);
    printf("x:%f\ny:%f\n",target_x,target_y);
    float angle = -1.*atanf(target_x / target_y) + M_PI_2;
    printf("Angle: %f\n", angle * (180. / M_PI));
    float vx = INIT_VELOCITY*cos(angle);
    float vy = INIT_VELOCITY*sin(angle);

    float x = (float)WIDTH / 2.;
    float y = 0.;

    while (true) {
        LCD.Clear(BLACK);

        x += vx*TICK_DURATION;

        vy += GRAVITY_ACCEL*TICK_DURATION;
        y += vy*TICK_DURATION;

        if (y < MIN_BALL_Y) {
            y = MIN_BALL_Y;
            vy = -0.75*vy;
        } else if(y > MAX_BALL_Y)
        {
            y = MAX_BALL_Y;
            vy = -0.75*vy;
        }

        if (x < MIN_BALL_X) {
            x = MIN_BALL_X;
            vx = -0.75*vx;
        } else if (x > MAX_BALL_X) {
            x = MAX_BALL_X;
            vx = -0.75*vx;
        }

        LCD.DrawCircle((int)x, (int)y, BALL_RADIUS);
        LCD.Update();
    }

    return 0;
}
