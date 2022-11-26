#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdio>

#include <FEHLCD.h>

#include "mechanics.hpp"

float Vector::magnitude() const {
    return std::abs(std::hypotf(this->x, this->y));
}

Position Position::touch() {
    Position target;
    while (!LCD.Touch(&target.x, &target.y));

    return target;
}

float Position::angleTo(const Position other) const {
    const auto x = other.x - this->x;
    const auto y = other.y - this->y;

    const auto angle = M_PI_2 - std::atan(x / y);
    printf("%f deg\n", angle * (180. / M_PI));

    return angle;
}

const Acceleration Acceleration::GRAVITY{0., -200'000.};
