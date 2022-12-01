#include <ui.hpp>

namespace ui {

BackgroundView::BackgroundView(const Color color) : color{color} {}

Color &BackgroundView::getColor() {
    return this->color;
}

const Color &BackgroundView::getColor() const {
    return this->color;
}

void BackgroundView::draw() const {
    LCD.Clear(this->color.encode());
}

} // namespace ui
