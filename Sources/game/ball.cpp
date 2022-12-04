#include <game.hpp>

#include <FEHLCD.hpp>

#include <cmath>

namespace game {

Ball::Ball() : pos{Screen::CENTER_X, Screen::MIN_Y + Ball::RADIUS + 5}, vel{} {}

void Ball::shootAt(const Position target) {
    // (Although the angle check will catch this as well, comparing Y coordinates is faster than
    // computing the angle.)
    if (target.y <= this->pos.y) {
        // Uh oh! If our Y velocity points downward, and gravity points downward, then there's no
        // way we could shoot to a point above the ball!
        return;
    }

    // We can't let the player shoot *too* high, because the X velocity necessary to compensate for
    // the low Y velocity would cause the ball to violently dart across the screen and probably
    // break everything.
    if (std::abs(this->pos.getAngleTo(target)) >= Ball::MAX_SHOOT_ANGLE) {
        return;
    }

    this->vel.y = Ball::SHOOT_Y_VEL;

    // Uses the angle to find the initial velocities in the x and y directions.
    //
    // This equation was derived from the following:
    //   y_t = .5 g t^2 + v_y t + y_0
    //     0 = .5 g t^2 + v_y t + (y_0 - y_t)
    //     t = (-v_y +/- (v_y^2 - 4 (.5 g) (y_0 - y_t))^0.5) / (2 (.5 g))        (quadratic formula)
    //       = (-v_y +/- (v_y^2 - 2 g (y_0 - y_t))^0.5) / g
    //       = (-v_y +/- (v_y^2 + 2 g (y_t - y_0))^0.5) / g
    //
    // It turns out that the '+' version of the quadratic equation is the one we want.
    const auto timeToTarget = (
        -this->vel.y + std::sqrt(
            std::pow(this->vel.y, 2.f) + (2.f * Acceleration::GRAVITY * (target.y - this->pos.y))
        )
    ) / Acceleration::GRAVITY;

    // This equation was derived from the following:
    //   x_t = v_x t + x_0
    //     0 = v_x t + (x_0 - x_t)
    //       = v_x + (x_0 - x_t) / t
    //   v_x = -(x_0 - x_t) / t
    //       = (x_t - x_0) / t
    this->vel.x = (target.x - this->pos.x) / timeToTarget;
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

void Ball::tick() {
    Ball::tick(this->vel, this->pos);
}

bool Ball::isOnScreen() const {
    return this->getBottomY() <= static_cast<float>(Screen::MAX_Y);
}

float Ball::getRadius() const {
    return static_cast<float>(Ball::RADIUS);
}

Position Ball::getCenter() const {
    return this->pos;
}

void Ball::draw() const {
    const auto x = static_cast<int>(this->pos.x);
    const auto y = static_cast<int>(this->pos.y);

    // Draw the brownish-reddish reflection on the bottom half of the ball.
    LCD.SetFontColor(Color::SADDLEBROWN.encode());
    LCD.FillCircle(x, y, static_cast<int>(Ball::RADIUS));
    // Draw the main body of the ball.
    LCD.SetFontColor(Color::SLATEGRAY.encode());
    LCD.FillCircle(x, y - 1, 2);
    // Draw the shine.
    LCD.SetFontColor(Color::GHOSTWHITE.encode());
    LCD.FillCircle(x + 1, y - 1, 1);
}

void Ball::tick(Velocity &vel, Position &pos) {
    Ball::tickX(vel, pos);
    Ball::tickY(vel, pos);
}

void Ball::tickX(const Velocity &vel, Position &pos) {
    pos.x += vel.x * Ball::TICK_DURATION;
}

void Ball::tickY(Velocity &vel, Position &pos) {
    vel.y += (Acceleration::GRAVITY * Ball::TICK_DURATION);
    pos.y += vel.y * Ball::TICK_DURATION;
}

void Ball::drawGuide(const std::vector<Peg> &pegs) const {
    auto pos = this->pos;
    auto vel = this->vel;

    for (std::size_t i = 0; i < Ball::GUIDE_LENGTH; i++) {
        Ball::tick(vel, pos);

        if (pos.y > static_cast<float>(Screen::MAX_Y)) {
            return;
        }

        LCD.SetFontColor(Color::LIGHTBLUE.encode());
        LCD.DrawPixel(static_cast<int>(pos.x), static_cast<int>(pos.y));

        CEILING.deflect(vel, pos);
        LEFT_WALL.deflect(vel, pos);
        RIGHT_WALL.deflect(vel, pos);
        for (auto &peg : pegs) {
            if (peg.deflect(vel, pos)) {
                break;
            }
        }
    }
}

} // namespace game
