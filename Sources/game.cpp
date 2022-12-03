#define _USE_MATH_DEFINES

#include <game.hpp>

#include <FEHLCD.hpp>
#include <FEHRandom.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>

namespace game {

Game::Game() : background{Color::BLACK}, bucket{} {}

Game::Result Game::run(game::Statistics &stats, PegBoard &board) {
    std::size_t orangePegsHit = 0;
    std::size_t ballsRemaining = 10;
    std::size_t score = 0;

    while ((ballsRemaining > 0) && (orangePegsHit != 25)) {
        this->background.draw();
        board.drawPegs();
        this->bucket.draw();
        this->bucket.tick();
        LCD.SetFontColor(Color::WHITE.encode());
        LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);

        Ball ball;

        // Location of where the player clicks on the screen
        Position target;
        while (!LCD.Touch(&target.x, &target.y)) {
            this->background.draw();
            board.drawPegs();
            this->bucket.draw();
            this->bucket.tick();
            LCD.SetFontColor(Color::WHITE.encode());
            LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);
        }

        while (LCD.Touch(&target.x, &target.y)) {
            ball.shootAt(target);

            this->background.draw();
            board.drawPegs();
            this->bucket.draw();
            this->bucket.tick();
            LCD.SetFontColor(Color::WHITE.encode());
            LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);
            ball.drawGuide(board.getPegs());

            LCD.ClearBuffer();
        }

        ballsRemaining -=1;
        stats.addBallsShot(1);

        // Updates the position of the ball after each tick based on the balls velocity and gravity
        while (ball.isOnScreen()) {
            this->background.draw();
            board.drawPegs();
            this->bucket.tick();
            LCD.SetFontColor(Color::WHITE.encode());
            LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);

            ball.tick();
            CEILING.deflect(ball.getVel(), ball.getPos());
            LEFT_WALL.deflect(ball.getVel(), ball.getPos());
            RIGHT_WALL.deflect(ball.getVel(), ball.getPos());

            for(auto &peg : board.getPegs())
            {
                if (peg.deflect(ball.getVel(), ball.getPos())) {
                    peg.setStatus(2);
                    break;
                }
            }

            ball.draw();
            this->bucket.draw();
            LCD.Update();
        }

        if ((ball.getLeftX() > this->bucket.getLeftX()) && (ball.getRightX() < this->bucket.getRightX())) {
            ballsRemaining += 1;
        }

        for(auto &peg : board.getPegs())
        {
            if(peg.getStatus() == 2)
            {
                switch (peg.getColor()) {
                    case 0:
                        score += 1;
                        break;
                    default:
                        orangePegsHit += 1;
                        score += 2;
                        break;
                }
                peg.setStatus(0);
            }
        }
        LCD.Update();
    }

    if (orangePegsHit == 25) {
        score += 100;
    }

    stats.addOrangePegsHit(orangePegsHit);
    stats.addScore(score);

    if (orangePegsHit == 25) {
        stats.addWin();
        return Result::Win;
    } else {
        return Result::Loss;
    }
}

} // namespace game
