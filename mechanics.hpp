#pragma once

struct Vector {
    Vector(const float x = 0., const float y = 0.) : x{x}, y{y} {}

    float x;
    float y;

    float magnitude() const;
};

struct Position : Vector {
    using Vector::Vector;

    static Position touch();

    float angleTo(Position) const;
};

struct Velocity : Vector {
    using Vector::Vector;
};

struct Acceleration : Vector {
    using Vector::Vector;

    static const Acceleration GRAVITY;
};
