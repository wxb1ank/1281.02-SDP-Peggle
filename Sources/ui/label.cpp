#include <ui.hpp>

#include <font.hpp>

namespace ui {

Label::Label(
    const Position center,
    const std::string content,
    const Background background,
    const Color fontColor
)
:   center{center},
    content{content},
    background{background},
    fontColor{fontColor}
{}

Label::~Label() {}

std::string &Label::getContent() {
    return this->content;
}

const std::string &Label::getContent() const {
    return this->content;
}

Color &Label::getFontColor() {
    return this->fontColor;
}

const Color &Label::getFontColor() const {
    return this->fontColor;
}

float Label::getWidth() const {
    return static_cast<float>(Font::WIDTH * this->content.length());
}

float Label::getHeight() const {
    return static_cast<float>(Font::HEIGHT);
}

Position Label::getCenter() const {
    return this->center;
}

Background &Label::getBackground() {
    return this->background;
}

const Background &Label::getBackground() const {
    return this->background;
}

void Label::drawForeground() const {
    LCD.SetFontColor(this->fontColor.encode());
    LCD.WriteAt(
        this->content.c_str(),
        static_cast<int>(this->getLeftX()),
        static_cast<int>(this->getTopY())
    );
}

} // namespace ui
