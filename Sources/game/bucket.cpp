// This is necessary for the `M_PI` family of macros.
#define _USE_MATH_DEFINES

#include <game.hpp>

#include <FEHLCD.hpp>

#include <cmath>

namespace game {

Bucket::Bucket()
:   center{
        static_cast<float>(Screen::CENTER_X),
        static_cast<float>(Screen::MAX_Y) - Ball::RADIUS
    },
    animationProgress{0.f}
{}

void Bucket::tick() {
    constexpr float DIFFERENTIAL = 0.01f;

    // This equation was derived from the following:
    //   x     = A sin(t) + A
    //   dx/dt = d(A sin(t))/dt + d(A)/dt
    //         = A d(sin(t))/dt + 0
    //         = A cos(t)
    //   x     = x_0 + dx
    //         = x_0 + dx/dt dt
    //         = x_0 + A cos(t) dt
    //
    // ...where A = 160 - (WIDTH / 2)
    this->center.x += ((static_cast<float>(Screen::WIDTH) / 2.f) - (Bucket::SIZE.width / 2.f)) *
                      std::cos(this->animationProgress) *
                      DIFFERENTIAL;
    this->animationProgress += DIFFERENTIAL;

    const auto tau = 2.f * static_cast<float>(M_PI);
    if (this->animationProgress >= tau) {
        this->animationProgress -= tau;
    }
}

ui::Size Bucket::getSize() const {
    return Bucket::SIZE;
}

float Bucket::getWidth() const {
    return Bucket::SIZE.width;
}

float Bucket::getHeight() const {
    return Bucket::SIZE.height;
}

Position Bucket::getCenter() const {
    return this->center;
}

void Bucket::draw() const {
    LCD.SetFontColor(Color::SILVER.encode());
    LCD.FillRectangle(
        static_cast<int>(this->getLeftX() + static_cast<float>(Ball::RADIUS)),
        static_cast<int>(this->getTopY()),
        static_cast<int>(Bucket::SIZE.width - (2.f * Ball::RADIUS)),
        static_cast<int>(Bucket::SIZE.height)
    );
    LCD.SetFontColor(Color::BLACK.encode());
    LCD.FillCircle(
        static_cast<int>(this->getLeftX() + static_cast<float>(Ball::RADIUS)),
        static_cast<int>(this->getTopY() + static_cast<float>(Ball::RADIUS)),
        static_cast<int>(Ball::RADIUS)
    );
    LCD.FillCircle(
        static_cast<int>(this->getRightX() - static_cast<float>(Ball::RADIUS)),
        static_cast<int>(this->getTopY() + static_cast<float>(Ball::RADIUS)),
        static_cast<int>(Ball::RADIUS)
    );
}

const ui::Size Bucket::SIZE{60.f + (2.f * Ball::RADIUS), 2.f * Ball::RADIUS};

} // namespace game
