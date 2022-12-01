#include <ui.hpp>

#include <screen.hpp>

namespace ui {

FullscreenView::~FullscreenView() {}

float FullscreenView::getWidth() const {
    return static_cast<float>(Screen::WIDTH);
}

float FullscreenView::getHeight() const {
    return static_cast<float>(Screen::HEIGHT);
}

Position FullscreenView::getCenter() const {
    return Screen::CENTER;
}

float FullscreenView::getLeftX() const {
    return static_cast<float>(Screen::MIN_X);
}

float FullscreenView::getRightX() const {
    return static_cast<float>(Screen::MAX_X);
}

float FullscreenView::getTopY() const {
    return static_cast<float>(Screen::MIN_Y);
}

float FullscreenView::getBottomY() const {
    return static_cast<float>(Screen::MAX_Y);
}

Position FullscreenView::getTopLeft() const {
    return Screen::TOP_LEFT;
}

Position FullscreenView::getTopRight() const {
    return Screen::TOP_RIGHT;
}

Position FullscreenView::getBottomLeft() const {
    return Screen::BOTTOM_LEFT;
}

Position FullscreenView::getBottomRight() const {
    return Screen::BOTTOM_RIGHT;
}

} // namespace ui
