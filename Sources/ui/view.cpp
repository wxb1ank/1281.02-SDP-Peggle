#include <ui.hpp>

namespace ui {

View::~View() {}

Size View::getSize() const {
    return Size(this->getWidth(), this->getHeight());
}

/// \brief Halves the given number.
///
/// \param[in]  f   A number.
/// \return `f` divided by two.
/// \author Will Blankemeyer
float half(const float f) {
    return f / 2.f;
}

float View::getLeftX() const {
    return this->getCenter().x - half(this->getWidth());
}

float View::getRightX() const {
    return this->getCenter().x + half(this->getWidth());
}

float View::getTopY() const {
    return this->getCenter().y - half(this->getHeight());
}

float View::getBottomY() const {
    return this->getCenter().y + half(this->getHeight());
}

Position View::getTopLeft() const {
    return Position(this->getLeftX(), this->getTopY());
}

Position View::getTopRight() const {
    return Position(this->getRightX(), this->getTopY());
}

Position View::getBottomLeft() const {
    return Position(this->getLeftX(), this->getBottomY());
}

Position View::getBottomRight() const {
    return Position(this->getRightX(), this->getBottomY());
}

bool View::contains(const Position Pos) const {
    if (Pos.x < this->getLeftX()) {
        return false;
    }
    if (Pos.x > this->getRightX()) {
        return false;
    }

    if (Pos.y < this->getTopY()) {
        return false;
    }
    if (Pos.y > this->getBottomY()) {
        return false;
    }

    // We have demonstrated that the given position cannot be outside this view, so it must be
    // inside.
    return true;
}

} // namespace ui
