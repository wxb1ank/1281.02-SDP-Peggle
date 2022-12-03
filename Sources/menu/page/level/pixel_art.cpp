#include <menu.hpp>

namespace menu {

void drawPixelArt(
    int radius,
    int initialXPosition,
    int initialYPosition,
    Level &level,
    const char *amogus,
    int len
) {
    float x = static_cast<float>(initialXPosition);
    float y = static_cast<float>(initialYPosition);

    for (int i = 0; i < len; i++) {
        switch (amogus[i]) {
            case '1':
                level.pegPositions.emplace_back(x, y);
            case '0':
                x += 2.f * radius;
                break;
            default:
                x = initialXPosition;
                y += 2.f * radius;
                break;
        }
    }
}

} // namespace menu
