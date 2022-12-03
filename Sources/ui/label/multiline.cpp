#include <ui.hpp>

#include <FEHLCD.hpp>
#include <font.hpp>

#include <sstream>
#include <utility>

namespace ui {

MultilineLabel::MultilineLabel(
    const Position center,
    const std::string content,
    const Color fontColor
)
: center{center}, fontColor{fontColor}, lines{}
{
    std::stringstream stream{std::move(content)};
    while (stream.good()) {
        std::string line{};
        std::getline(stream, line);
        this->lines.push_back(std::move(line));
    }
}

MultilineLabel::~MultilineLabel() {}

float MultilineLabel::getWidth() const {
    if (this->lines.empty()) {
        return 0.f;
    }

    // Unfortunately we can't use `std::max_element` here, but the semantics are the same: we want
    // to return the greatest width of any label.

    auto greatestWidth = Font::getWidthOf(this->lines.at(0));
    for (auto i = this->lines.begin() + 1; i != this->lines.end(); i++) {
        const auto width = Font::getWidthOf(*i);
        if (width > greatestWidth) {
            greatestWidth = width;
        }
    }

    return static_cast<float>(greatestWidth);
}

float MultilineLabel::getHeight() const {
    const auto lineCount = this->lines.size();

    switch (lineCount) {
        case 0:
            return 0.f;
        case 1:
            return static_cast<float>(Font::HEIGHT);
        default:
            return static_cast<float>(
                ((Font::HEIGHT + Font::VERT_PADDING) * lineCount)
                // Vertical padding only applies between lines, so we counted one too many.
                - Font::VERT_PADDING
            );
    };
}

Position MultilineLabel::getCenter() const {
    return this->center;
}

void MultilineLabel::draw() const {
    LCD.SetFontColor(this->fontColor.encode());

    auto y = this->getTopY();
    for (const auto &line : this->lines) {
        LCD.WriteAt(
            line.c_str(),
            // `Label::getWidth` does not include the left margin, so we need to account for it when
            // choosing the draw position.
            static_cast<int>(this->getLeftX() - static_cast<float>(Font::LEFT_MARGIN)),
            static_cast<int>(y)
        );

        y += static_cast<float>(Font::HEIGHT + Font::VERT_PADDING);
    }
}

} // namespace ui
