#include <game.hpp>

namespace game {

Obstacle::~Obstacle() {}

Ceiling::Ceiling() {}

std::optional<Velocity> Ceiling::deflectionTo(const Ball &ball) const {
    if (ball.getPos().y < static_cast<float>(Screen::MIN_Y)) {
        auto vel = ball.getVel();
        vel.y *= Obstacle::MOMENTUM_LOSS;

        return std::optional(vel);
    } else {
        return {};
    }
}

LeftWall::LeftWall() {}

std::optional<Velocity> LeftWall::deflectionTo(const Ball &ball) const {
    if (ball.getPos().x < static_cast<float>(Screen::MIN_X)) {
        auto vel = ball.getVel();
        vel.x *= Obstacle::MOMENTUM_LOSS;

        return std::optional(vel);
    } else {
        return {};
    }
}

RightWall::RightWall() {}

std::optional<Velocity> RightWall::deflectionTo(const Ball &ball) const {
    if (ball.getPos().x > static_cast<float>(Screen::MAX_X)) {
        auto vel = ball.getVel();
        vel.x *= Obstacle::MOMENTUM_LOSS;

        return std::optional(vel);
    } else {
        return {};
    }
}

const Ceiling CEILING{};
const LeftWall LEFT_WALL{};
const RightWall RIGHT_WALL{};

} // namespace game
