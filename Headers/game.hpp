/// \file
/// \brief Core game logic.

#pragma once

#include <mechanics.hpp>
#include <ui.hpp>

#include <array>
#include <cstdlib>
#include <optional>
#include <vector>

/// \brief Core game logic.
namespace game {

class Obstacle;
class Peg;

/// \brief Lifetime game statistics.
///
/// \author Will Blankemeyer
class Statistics {
public:
    /// \brief Creates a default set of statistics.
    ///
    /// \author Will Blankemeyer
    Statistics();

    /// \brief The total number of wins across all games.
    ///
    /// \return The total wins.
    /// \author Will Blankemeyer
    std::size_t getWins() const;
    /// \brief The total score accumulated across all games.
    ///
    /// \return The total score.
    /// \author Will Blankemeyer
    std::size_t getTotalScore() const;
    /// \brief The top score achieved in any single game.
    ///
    /// \return The top score.
    /// \author Will Blankemeyer
    std::size_t getTopScore() const;
    /// \brief The total number of orange pegs hit across all games.
    ///
    /// \return The total orange pegs hit.
    /// \author Will Blankemeyer
    std::size_t getOrangePegsHit() const;
    /// \brief The total number of balls shot across all games.
    ///
    /// \return The total balls shot.
    /// \author Will Blankemeyer
    std::size_t getBallsShot() const;

    /// \brief Increments the total number of wins by one.
    ///
    /// \author Will Blankemeyer
    void addWin();
    /// \brief Increases the total score by the given amount.
    ///
    /// If the given score is greater than the top score, then it becomes the new top score.
    ///
    /// \param[in]  score   The final score of a game.
    /// \author Will Blankemeyer
    void addScore(std::size_t score);
    /// \brief Increases the total orange pegs hit by the given amount.
    ///
    /// \param[in]  pegsHit The orange pegs hit.
    /// \author Will Blankemeyer
    void addOrangePegsHit(std::size_t pegsHit);
    /// \brief Increases the total balls shot by the given amount.
    ///
    /// \param[in]  ballsShot The balls shot.
    /// \author Will Blankemeyer
    void addBallsShot(std::size_t ballsShot);

private:
    /// \author Will Blankemeyer
    std::size_t wins;
    /// \author Will Blankemeyer
    std::size_t totalScore;
    /// \author Will Blankemeyer
    std::size_t topScore;
    /// \author Will Blankemeyer
    std::size_t orangePegsHit;
    /// \author Will Blankemeyer
    std::size_t ballsShot;
};

/// \brief The Peggle ball.
///
/// \author Solomon Blair
/// \author Will Blankemeyer
class Ball final : public ui::CircleView {
public:
    /// \brief Creates a new Peggle ball in the top-center of the screen.
    ///
    /// \author Will Blankemeyer
    Ball();

    /// \brief The radius, in pixels, of the ball.
    ///
    /// Unlike pegs, which can vary in radius, all Peggle balls are of this radius.
    ///
    /// \author Solomon Blair
    static constexpr size_t RADIUS{3};

    /// \brief The initial Y component of velocity when the ball is shot with `shootAt`.
    ///
    /// \note The X component of velocity varies with angle but the Y component is constant.
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    static constexpr float SHOOT_Y_VEL{4.f * Acceleration::GRAVITY};
    /// \brief The maximum angle, in radians, that a ball can be shot at.
    ///
    /// `pi/2` radians corresponds to shooting horizontal.
    ///
    /// \author Will Blankemeyer
    static constexpr float MAX_SHOOT_ANGLE{1.35f};

    /// \brief Adjusts the velocity of this ball such that it will hit the given target after some
    /// period of time.
    ///
    /// \param[in]  target  The point on the screen that the ball should aim at.
    /// \author Will Blankemeyer
    void shootAt(Position target);

    /// \brief A mutable reference to the position.
    ///
    /// \return The position.
    /// \author Will Blankemeyer
    Position &getPos();
    /// \brief An immutable reference to the position.
    ///
    /// \return The position.
    /// \author Will Blankemeyer
    const Position &getPos() const;

    /// \brief A mutable reference to the velocity.
    ///
    /// \return The velocity.
    /// \author Will Blankemeyer
    Velocity &getVel();
    /// \brief An immutable reference to the velocity.
    ///
    /// \return The velocity.
    /// \author Will Blankemeyer
    const Velocity &getVel() const;

    /// \brief The duration that `tick` operates on.
    ///
    /// \note
    /// \parblock
    /// The unit of tick duration was originally intended to be the second, but our physics system
    /// does not invoke `TimeNow` or `Sleep`, so it is probably related to CPU speed. As such, while
    /// the path a ball takes should be the same on all machines, the speed of the simulation may
    /// vary.
    /// \endparblock
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    static constexpr float TICK_DURATION{Acceleration::GRAVITY / 100.f};

    /// \brief Calculates the new position and velocity of this ball as if a brief duration of time
    /// had elapsed.
    ///
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    void tick();

    /// \brief Determines if the ball is above the bottom of the screen.
    ///
    /// \return Whether or not the ball is on the screen.
    /// \author Will Blankemeyer
    bool isOnScreen() const;

    /// \brief The number of discrete ball positions that `drawGuide` should draw.
    ///
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    static constexpr std::size_t GUIDE_LENGTH{50};

    /// \brief Draws future positions of this ball to the screen.
    ///
    /// Each position is rendered as a single pixel. The number of positions drawn is
    /// `GUIDE_LENGTH`, and the duration between each position is `TICK_DURATION`.
    ///
    /// \param[in]  pegs    All pegs that this simulation should consider for collision checking.
    /// \note This method is `const` and, as such, does not mutate the ball position or velocity.
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    void drawGuide(const std::vector<Peg> &pegs) const;

    /// \author Will Blankemeyer
    virtual float getRadius() const override;
    /// \author Will Blankemeyer
    virtual Position getCenter() const override;
    /// \author Will Blankemeyer
    virtual void draw() const override;

private:
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    Position pos;
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    Velocity vel;

    /// \author Solomon Blair
    /// \author Will Blankemeyer
    static void tick(Velocity &vel, Position &pos);
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    static void tickX(const Velocity &vel, Position &pos);
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    static void tickY(Velocity &vel, Position &pos);
};

/// \brief An immovable object that deflects projectiles upon contact.
///
/// \author Will Blankemeyer
class Obstacle {
public:
    /// \brief Destroys this obstacle.
    ///
    /// \author Will Blankemeyer
    ~Obstacle();

    /// \brief The factor by which the magnitude of the momentum of incoming projectiles is
    /// multipled after contact with an obstacle.
    ///
    /// \author Will Blankemeyer
    static constexpr float MOMENTUM_LOSS{-.90f};

    // TODO: I'm (Will) not a fan of this style where copyable arguments are used for both input and
    // output. If this method instead returned an `std::optional<Deflection>` object where
    // `Deflection` contains the new position and velocity of the projectile, then the caller would
    // not need to put blind faith into this method's claim to only mutate arguments if a deflection
    // occurs. But, we're running short on time, and this is faster to write.

    /// \brief Determines if a projectile is in contact with this obstacle and, if so, deflects the
    /// projectile, adjusting the position and velocity as necessary.
    ///
    /// \param[inout]   vel The velocity of the projectile.
    /// \param[inout]   pos The position of the projectile.
    /// \return Whether or not a collision occurred.
    /// \note `vel` and `pos` are only mutated if a deflection occurs.
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    virtual bool deflect(Velocity &vel, Position &pos) const = 0;
};

/// \brief A flat ceiling obstacle that deflects projectiles downward.
///
/// \author Solomon Blair
/// \author Will Blankemeyer
class Ceiling final : public Obstacle {
public:
    /// \brief Creates a new ceiling.
    ///
    /// \author Will Blankemeyer
    Ceiling();

    /// \author Solomon Blair
    /// \author Will Blankemeyer
    virtual bool deflect(Velocity &vel, Position &pos) const override;
};

/// \brief A flat wall obstacle that deflects projectiles rightward.
///
/// \author Solomon Blair
/// \author Will Blankemeyer
class LeftWall final : public Obstacle {
public:
    /// \brief Creates a new left wall.
    ///
    /// \author Will Blankemeyer
    LeftWall();

    /// \author Solomon Blair
    /// \author Will Blankemeyer
    virtual bool deflect(Velocity &vel, Position &pos) const override;
};

/// \brief A flat wall obstacle that deflects projectiles leftward.
///
/// \author Solomon Blair
/// \author Will Blankemeyer
class RightWall final : public Obstacle {
public:
    /// \brief Creates a new right wall.
    ///
    /// \author Will Blankemeyer
    RightWall();

    /// \author Solomon Blair
    /// \author Will Blankemeyer
    virtual bool deflect(Velocity &vel, Position &pos) const override;
};

/// \brief A global instance of `Ceiling`.
///
/// \author Will Blankemeyer
extern const Ceiling CEILING;
/// \brief A global instance of `LeftWall`.
///
/// \author Will Blankemeyer
extern const LeftWall LEFT_WALL;
/// \brief A global instance of `RightWall`.
///
/// \author Will Blankemeyer
extern const RightWall RIGHT_WALL;

/// \brief A view that translates along the bottom of the screen and returns balls that come into
/// contact with it.
///
/// \author Will Blankemeyer
class Bucket final : public ui::View {
public:
    /// \brief Creates a new bucket in the bottom-center of the screen.
    ///
    /// \author Will Blankemeyer
    Bucket();

    /// \brief Translates this bucket to its next position.
    ///
    /// \author Will Blankemeyer
    void tick();

    /// \brief The size of a bucket.
    ///
    /// \author Will Blankemeyer
    static const ui::Size SIZE;

    /// \author Will Blankemeyer
    virtual ui::Size getSize() const override;
    /// \author Will Blankemeyer
    virtual float getWidth() const override;
    /// \author Will Blankemeyer
    virtual float getHeight() const override;
    /// \author Will Blankemeyer
    virtual Position getCenter() const override;
    /// \author Will Blankemeyer
    virtual void draw() const override;

private:
    /// \author Will Blankemeyer
    Position center;
    /// \author Will Blankemeyer
    float animationProgress;
};

/// \brief Class representing a peg
///
/// \author Solomon Blair
class Peg final : public ui::CircleView, public Obstacle
{
    public:
        enum class Color;

        /// \brief Creates a new peg.
        ///
        /// \param[in]  pos
        /// \param[in]  radius
        /// \param[in]  color
        /// \author Solomon Blair
        /// \author Will Blankemeyer
        Peg(Position pos, float radius, Peg::Color color);

        /// \brief The state of a peg.
        ///
        /// \author Will Blankemeyer
        enum class Status {
            /// \brief This peg has not been hit yet.
            ///
            /// \author Will Blankemeyer
            Unlit,
            /// \brief This peg has been hit but is still visible.
            ///
            /// \author Will Blankemeyer
            Lit,
            /// \brief This peg was hit in a previous round and is now hidden.
            ///
            /// Collision checks are disabled while in this state.
            ///
            /// \author Will Blankemeyer
            Obliterated,
        };

        /// \brief The state of this peg.
        ///
        /// \return The status.
        /// \author Solomon Blair
        /// \author Will Blankemeyer
        Status getStatus() const;
        /// \brief Lights up this peg if it was not hit previously.
        ///
        /// \author Will Blankemeyer
        void hit();
        /// \brief Sets the status of this peg to `Status::Obliterate`.
        ///
        /// \author Will Blankemeyer
        void obliterate();

        /// \brief The color of a peg.
        ///
        /// \author Will Blankemeyer
        enum class Color {
            /// \brief This peg is blue.
            ///
            /// Hitting a blue peg contributes 1 point to the score.
            ///
            /// \author Will Blankemeyer
            Blue,
            /// \brief This peg is orange.
            ///
            /// Hitting an orange peg contributes 2 points to the score, and hitting 25 orange pegs
            /// in a level is a necessary win condition.
            ///
            /// \author Will Blankemeyer
            Orange,
        };

        /// \brief The color of this peg.
        ///
        /// \return The color.
        /// \author Solomon Blair
        /// \author Will Blankemeyer
        Peg::Color getColor() const;

        /// \author Solomon Blair
        virtual float getRadius() const override;
        /// \author Will Blankemeyer
        virtual Position getCenter() const override;
        /// \author Will Blankemeyer
        virtual void draw() const override;
        /// \author Will Blankemeyer
        virtual bool deflect(Velocity &vel, Position &pos) const override;

    private:
        /// \author Solomon Blair
        Position center;
        /// \author Solomon Blair
        float radius;
        /// \author Solomon Blair
        Status status;
        /// \author Solomon Blair
        Peg::Color color;
};

/// \brief Class represeting the whole board
///
/// This is essentially a wrapper over a vector of pegs.
///
/// \author Solomon Blair
class PegBoard : public ui::FullscreenView
{
    public:
        /// \brief Creates an empty peg board.
        ///
        /// \author Solomon Blair
        PegBoard();

        /// \brief Adds a new peg to this board.
        ///
        /// \param[in]  peg The peg to add.
        /// \author Will Blankemeyer
        void push(Peg peg);

        /// \brief A mutable reference to the pegs contained in this board.
        ///
        /// \return All pegs.
        /// \author Solomon Blair
        /// \author Will Blankemeyer
        std::vector<Peg> &getPegs();
        /// \brief An immutable reference to the pegs contained in this board.
        ///
        /// \return All pegs.
        /// \author Solomon Blair
        /// \author Will Blankemeyer
        const std::vector<Peg> &getPegs() const;

        /// \author Solomon Blair
        virtual void draw() const override;

    private:
        /// \author Solomon Blair
        /// \author Will Blankemeyer
        std::vector<Peg> pegs;
};

/// \brief A level of Peggle.
///
/// \author Will Blankemeyer
struct Level {
    /// \brief The name of this level.
    ///
    /// This value is only used for initializing the content of the run button label on the
    /// corresponding level page. If this value is unset, then the label content is initialized with
    /// this level's rank (e.g. 1 for the first level, 2 for the second level).
    ///
    /// \author Will Blankemeyer
    std::optional<std::string> name{};
    /// \brief The radius of all pegs in this level.
    ///
    /// \note The radii of individual pegs cannot be set.
    /// \author Will Blankemeyer
    float pegRadius{3.f};
    /// \brief The number of orange pegs to generate in this level.
    ///
    /// If the length of `pegPositions` is less than this number, then all pegs will be orange.
    ///
    /// \note A standard Peggle level contains 25 orange pegs.
    /// \author Will Blankemeyer
    std::size_t orangePegCount{25};
    /// \brief The positions of all pegs in this level.
    ///
    /// \note Peg positions are unfortunately static; pegs cannot move while a level is being
    /// played.
    /// \author Will Blankemeyer
    std::vector<Position> pegPositions{};

    /// \brief Inserts new peg positions according to the given bitmap.
    ///
    /// The bitmap is encoded as a sequence of lines, delimited by a single line feed character,
    /// each consisting of a sequence of characters of either `0` or `1`. Each `1` corresponds to a
    /// peg whereas each `0` is the absence of a peg.
    ///
    /// \param[in]  topLeft The position of the top-left corner of the bitmap.
    /// \param[in]  bitmap  The bitmap.
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    void addPegBitmap(Position topLeft, const std::string &bitmap);

    /// \brief All levels, in chronological order.
    ///
    /// \author Will Blankemeyer
    static const std::array<Level, 7> ALL;

    /// \brief The first level.
    ///
    /// This is based on the first level in Peggle Deluxe.
    ///
    /// \return Level one.
    /// \author Solomon Blair
    static Level one();
    /// \brief The second level.
    ///
    /// \return Level two.
    /// \author Solomon Blair
    static Level two();
    /// \brief The third level.
    ///
    /// \return Level three.
    /// \author Solomon Blair
    static Level three();
    /// \brief The fourth level.
    ///
    /// \return Level four.
    /// \author Solomon Blair
    static Level four();
    /// \brief The fifth level.
    ///
    /// \return Level five.
    /// \author Solomon Blair
    static Level five();
    /// \brief The sixth level.
    ///
    /// \return Level six.
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    static Level six();
    /// \brief The seventh and final level.
    ///
    /// \return Level seven.
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    static Level amogus();
};

/// \brief That which can play a level.
///
/// \author Will Blankemeyer
class Game {
public:
    /// \brief Creates a new game.
    ///
    /// \author Will Blankemeyer
    Game();

    /// \brief The result of `play`.
    ///
    /// \author Will Blankemeyer
    enum class Result {
        /// \brief The player won the game. Congratulations!
        ///
        /// \author Will Blankemeyer
        Win,
        /// \brief The player lost the game.
        ///
        /// \author Will Blankemeyer
        Loss,
    };

    /// \brief Plays the given level, returning when either all balls have been expended or all
    /// orange pegs have been hit.
    ///
    /// \param[inout]   stats   Lifetime statistics.
    /// \param[in]      level   The level to play.
    /// \return The result of the game.
    /// \author Solomon Blair
    /// \author Will Blankemeyer
    Result play(Statistics &stats, const Level &level);

private:
    /// \author Will Blankemeyer
    ui::BackgroundView background;
    /// \author Will Blankemeyer
    Bucket bucket;
};

} // namespace game

// `game::Game` is tedious to write, so consumers can instead write `Game`.
using game::Game;
