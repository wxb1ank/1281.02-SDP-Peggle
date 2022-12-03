#include <game.hpp>

#include <FEHLCD.hpp>

namespace game {

Bucket::Bucket()
:   center{
        static_cast<float>(Screen::CENTER_X),
        static_cast<float>(Screen::MAX_Y) - Ball::RADIUS
    },
    changeX{1.f}
{}

void Bucket::tick() {
    if ((this->getRightX() >= Screen::MAX_X) || (this->getLeftX() <= Screen::MIN_X)) {
        this->changeX *= -1.f;
    }

    this->center.x += this->changeX;
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
        this->getLeftX() + Ball::RADIUS,
        this->getTopY(),
        Bucket::SIZE.width - (2.f * Ball::RADIUS),
        Bucket::SIZE.height
    );
    LCD.SetFontColor(Color::BLACK.encode());
    LCD.FillCircle(this->getLeftX() + Ball::RADIUS, this->getTopY() + Ball::RADIUS, Ball::RADIUS);
    LCD.FillCircle(this->getRightX() - Ball::RADIUS, this->getTopY() + Ball::RADIUS, Ball::RADIUS);
}

const ui::Size Bucket::SIZE{60.f, 2.f * Ball::RADIUS};

} // namespace game
