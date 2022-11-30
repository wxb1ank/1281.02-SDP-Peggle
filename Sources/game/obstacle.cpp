#include <game.hpp>

#include <functional>

namespace game {

Obstacle::~Obstacle() {}

Ceiling::Ceiling() {}

std::optional<Velocity> flatDeflectionTo(
    const Ball &ball,
    const bool condition,
    std::function<float &(Velocity &)> selectComp
) {
    if (condition) {
        auto vel = ball.getVel();
        selectComp(vel) *= Obstacle::MOMENTUM_LOSS;

        return std::optional(vel);
    } else {
        return {};
    }
}

std::optional<Velocity> Ceiling::deflectionTo(const Ball &ball) const {
    return flatDeflectionTo(
        ball,
        ball.getTopY() < static_cast<float>(Screen::MIN_Y),
        [](Velocity &vel) -> float & { return vel.y; }
    );
}

LeftWall::LeftWall() {}

std::optional<Velocity> LeftWall::deflectionTo(const Ball &ball) const {
    return flatDeflectionTo(
        ball,
        ball.getLeftX() < static_cast<float>(Screen::MIN_X),
        [](Velocity &vel) -> float & { return vel.x; }
    );
}

RightWall::RightWall() {}

std::optional<Velocity> RightWall::deflectionTo(const Ball &ball) const {
    return flatDeflectionTo(
        ball,
        ball.getRightX() > static_cast<float>(Screen::MAX_X),
        [](Velocity &vel) -> float & { return vel.x; }
    );
}

const Ceiling CEILING{};
const LeftWall LEFT_WALL{};
const RightWall RIGHT_WALL{};

} // namespace game
