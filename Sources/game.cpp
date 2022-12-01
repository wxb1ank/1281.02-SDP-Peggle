#define _USE_MATH_DEFINES

#include <game.hpp>

#include <FEHLCD.hpp>
#include <FEHRandom.h>
#include <FEHUtility.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>

namespace game {

Statistics::Statistics() : totalScore{0}, topScore{0}, orangePegsHit{0}, ballsShot{0} {}

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

void Statistics::addScore(std::size_t score) {
    this->totalScore += score;

    if (score > this->topScore) {
        this->topScore = score;
    }
}

void Statistics::addOrangePegsHit(std::size_t pegsHit) {
    this->orangePegsHit += pegsHit;
}

void Statistics::addBallsShot(std::size_t ballsShot) {
    this->ballsShot += ballsShot;
}

Bucket::Bucket() : center{static_cast<float>(Screen::CENTER_X), static_cast<float>(Screen::MAX_Y) - (Bucket::SIZE.height / 2.f)}, changeX{1.f} {}

void Bucket::tick() {
    if ((this->getRightX() >= Screen::MAX_X) || (this->getLeftX() <= Screen::MIN_X)) {
        this->changeX *= -1.f;
    }

    this->center.x += this->changeX;
}

float Bucket::getWidth() const {
    return Bucket::SIZE.width;
}

float Bucket::getHeight() const {
    return Bucket::SIZE.height;
}

Position Bucket::getCenter() const {
    return this->center;
}

void Bucket::draw() const {
    LCD.SetFontColor(Color::RED.encode());
    LCD.FillRectangle(this->getLeftX(), this->getTopY(), Bucket::SIZE.width, Bucket::SIZE.height);
}

const ui::Size Bucket::SIZE{60, 5};

Game::Game() : background{Color::BLACK}, bucket{} {}

void Game::run(game::Statistics &stats) {

    int orangePegsToPlace = 25;
    int pegsToPlace = 100;
    int tempColor = 0;
    // Pegs on the board
    for (unsigned x = 1; x < 200; x += 2) {
        if(Random.RandInt()%pegsToPlace / pegsToPlace < orangePegsToPlace / pegsToPlace)
        {
            tempColor = 1;
        }
        else{
            tempColor = 0;
        }
        board.push(Peg(x, 200, 1, tempColor));
    }

    std::size_t ballsRemaining = 10;
    std::size_t score = 0;

    while (ballsRemaining > 0) {
        this->background.draw();
        this->board.drawPegs();
        this->bucket.draw();
        this->bucket.tick();
        LCD.SetFontColor(Color::WHITE.encode());
        LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);

        Ball ball;

        // Location of where the player clicks on the screen
        Position target;
        while (!LCD.Touch(&target.x, &target.y)) {
            this->background.draw();
            this->board.drawPegs();
            this->bucket.draw();
            this->bucket.tick();
            LCD.SetFontColor(Color::WHITE.encode());
            LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);
        }

        while (LCD.Touch(&target.x, &target.y)) {
            target.x -= ball.getPos().x;
            target.y -= ball.getPos().y;
            ball.shootAt(target);

            this->background.draw();
            this->board.drawPegs();
            this->bucket.draw();
            this->bucket.tick();
            LCD.SetFontColor(Color::WHITE.encode());
            LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);
            ball.drawGuide(this->board.getPegs());

            LCD.ClearBuffer();
        }

        float target_angle = M_PI_2 - std::atan2(target.y, target.x);

        double lastTime = TimeNow();

        ballsRemaining -=1;
        stats.addBallsShot(1);

        // Updates the position of the ball after each tick based on the balls velocity and gravity
        while (ball.isOnScreen()) {
            this->background.draw();
            this->board.drawPegs();
            this->bucket.draw();
            this->bucket.tick();
            LCD.SetFontColor(Color::WHITE.encode());
            LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);

            double newTime = TimeNow();
            const auto tickDuration = static_cast<float>(newTime - lastTime);
            lastTime = newTime;

            ball.tick(tickDuration);
            CEILING.checkCollisionWith(ball.getVel(), ball.getPos(), 0);
            LEFT_WALL.checkCollisionWith(ball.getVel(), ball.getPos(), 0);
            RIGHT_WALL.checkCollisionWith(ball.getVel(), ball.getPos(), 0);

            for(auto &peg : this->board.getPegs())
            {
                peg.checkCollisionWith(ball.getVel(), ball.getPos(), 0);
            }

            ball.draw();
            LCD.Update();
        }

        if ((ball.getLeftX() > this->bucket.getLeftX()) && (ball.getRightX() < this->bucket.getRightX())) {
            ballsRemaining += 1;
        }

        for(auto &peg : this->board.getPegs())
        {
            if(peg.getStatus() == 2)
            {
                switch (peg.getColor()) {
                    case 0:
                        score += 1;
                        break;
                    default:
                        stats.addOrangePegsHit(1);
                        score += 2;
                        break;
                }
                peg.setStatus(0);
            }
        }
        LCD.Update();
    }

    stats.addScore(score);
}

} // namespace game
