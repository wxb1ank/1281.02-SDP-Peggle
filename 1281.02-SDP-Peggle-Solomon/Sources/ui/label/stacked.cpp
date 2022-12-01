#include <ui.hpp>

namespace ui {

StackedLabel::StackedLabel(const Label label) : Label{label} {}

StackedLabel::~StackedLabel() {}

void StackedLabel::draw() const {
    LCD.SetFontColor(this->getFontColor().encode());
    for (std::size_t i = 0; i < 3; i++) {
        const auto offset = static_cast<float>(i);
        LCD.WriteAt(
            this->getContent().c_str(),
            static_cast<int>(this->getLeftX() + offset),
            static_cast<int>(this->getTopY() + offset)
        );
    }
}

} // namespace ui
