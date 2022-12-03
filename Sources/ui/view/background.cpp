#include <ui.hpp>

#include <FEHLCD.hpp>

namespace ui {

BackgroundView::BackgroundView(const Color color) : color{color} {}

Color &BackgroundView::getColor() {
    return this->color;
}

const Color &BackgroundView::getColor() const {
    return this->color;
}

void BackgroundView::draw() const {
    // Maybe this is faster than drawing a filled rectangle?
    LCD.Clear(this->color.encode());
}

} // namespace ui
