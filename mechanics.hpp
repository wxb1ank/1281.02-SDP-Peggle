#pragma once

#include <cstdlib>
#include <optional>

struct Vector {
    Vector();
    Vector(float, float);

    float x;
    float y;

    float magnitude() const;
};

struct Position : Vector {
    using Vector::Vector;

    Position(std::size_t, std::size_t);

    static std::optional<Position> currentTouch();
    static Position nextTouch();

    float angleTo(Position) const;
};

struct Velocity : Vector {
    using Vector::Vector;
};

struct Acceleration : Vector {
    using Vector::Vector;

    static const Acceleration GRAVITY;
};
