#include <menu.hpp>

#include <game.hpp>

#include <FEHRandom.h>

#include <algorithm>

namespace menu {

LevelPage::LevelPage(const std::string name, const float centerY, const Level level)
:   Page{name, centerY}, level{level}
{}

void LevelPage::run(game::Statistics &stats) {
    auto pegsToPlace = this->level.pegPositions.size();
    auto orangePegsToPlace = std::min(this->level.orangePegCount, pegsToPlace);

    game::PegBoard board{};
    for (auto pegPos : this->level.pegPositions) {
        int color;

        if((Random.RandInt()%pegsToPlace) * 1. / pegsToPlace < orangePegsToPlace * 1. / pegsToPlace)
        {
            color = 1;
            orangePegsToPlace -= 1;
        }
        else{
            color = 0;
        }
        board.push(game::Peg(pegPos.x, pegPos.y, this->level.pegRadius, color));
        pegsToPlace -= 1;
    }

    Game().run(stats, board);
}

} // namespace menu
