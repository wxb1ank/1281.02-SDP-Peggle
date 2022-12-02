#include <menu.hpp>

#include <game.hpp>

#include <FEHRandom.h>

namespace menu {

LevelPage::LevelPage(
    const std::string name,
    const float centerY,
    std::function<std::vector<Position>()> makeLevel
)
:   Page{name, centerY}, makeLevel{makeLevel}
{}

void LevelPage::run(game::Statistics &stats) {
    int orangePegsToPlace = 25;
    int pegsToPlace = 100;
    int tempColor = 0;

    game::PegBoard board{};
    for (auto pegPos : this->makeLevel()) {
        if(Random.RandInt()%pegsToPlace / pegsToPlace < orangePegsToPlace / pegsToPlace)
        {
            tempColor = 1;
        }
        else{
            tempColor = 0;
        }
        board.push(game::Peg(pegPos.x, pegPos.y, 1, tempColor));
    }

    Game().run(stats, board);
}

} // namespace menu
