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
    /// \brief Creates a vector.
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

struct Position : Vector {
    // Copy the `Vector` constructors.
    using Vector::Vector;

    Position(std::size_t, std::size_t);

    static std::optional<Position> getCurrentTouch();
    static Position getNextTouch();

    float getAngleTo(Position) const;
};

struct Velocity : Vector {
    // Copy the `Vector` constructors.
    using Vector::Vector;
};

struct Acceleration : Vector {
    // Copy the `Vector` constructors.
    using Vector::Vector;

    /// \brief The acceleration caused by gravity on the world of Peggle.
    ///
    /// \author Will Blankemeyer
    static const Acceleration GRAVITY;
};
