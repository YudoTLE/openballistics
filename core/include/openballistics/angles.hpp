#ifndef OPENBALLISTICS_ANGLES_HPP
#define OPENBALLISTICS_ANGLES_HPP

#include "./types.hpp"
#include <Eigen/Dense>
#include <cmath>
#include <algorithm>

namespace openballistics
{
    /// @brief Represents a 3D direction using azimuth and elevation angles.
    /// @details Stores angles in radians. Azimuth is measured in the XY plane from +X toward +Y, and elevation is measured from the XY plane toward +Z.
    class angles
    {
    private:
        scalar m_azimuth;
        scalar m_elevation;

    public:
        /// @brief Creates an angle pair from azimuth and elevation values.
        /// @param azimuth Horizontal angle in the XY plane from +X toward +Y [rad]
        /// @param elevation Vertical angle from the XY plane toward +Z [rad]
        angles(const scalar azimuth, const scalar elevation) noexcept
            : m_azimuth(azimuth),
              m_elevation(elevation)
        {
        }

    public:
        /// @brief Gets the `azimuth`.
        /// @returns Horizontal angle in the XY plane from +X toward +Y [rad]
        [[nodiscard]] scalar azimuth() const noexcept { return m_azimuth; }

        /// @brief Gets the `elevation`.
        /// @returns Vertical angle from the XY plane toward +Z [rad]
        [[nodiscard]] scalar elevation() const noexcept { return m_elevation; }

    public:
        /// @brief Computes azimuth and elevation from a direction vector.
        /// @details Normalizes the input direction before extracting the angles.
        /// @param direction Non-zero direction vector
        /// @returns Angles representing the normalized direction
        [[nodiscard]] static angles from_direction(const Eigen::Vector3d &direction) noexcept
        {
            return from_unit_direction(direction.normalized());
        }

        /// @brief Computes azimuth and elevation from a unit direction vector.
        /// @details Uses the vector components directly and clamps the vertical component to the valid asin domain.
        /// @param unit_direction Normalized direction vector
        /// @returns Angles representing the unit direction
        [[nodiscard]] static angles from_unit_direction(const Eigen::Vector3d &unit_direction) noexcept
        {
            return angles(
                std::atan2(unit_direction.y(), unit_direction.x()),
                std::asin(std::clamp(unit_direction.z(), -1.0, 1.0)));
        }

    public:
        /// @brief Converts the angle pair to a unit direction vector.
        /// @returns 3D unit direction vector represented by the stored angles
        [[nodiscard]] Eigen::Vector3d to_unit_direction() const noexcept
        {
            return Eigen::Vector3d(
                std::cos(m_azimuth) * std::cos(m_elevation),
                std::sin(m_azimuth) * std::cos(m_elevation),
                std::sin(m_elevation));
        }
    };
}

#endif // OPENBALLISTICS_ANGLES_HPP