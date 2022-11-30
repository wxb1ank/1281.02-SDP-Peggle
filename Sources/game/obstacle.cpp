#include <game.hpp>

#include <functional>

namespace game {

Obstacle::~Obstacle() {}

Ceiling::Ceiling() {}

void checkFlatCollisionWith(
    Ball &ball,
    const bool condition,
    std::function<void(Position &)> fixPos,
    std::function<float &(Velocity &)> selectVelComp
) {
    if (condition) {
        fixPos(ball.getPos());
        selectVelComp(ball.getVel()) *= Obstacle::MOMENTUM_LOSS;
    }
}

void Ceiling::checkCollisionWith(Ball &ball) const {
    checkFlatCollisionWith(
        ball,
        ball.getTopY() < static_cast<float>(Screen::MIN_Y),
        [](Position &pos) { pos.y = static_cast<float>(Screen::MIN_Y - Ball::RADIUS) - 1.f; },
        [](Velocity &vel) -> float & { return vel.y; }
    );
}

LeftWall::LeftWall() {}

void LeftWall::checkCollisionWith(Ball &ball) const {
    checkFlatCollisionWith(
        ball,
        ball.getLeftX() < static_cast<float>(Screen::MIN_X),
        [](Position &pos) { pos.x = static_cast<float>(Screen::MIN_X + Ball::RADIUS) + 1.f; },
        [](Velocity &vel) -> float & { return vel.x; }
    );
}

RightWall::RightWall() {}

void RightWall::checkCollisionWith(Ball &ball) const {
    checkFlatCollisionWith(
        ball,
        ball.getRightX() > static_cast<float>(Screen::MAX_X),
        [](Position &pos) { pos.x = static_cast<float>(Screen::MAX_X - Ball::RADIUS) - 1.f; },
        [](Velocity &vel) -> float & { return vel.x; }
    );
}

const Ceiling CEILING{};
const LeftWall LEFT_WALL{};
const RightWall RIGHT_WALL{};

} // namespace game
