#include <ui.hpp>

#include <FEHLCD.hpp>
#include <font.hpp>

namespace ui {

Label::Label(const Position center, const std::string content, const Color fontColor)
: center{center}, content{content}, fontColor{fontColor}
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
    const auto length = this->content.length();

    switch (length) {
        case 0:
            return 0.f;
        case 1:
            return static_cast<float>(Font::WIDTH);
        default:
            return static_cast<float>(
                ((Font::WIDTH + Font::HORI_PADDING) * length)
                // Horizontal padding only applies between characters, so we counted one too many.
                - Font::HORI_PADDING
            );
    };
}

float Label::getHeight() const {
    return static_cast<float>(Font::HEIGHT);
}

Position Label::getCenter() const {
    return this->center;
}

void Label::draw() const {
    LCD.SetFontColor(this->fontColor.encode());
    LCD.WriteAt(
        this->content.c_str(),
        // We need to be careful here. `Label::getWidth` does not include the left margin, so we
        // need to account for it when choosing the draw position.
        static_cast<int>(this->getLeftX() - static_cast<float>(Font::LEFT_MARGIN)),
        // We don't actually need to do anything for the bottom padding, though. The bottom padding
        // seems to only impact the newline functionality offered by `LCD::NextLine.`
        static_cast<int>(this->getTopY())
    );
}

} // namespace ui
