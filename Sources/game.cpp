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
        board.push(Peg(x, 200 - x, 5));
    }
}

void Game::run() {
    std::size_t ballsRemaining = 10;

    while (ballsRemaining > 0) {
        this->background.draw();
        this->board.drawPegs();
        LCD.SetFontColor(Color::WHITE.encode());
        LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);

        Ball ball;

        // Location of where the player clicks on the screen
        Position target;
        while (!LCD.Touch(&target.x, &target.y));

        while (LCD.Touch(&target.x, &target.y)) {
            target.x -= ball.getPos().x;
            target.y -= ball.getPos().y;
            ball.shootAt(target);

            this->background.draw();
            this->board.drawPegs();
            LCD.SetFontColor(Color::WHITE.encode());
            LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);
            ball.drawGuide(this->board.getPegs());

            LCD.ClearBuffer();
        }

        float target_angle = M_PI_2 - std::atan2(target.y, target.x);

        double lastTime = TimeNow();

        ballsRemaining -=1;

        // Updates the position of the ball after each tick based on the balls velocity and gravity
        while (ball.isOnScreen()) {
            this->background.draw();
            this->board.drawPegs();
            LCD.SetFontColor(Color::WHITE.encode());
            LCD.WriteAt(static_cast<int>(ballsRemaining), 15, 15);

            double newTime = TimeNow();
            const auto tickDuration = static_cast<float>(newTime - lastTime);
            lastTime = newTime;

            ball.tick(tickDuration);
            CEILING.checkCollisionWith(ball.getVel(), ball.getPos());
            LEFT_WALL.checkCollisionWith(ball.getVel(), ball.getPos());
            RIGHT_WALL.checkCollisionWith(ball.getVel(), ball.getPos());

            for(const auto &peg : this->board.getPegs())
            {
                peg.checkCollisionWith(ball.getVel(), ball.getPos());
            }

            ball.draw();
            LCD.Update();
        }
    }
}

} // namespace game
