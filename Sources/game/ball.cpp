#include <game.hpp>

#include <cmath>
#include <cstdio>

namespace game {

Ball::Ball() : pos{Screen::CENTER_X, Screen::MIN_Y + Ball::RADIUS + 5}, vel{} {}

void Ball::shootAt(const Position target) {
    printf("Target: (%.1f, %.1f)\n", target.x, target.y);

    this->vel.y = 100.f;

    // Uses the angle to find the initial velocities in the x and y directions
    const auto timeToTarget = (
        -this->vel.y + std::sqrt(
            std::pow(this->vel.y, 2.f) + (2.f * Acceleration::GRAVITY.y * target.y)
        )
    ) / Acceleration::GRAVITY.y;
    printf("Time to target: %f sec\n", timeToTarget);

    this->vel.x = target.x / timeToTarget;
    printf("Vel: (%.5f, %.5f)\n", this->vel.x, this->vel.y);
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
    this->tickX(timeElapsed);
    this->tickY(timeElapsed);
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
    LCD.DrawCircle(
        static_cast<int>(this->pos.x),
        static_cast<int>(this->pos.y),
        static_cast<int>(Ball::RADIUS)
    );
}

void Ball::tickX(const float timeElapsed) {
    this->pos.x += this->vel.x * timeElapsed;
}

void Ball::tickY(const float timeElapsed) {
    this->vel.y += Acceleration::GRAVITY.y * timeElapsed;
    this->pos.y += this->vel.y * timeElapsed;
}

} // namespace game
