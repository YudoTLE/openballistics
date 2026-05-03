#ifndef OPENBALLISTICS_ANGLES_HPP
#define OPENBALLISTICS_ANGLES_HPP

#include "./types.hpp"
#include <Eigen/Dense>
#include <cmath>
#include <algorithm>

namespace openballistics
{
    class angles
    {
    private:
        scalar m_azimuth;
        scalar m_elevation;

    public:
        angles(const scalar azimuth, const scalar elevation) noexcept
            : m_azimuth(azimuth),
              m_elevation(elevation)
        {
        }

    public:
        [[nodiscard]] scalar azimuth() const noexcept { return m_azimuth; }

        [[nodiscard]] scalar elevation() const noexcept { return m_elevation; }

    public:
        [[nodiscard]] static angles from_direction(const Eigen::Vector3d &direction) noexcept
        {
            return from_unit_direction(direction.normalized());
        }

        [[nodiscard]] static angles from_unit_direction(const Eigen::Vector3d &unit_direction) noexcept
        {
            return angles(
                std::atan2(unit_direction.y(), unit_direction.x()),
                std::asin(std::clamp(unit_direction.z(), -1.0, 1.0)));
        }

    public:
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