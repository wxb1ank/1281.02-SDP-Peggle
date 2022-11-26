#pragma once

#include <string>

#include "mechanics.hpp"

namespace gfx {

struct Size {
    float width;
    float height;
};

class Button {
public:
    Button(const std::string label, const Position center, const Size size)
        : label{label},
          center{center},
          size{size}
    {}

    const std::string &getLabel() const {
        return this->label;
    }

    Position getCenter() const {
        return this->center;
    }

    Size getSize() const {
        return this->size;
    }

    Position getTopLeft() const;
    Position getTopRight() const;
    Position getBottomLeft() const;
    Position getBottomRight() const;

    bool isPressed() const;
    bool isPressed(Position) const;

    void draw() const;

private:
    std::string label;
    Position center;
    Size size;

    float getLeftX() const;
    float getRightX() const;
    float getTopY() const;
    float getBottomY() const;
};

} // namespace gfx
