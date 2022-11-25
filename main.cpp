#define _USE_MATH_DEFINES

#include <cstdio>
#include <cmath>

#include "FEHLCD.h"
#include "FEHUtility.h"

#define TICK_DURATION 0.001

#define GRAVITY_ACCEL 200'000.

#define MIN_BALL_Y ((float)Ball::RADIUS)
#define MAX_BALL_Y (((float)HEIGHT - 1.0) - (float)Ball::RADIUS)
#define MIN_BALL_X ((float)Ball::RADIUS)
#define MAX_BALL_X (((float)WIDTH - 1.0) - (float)Ball::RADIUS)
#define WIDTH  320
#define HEIGHT 240

bool is_lcd_touched() {
    float trash[2];
    return LCD.Touch(&trash[0], &trash[1]);
}

struct Position {
    float x;
    float y;

    static Position target() {
        while (!is_lcd_touched());

        Position target;
        while (LCD.Touch(&target.x, &target.y));

        return target;
    }

    float angle_to(const Position other) const {
        const float x = other.x - this->x;
        const float y = other.y - this->y;

        const float angle = M_PI_2 - atanf(x / y);
        printf("%f deg\n", angle * (180. / M_PI));

        return angle;
    }
};

struct Velocity {
    float x;
    float y;

    float magnitude() const {
        return std::abs(hypotf(this->x, this->y));
    }
};

class Ball {
public:
    static constexpr size_t RADIUS{4};

    void shoot(const float angle) {
        const float mag = this->vel.magnitude();
        this->vel.x = mag * cos(angle);
        this->vel.y = mag * sin(angle);
    }

    void shoot_at(const Position target) {
        this->shoot(this->pos.angle_to(target));
    }

    void tick() {
        this->tick_x();
        this->tick_y();

        // TODO


        if (this->pos.y < MIN_BALL_Y) {
            this->pos.y = MIN_BALL_Y;
            this->vel.y *= -0.75;
        } else if(this->pos.y > MAX_BALL_Y) {
            this->pos.y = MAX_BALL_Y;
            this->vel.y *= -0.75;
        }

        if (this->pos.x < MIN_BALL_X) {
            this->pos.x = MIN_BALL_X;
            this->vel.x *= -0.75;
        } else if (this->pos.x > MAX_BALL_X) {
            this->pos.x = MAX_BALL_X;
            this->vel.x *= -0.75;
        }
    }

    void draw() const {
        LCD.DrawCircle((int)this->pos.x, (int)this->pos.y, (int)Ball::RADIUS);
    }

private:
    Position pos{(float)WIDTH / 2., 0.};
    Velocity vel{0., 10'000.};

    void tick_x() {
        this->pos.x += this->vel.x * TICK_DURATION;
    }

    void tick_y() {
        this->vel.y += GRAVITY_ACCEL * TICK_DURATION;
        this->pos.y += this->vel.y * TICK_DURATION;
    }
};

class HasHitbox {
public:
    virtual bool collides_with(const Ball &);

    virtual Velocity deflection();
};

class Wall : HasHitbox {

};

class Peg : HasHitbox {
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

int main()
{
    Ball ball;
    ball.draw();
    ball.shoot_at(Position::target());

    while (true) {
        LCD.Clear(BLACK);

        if (is_lcd_touched()) {
            ball.shoot_at(Position::target());
        } else {
            ball.tick();
        }

        ball.draw();
        LCD.Update();
    }

    return 0;
}
