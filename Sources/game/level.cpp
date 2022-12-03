#include <game.hpp>

namespace game {

const std::array<Level, 7> Level::ALL{
    Level::one(),
    Level::two(),
    Level::three(),
    Level::four(),
    Level::five(),
    Level::six(),
    Level::amogus()
};

void Level::addPegBitmap(const Position pos, const std::string &bitmap) {
    auto workingPos = pos;

    for (const auto c : bitmap) {
        switch (c) {
            case '1':
                this->pegPositions.push_back(workingPos);
            case '0':
                workingPos.x += 2.f * this->pegRadius;
                break;
            case '\n':
            default:
                workingPos.x = pos.x;
                workingPos.y += 2.f * this->pegRadius;
                break;
        }
    }
}

} // namespace game
