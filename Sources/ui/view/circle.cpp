#include <ui.hpp>

namespace ui {

CircleView::~CircleView() {}

float CircleView::getDiameter() const {
    return 2.f * this->getRadius();
}

float CircleView::getWidth() const {
    return this->getDiameter();
}

float CircleView::getHeight() const {
    return this->getDiameter();
}

} // namespace ui
