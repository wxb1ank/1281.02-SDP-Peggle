/// \file
/// \brief Newtonian mechanics.

#pragma once

#include <cstdlib>
#include <optional>

/// \brief A two-component vector.
///
/// \author Will Blankemeyer
struct Vector {
    /// \brief Creates the zero vector.
    ///
    /// \author Will Blankemeyer
    Vector();
    /// \brief Creates a new vector.
    ///
    /// \param[in]  x   The X component.
    /// \param[in]  y   The Y component.
    /// \author Will Blankemeyer
    Vector(std::size_t x, std::size_t y);
    /// \brief Creates a new vector.
    ///
    /// \param[in]  x   The X component.
    /// \param[in]  y   The Y component.
    /// \author Will Blankemeyer
    Vector(float x, float y);

    /// \brief The X component.
    ///
    /// \author Will Blankemeyer
    float x;
    /// \brief The Y component.
    ///
    /// \author Will Blankemeyer
    float y;

    /// \brief The magnitude, or length, of this vector.
    ///
    /// \return The magnitude.
    /// \note The return value is always non-negative (i.e. greater than or equal to zero).
    /// \author Will Blankemeyer
    float getMagnitude() const;
};

/// \brief A location in 2D space.
///
/// In a user interface (UI), context, this type may refer specifically to a location on the screen
/// where the X component lies in `[Screen::MIN_X, Screen::MAX_X]` and the Y component lies in
/// `[Screen::MIN_Y, Screen::MAX_Y]`.
///
/// \author Will Blankemeyer
struct Position : Vector {
    // Copy the `Vector` constructors.
    using Vector::Vector;

    /// \brief Returns the position of the current LCD touch.
    ///
    /// If the LCD is not currently touched, then an empty `std::optional` is returned.
    ///
    /// \warning This method updates the LCD.
    /// \return The current touch position.
    /// \author Will Blankemeyer
    static std::optional<Position> getCurrentTouch();
    /// \brief Returns the position of the next LCD touch.
    ///
    /// If the LCD is currently touched, this function immediately returns its position. Otherwise,
    /// this function waits until the next touch is registered and returns that.
    ///
    /// \warning This method updates the LCD.
    /// \return The next touch position.
    /// \author Will Blankemeyer
    static Position getNextTouch();

    /// \brief Returns the angle from this position to the given position.
    ///
    /// If the given position is directly below this position, then the returned angle is 0. If the
    /// given position is to the right of this position, the returned angle is positive; otherwise,
    /// if the given position is to the left of this position, the returned angle is negative. The
    /// maximum returned angle of `M_PI` radians is achieved when the given position is directly
    /// above this position.
    ///
    /// \param[in]  pos The position to which angle is calculated.
    /// \return The angle, in radians.
    /// \author Will Blankemeyer
    float getAngleTo(Position pos) const;
};

/// \brief The first derivative of position.
///
/// \author Will Blankemeyer
struct Velocity : Vector {
    // Copy the `Vector` constructors.
    using Vector::Vector;
};

/// \brief The second derivative of position.
///
/// \author Will Blankemeyer
struct Acceleration : Vector {
    // Copy the `Vector` constructors.
    using Vector::Vector;

    /// \brief The Y component of the acceleration caused by gravity on the world of Peggle.
    ///
    /// \note
    /// \parblock
    /// This value is arbitrary. While it is defined as roughly equivalent to that of Earth in
    /// meters per second per second, the units of gravity in the world of Peggle are *not* the
    /// standard SI units of Earth.
    /// \author Will Blankemeyer
    static constexpr float GRAVITY{9.8f};
};
