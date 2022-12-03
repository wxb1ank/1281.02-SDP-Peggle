#include <game.hpp>

#include <functional>

namespace game {

Obstacle::~Obstacle() {}

Ceiling::Ceiling() {}

void checkFlatCollisionWith(
    Velocity &vel,
    Position &pos,
    const bool condition,
    std::function<void(Position &)> fixPos,
    std::function<float &(Velocity &)> selectVelComp
) {
    if (condition) {
        fixPos(pos);
        selectVelComp(vel) *= Obstacle::MOMENTUM_LOSS;
    }
}

void Ceiling::deflect(Velocity &vel, Position &pos, int guide) {
    checkFlatCollisionWith(
        vel,
        pos,
        (pos.y - static_cast<float>(Ball::RADIUS)) < static_cast<float>(Screen::MIN_Y),
        [](Position &pos) { pos.y = static_cast<float>(Screen::MIN_Y + Ball::RADIUS) + 1.f; },
        [](Velocity &vel) -> float & { return vel.y; }
    );
}

LeftWall::LeftWall() {}

void LeftWall::deflect(Velocity &vel, Position &pos, int guide) {
    checkFlatCollisionWith(
        vel,
        pos,
        (pos.x - static_cast<float>(Ball::RADIUS)) < static_cast<float>(Screen::MIN_X),
        [](Position &pos) { pos.x = static_cast<float>(Screen::MIN_X + Ball::RADIUS) + 1.f; },
        [](Velocity &vel) -> float & { return vel.x; }
    );
}

RightWall::RightWall() {}

void RightWall::deflect(Velocity &vel, Position &pos, int guide) {
    checkFlatCollisionWith(
        vel,
        pos,
        (pos.x + static_cast<float>(Ball::RADIUS)) > static_cast<float>(Screen::MAX_X),
        [](Position &pos) { pos.x = static_cast<float>(Screen::MAX_X - Ball::RADIUS) - 1.f; },
        [](Velocity &vel) -> float & { return vel.x; }
    );
}

Ceiling CEILING{};
LeftWall LEFT_WALL{};
RightWall RIGHT_WALL{};

} // namespace game
