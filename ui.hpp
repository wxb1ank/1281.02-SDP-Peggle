#pragma once

#include <cstdlib>
#include <string>

#include "mechanics.hpp"

namespace ui {

struct Size {
    Size(float, float);

    float width;
    float height;
};

class View {
public:
    virtual Size getSize() const {
        return {this->getWidth(), this->getHeight()};
    }

    virtual Position getCenter() const = 0;
    virtual float getWidth() const = 0;
    virtual float getHeight() const = 0;

    float getLeftX() const;
    float getRightX() const;
    float getTopY() const;
    float getBottomY() const;

    Position getTopLeft() const;
    Position getTopRight() const;
    Position getBottomLeft() const;
    Position getBottomRight() const;
};

class Label : public View {
public:
    Label(Position, std::string);

    const std::string &getContent() const {
        return this->content;
    }

    virtual Position getCenter() const {
        return this->center;
    }

    virtual float getWidth() const;
    virtual float getHeight() const;

    void draw() const;

private:
    Position center;
    std::string content;
};

class Button : public View {
public:
    Button(Label);
    Button(Label, Size);

    const Label &getLabel() const {
        return this->label;
    }

    virtual Size getSize() const {
        return this->size;
    }

    virtual Position getCenter() const {
        return this->label.getCenter();
    }

    virtual float getWidth() const {
        return this->size.width;
    }

    virtual float getHeight() const {
        return this->size.height;
    }

    bool isPressed() const;
    bool isPressed(Position) const;

    void drawUnpressed() const;
    void drawPressed() const;

private:
    static constexpr float DEFAULT_PADDING{5.f};

    Label label;
    Size size;

    void drawBorder() const;
    void fillBorder() const;
};

} // namespace ui
