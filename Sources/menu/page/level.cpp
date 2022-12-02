#include <menu.hpp>

#include <game.hpp>

#include <FEHRandom.h>

#include <algorithm>

namespace menu {

LevelPage::LevelPage(const std::string name, const float centerY, const Level level)
:   Page{name, centerY}, level{level}
{}

void LevelPage::run(game::Statistics &stats) {
    int pegsToPlace = this->level.pegPositions.size();
    int orangePegsToPlace = std::min(25, pegsToPlace);

    game::PegBoard board{};
    for (auto pegPos : this->level.pegPositions) {
        int tempColor = 0;

        if((Random.RandInt()%pegsToPlace) * 1. / pegsToPlace < orangePegsToPlace * 1. / pegsToPlace)
        {
            tempColor = 1;
            orangePegsToPlace -= 1;
        }
        else{
            tempColor = 0;
        }
        board.push(game::Peg(pegPos.x, pegPos.y, 1, tempColor));
        pegsToPlace -= 1;
    }

    Game().run(stats, board);
}

} // namespace menu
