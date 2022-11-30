#include <game.hpp>

#include <FEHUtility.h>

#include <cmath>
#include <cstdio>

#include <LCDColors.h>

namespace game {

Ball::Ball() : pos{Screen::CENTER_X, Screen::MIN_Y + Ball::RADIUS + 5}, vel{} {}

void Ball::shootAt(const Position target) {
    // printf("Target: (%.1f, %.1f)\n", target.x, target.y);

    this->vel.y = 100.f;

    // Uses the angle to find the initial velocities in the x and y directions
    const auto timeToTarget = (
        -this->vel.y + std::sqrt(
            std::abs(std::pow(this->vel.y, 2.f) + (2.f * Acceleration::GRAVITY.y * target.y))
        )
    ) / Acceleration::GRAVITY.y;
    // printf("Time to target: %f sec\n", timeToTarget);

    this->vel.x = target.x / timeToTarget;
    // printf("Vel: (%.5f, %.5f)\n", this->vel.x, this->vel.y);
}

Position &Ball::getPos() {
    return this->pos;
}

const Position &Ball::getPos() const {
    return this->pos;
}

Velocity &Ball::getVel() {
    return this->vel;
}

const Velocity &Ball::getVel() const {
    return this->vel;
}

void Ball::tick(const float timeElapsed) {
    Ball::tick(this->vel, this->pos, timeElapsed);
}

bool Ball::isOnScreen() const {
    return (this->pos.y + static_cast<float>(Ball::RADIUS)) <= static_cast<float>(Screen::MAX_Y);
}

float Ball::getWidth() const {
    return static_cast<float>(Ball::RADIUS);
}

float Ball::getHeight() const {
    return static_cast<float>(Ball::RADIUS);
}

Position Ball::getCenter() const {
    return this->pos;
}

void Ball::draw() const {
    LCD.SetFontColor(SADDLEBROWN);
    LCD.FillCircle(
        static_cast<int>(this->pos.x),
        static_cast<int>(this->pos.y),
        static_cast<int>(Ball::RADIUS)
    );
    LCD.SetFontColor(SLATEGRAY);
    LCD.FillCircle(
        static_cast<int>(this->pos.x),
        static_cast<int>(this->pos.y) - 1,
        2
    );
    LCD.SetFontColor(GHOSTWHITE);
    LCD.FillCircle(
        static_cast<int>(this->pos.x) + 1,
        static_cast<int>(this->pos.y) - 1,
        1
    );
}

void Ball::tick(Velocity &vel, Position &pos, const float timeElapsed) {
    Ball::tickX(vel, pos, timeElapsed);
    Ball::tickY(vel, pos, timeElapsed);
}

void Ball::tickX(const Velocity &vel, Position &pos, const float timeElapsed) {
    pos.x += vel.x * timeElapsed;
}

void Ball::tickY(Velocity &vel, Position &pos, const float timeElapsed) {
    vel.y += Acceleration::GRAVITY.y * timeElapsed;
    pos.y += vel.y * timeElapsed;
}

void Ball::drawGuide(const std::vector<Peg> &pegs) {
    auto pos = this->pos;
    auto vel = this->vel;

    for (int i = 0; i < 40; i++) {
        Ball::tick(vel, pos, 0.025f);
        LCD.SetFontColor(GOLDENROD);
        LCD.DrawPixel(static_cast<int>(pos.x), static_cast<int>(pos.y));

        CEILING.checkCollisionWith(vel, pos);
        LEFT_WALL.checkCollisionWith(vel, pos);
        RIGHT_WALL.checkCollisionWith(vel, pos);
        for (const auto &peg : pegs) {
            peg.checkCollisionWith(vel, pos);
        }
    }
}

} // namespace game
