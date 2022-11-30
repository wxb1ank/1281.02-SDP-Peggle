#define _USE_MATH_DEFINES

#include <game.hpp>

#include <FEHLCD.hpp>
#include <FEHUtility.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>

namespace game {

Game::Game() : background{Color::BLACK} {
    // Pegs on the board
    for (unsigned x = 5; x < 160; x += 10) {
        board.push({x, 200 - x, 5});
    }
}

void Game::run() {
    std::size_t ballsRemaining = 10;

    while (ballsRemaining > 0) {
        this->background.draw();
        this->board.drawPegs();
        LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);

        Ball ball;

        // Location of where the player clicks on the screen
        auto target = Position::getNextTouch();
        // Sets (0,0) to be at (160,0)
        target.x -= static_cast<float>(Screen::CENTER_X);

        ball.shootAt(target);

        float target_angle = M_PI_2 - std::atan2(target.y, target.x);

        double lastTime = TimeNow();

        ballsRemaining -=1;

        // Updates the position of the ball after each tick based on the balls velocity and gravity
        while (ball.isOnScreen()) {
            this->background.draw();
            this->board.drawPegs();
            LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);

            double newTime = TimeNow();
            const auto tickDuration = static_cast<float>(newTime - lastTime);
            lastTime = newTime;

            ball.tick(tickDuration);
            ball.checkCollisionWith(CEILING);
            ball.checkCollisionWith(LEFT_WALL);
            ball.checkCollisionWith(RIGHT_WALL);

            for(const auto &peg : this->board.getPegs())
            {
                ball.checkCollisionWith(peg);
            }

            ball.draw();
            LCD.Update();
        }
    }
}

} // namespace game
