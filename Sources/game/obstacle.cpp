#include <game.hpp>

#include <functional>

namespace game {

Obstacle::~Obstacle() {}

Ceiling::Ceiling() {}

static bool checkFlatCollisionWith(
    Velocity &vel,
    Position &pos,
    const bool condition,
    std::function<void(Position &)> fixPos,
    std::function<float &(Velocity &)> selectVelComp
) {
    if (condition) {
        fixPos(pos);
        selectVelComp(vel) *= Obstacle::MOMENTUM_LOSS;

        return true;
    } else {
        return false;
    }
}

bool Ceiling::deflect(Velocity &vel, Position &pos) const {
    return checkFlatCollisionWith(
        vel,
        pos,
        (pos.y - static_cast<float>(Ball::RADIUS)) < static_cast<float>(Screen::MIN_Y),
        [](Position &pos) { pos.y = static_cast<float>(Screen::MIN_Y + Ball::RADIUS) + 1.f; },
        [](Velocity &vel) -> float & { return vel.y; }
    );
}

LeftWall::LeftWall() {}

bool LeftWall::deflect(Velocity &vel, Position &pos) const {
    return checkFlatCollisionWith(
        vel,
        pos,
        (pos.x - static_cast<float>(Ball::RADIUS)) < static_cast<float>(Screen::MIN_X),
        [](Position &pos) { pos.x = static_cast<float>(Screen::MIN_X + Ball::RADIUS) + 1.f; },
        [](Velocity &vel) -> float & { return vel.x; }
    );
}

RightWall::RightWall() {}

bool RightWall::deflect(Velocity &vel, Position &pos) const {
    return checkFlatCollisionWith(
        vel,
        pos,
        (pos.x + static_cast<float>(Ball::RADIUS)) > static_cast<float>(Screen::MAX_X),
        [](Position &pos) { pos.x = static_cast<float>(Screen::MAX_X - Ball::RADIUS) - 1.f; },
        [](Velocity &vel) -> float & { return vel.x; }
    );
}

const Ceiling CEILING{};
const LeftWall LEFT_WALL{};
const RightWall RIGHT_WALL{};

} // namespace game
