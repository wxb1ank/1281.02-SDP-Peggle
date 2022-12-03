#include <game.hpp>

namespace game {

Statistics::Statistics()
:   wins{0}, totalScore{0}, topScore{0}, orangePegsHit{0}, ballsShot{0}
{}

std::size_t Statistics::getWins() const {
    return this->wins;
}

std::size_t Statistics::getTotalScore() const {
    return this->totalScore;
}

std::size_t Statistics::getTopScore() const {
    return this->topScore;
}

std::size_t Statistics::getOrangePegsHit() const {
    return this->orangePegsHit;
}

std::size_t Statistics::getBallsShot() const {
    return this->ballsShot;
}

void Statistics::addWin() {
    this->wins += 1;
}

void Statistics::addScore(const std::size_t score) {
    this->totalScore += score;

    if (score > this->topScore) {
        this->topScore = score;
    }
}

void Statistics::addOrangePegsHit(const std::size_t pegsHit) {
    this->orangePegsHit += pegsHit;
}

void Statistics::addBallsShot(const std::size_t ballsShot) {
    this->ballsShot += ballsShot;
}

} // namespace game
