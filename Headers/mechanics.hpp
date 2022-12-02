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
    /// \author Will Blankemeyer
    float getMagnitude() const;
};

/// \brief A location in 2D space.
///
/// In a user interface (UI), context, this type may also refer to a location on the screen.
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
    /// \author Will Blankemeyer
    static constexpr float GRAVITY{1'000.f};
};
