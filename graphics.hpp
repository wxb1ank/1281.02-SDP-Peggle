#pragma once

#include <cstdlib>
#include <string>

#include "mechanics.hpp"

namespace gfx {

struct Size {
    float width;
    float height;
};

class Button {
public:
    Button(std::string, Position);
    Button(std::string, Position, Size);

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

    void drawUnpressed() const;
    void drawPressed() const;

private:
    static constexpr float DEFAULT_PADDING{5.f};

    std::string label;
    Position center;
    Size size;

    void drawBorder() const;
    void fillBorder() const;
    void drawLabel() const;

    float getLeftX() const;
    float getRightX() const;
    float getTopY() const;
    float getBottomY() const;

    float labelLeft() const;
    float labelTop() const;
};

} // namespace gfx
