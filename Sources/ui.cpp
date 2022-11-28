#include <ui.hpp>

namespace ui {

Background::Background() : visibility{false}, color{Color::BLACK} {}

Background::Background(const Color color) : visibility{true}, color{color} {}

bool Background::isVisible() const {
    return this->visibility;
}

void Background::setVisibility(bool visibility) {
    this->visibility = visibility;
}

void Background::show() {
    this->visibility = true;
}

void Background::hide() {
    this->visibility = false;
}

Color &Background::getColor() {
    return this->color;
}

const Color &Background::getColor() const {
    return this->color;
}

Size::Size(const float width, const float height) : width{width}, height{height} {}

} // namespace ui
