#include <menu.hpp>

namespace menu {

static const Level LEVEL = []() -> Level {
    Level level{};
    for (int i = 0; i < 50; i++) {
        level.pegPositions.emplace_back(2.f * static_cast<float>(i), 100.f);
    }

    return level;
}();

Level2Page::Level2Page(const float centerY) : LevelPage{"Level 2", centerY, LEVEL} {}

} // namespace menu
