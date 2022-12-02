#include <ui.hpp>

namespace ui {

Size::Size(const std::size_t width, const std::size_t height)
:   width{static_cast<float>(width)}, height{static_cast<float>(height)}
{}

Size::Size(const float width, const float height) : width{width}, height{height} {}

} // namespace ui
