#ifndef OPENBALLISTICS_PROJECTILE_REALISTIC_HPP
#define OPENBALLISTICS_PROJECTILE_REALISTIC_HPP

#include "../types.hpp"
#include "../interpolator/lazy_linear.hpp"
#include <boost/math/interpolators/pchip.hpp>
#include <algorithm>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>
#include <optional>

namespace openballistics::projectile
{
	class realistic
	{
	public:
		[[nodiscard]] static realistic m56a3()
		{
			constexpr double mass = 0.10141;									   // kg    (101.41 gm)
			constexpr double diameter = 0.02;									   // m     (20mm)
			constexpr double referenceArea = 3.14159265358979323846 * 0.01 * 0.01; // m²    (π·r², r = 10mm)
			constexpr double axialMomentOfInertia = 5.478e-6;					   // kg·m² (54.78 gm·cm²)

			return realistic{}
				.set_mass(mass)
				.set_diameter(diameter)
				.set_reference_area(referenceArea)
				.set_axial_moment_of_inertia(axialMomentOfInertia)
				.set_drag_force_coefficient(
					{0.000, 0.620, 0.780, 0.870, 0.930, 0.950,
					 1.020, 1.060, 1.100, 1.200, 1.310, 1.380,
					 1.530, 1.700, 2.030, 2.475, 3.000, 3.500},
					{0.2800, 0.2756, 0.2700, 0.2470, 0.2860, 0.3090,
					 0.5260, 0.5590, 0.5680, 0.5760, 0.5700, 0.5610,
					 0.5280, 0.5080, 0.4830, 0.4280, 0.3860, 0.3570})
				.set_lift_force_coefficient(
					{0.0, 0.9, 1.1, 1.3, 1.6, 2.0, 2.4, 3.4, 3.5},
					{1.944, 1.944, 1.923, 2.100, 2.311, 2.484, 2.554, 2.317, 2.283})
				.set_overturning_moment_coefficient(
					{0.00, 0.40, 0.60, 0.71, 0.85, 0.96,
					 1.06, 1.15, 2.20, 2.70, 3.10, 3.30, 3.50},
					{2.48, 2.48, 2.54, 2.60, 2.76, 3.07,
					 2.80, 2.72, 2.16, 1.93, 1.80, 1.77, 1.75})
				.set_spin_damping_moment_coefficient(0.013)
				.set_magnus_force_coefficient(0.0);
		}

	public:
		realistic()
		{
#pragma region "CODEGEN PROJ-R-DEF" // AUTO-GENERATED - DO NOT EDIT MANUALLY

#pragma endregion "CODEGEN PROJ-R-DEF"
		}

	public:
#pragma region "CODEGEN PROJ-R-SET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		realistic &set_mass(const scalar value)
		{
			m_mass_constant = value;
			m_mass_source = 1;
			return *this;
		}

		realistic &set_diameter(const scalar value)
		{
			m_diameter_constant = value;
			m_diameter_source = 1;
			return *this;
		}

		realistic &set_reference_area(const scalar value)
		{
			m_reference_area_constant = value;
			m_reference_area_source = 1;
			return *this;
		}

		realistic &set_axial_moment_of_inertia(const scalar value)
		{
			m_axial_moment_of_inertia_constant = value;
			m_axial_moment_of_inertia_source = 1;
			return *this;
		}

		realistic &set_drag_force_coefficient(const scalar value)
		{
			m_drag_force_coefficient_constant = value;
			m_drag_force_coefficient_source = 1;
			return *this;
		}
		realistic &set_drag_force_coefficient(scalar (*curve)(scalar))
		{
			m_drag_force_coefficient_curve = curve;
			m_drag_force_coefficient_source = 2;
			return *this;
		}
		realistic &set_drag_force_coefficient(std::function<scalar(scalar)> curve)
		{
			m_drag_force_coefficient_curve_virtual = std::move(curve);
			m_drag_force_coefficient_source = 3;
			return *this;
		}
		realistic &set_drag_force_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_drag_force_coefficient_curve_interpolator = interpolator::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_drag_force_coefficient_source = 4;
			return *this;
		}
		realistic &set_drag_force_coefficient(std::vector<scalar> machs, std::vector<scalar> values)
		{
			m_drag_force_coefficient_table_min = machs.front();
			m_drag_force_coefficient_table_max = machs.back();
			m_drag_force_coefficient_table = boost::math::interpolators::pchip<std::vector<scalar>>(std::move(machs), std::move(values));
			m_drag_force_coefficient_source = 5;
			return *this;
		}

		realistic &set_lift_force_coefficient(const scalar value)
		{
			m_lift_force_coefficient_constant = value;
			m_lift_force_coefficient_source = 1;
			return *this;
		}
		realistic &set_lift_force_coefficient(scalar (*curve)(scalar))
		{
			m_lift_force_coefficient_curve = curve;
			m_lift_force_coefficient_source = 2;
			return *this;
		}
		realistic &set_lift_force_coefficient(std::function<scalar(scalar)> curve)
		{
			m_lift_force_coefficient_curve_virtual = std::move(curve);
			m_lift_force_coefficient_source = 3;
			return *this;
		}
		realistic &set_lift_force_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_lift_force_coefficient_curve_interpolator = interpolator::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_lift_force_coefficient_source = 4;
			return *this;
		}
		realistic &set_lift_force_coefficient(std::vector<scalar> machs, std::vector<scalar> values)
		{
			m_lift_force_coefficient_table_min = machs.front();
			m_lift_force_coefficient_table_max = machs.back();
			m_lift_force_coefficient_table = boost::math::interpolators::pchip<std::vector<scalar>>(std::move(machs), std::move(values));
			m_lift_force_coefficient_source = 5;
			return *this;
		}

		realistic &set_overturning_moment_coefficient(const scalar value)
		{
			m_overturning_moment_coefficient_constant = value;
			m_overturning_moment_coefficient_source = 1;
			return *this;
		}
		realistic &set_overturning_moment_coefficient(scalar (*curve)(scalar))
		{
			m_overturning_moment_coefficient_curve = curve;
			m_overturning_moment_coefficient_source = 2;
			return *this;
		}
		realistic &set_overturning_moment_coefficient(std::function<scalar(scalar)> curve)
		{
			m_overturning_moment_coefficient_curve_virtual = std::move(curve);
			m_overturning_moment_coefficient_source = 3;
			return *this;
		}
		realistic &set_overturning_moment_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_overturning_moment_coefficient_curve_interpolator = interpolator::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_overturning_moment_coefficient_source = 4;
			return *this;
		}
		realistic &set_overturning_moment_coefficient(std::vector<scalar> machs, std::vector<scalar> values)
		{
			m_overturning_moment_coefficient_table_min = machs.front();
			m_overturning_moment_coefficient_table_max = machs.back();
			m_overturning_moment_coefficient_table = boost::math::interpolators::pchip<std::vector<scalar>>(std::move(machs), std::move(values));
			m_overturning_moment_coefficient_source = 5;
			return *this;
		}

		realistic &set_spin_damping_moment_coefficient(const scalar value)
		{
			m_spin_damping_moment_coefficient_constant = value;
			m_spin_damping_moment_coefficient_source = 1;
			return *this;
		}
		realistic &set_spin_damping_moment_coefficient(scalar (*curve)(scalar))
		{
			m_spin_damping_moment_coefficient_curve = curve;
			m_spin_damping_moment_coefficient_source = 2;
			return *this;
		}
		realistic &set_spin_damping_moment_coefficient(std::function<scalar(scalar)> curve)
		{
			m_spin_damping_moment_coefficient_curve_virtual = std::move(curve);
			m_spin_damping_moment_coefficient_source = 3;
			return *this;
		}
		realistic &set_spin_damping_moment_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_spin_damping_moment_coefficient_curve_interpolator = interpolator::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_spin_damping_moment_coefficient_source = 4;
			return *this;
		}
		realistic &set_spin_damping_moment_coefficient(std::vector<scalar> machs, std::vector<scalar> values)
		{
			m_spin_damping_moment_coefficient_table_min = machs.front();
			m_spin_damping_moment_coefficient_table_max = machs.back();
			m_spin_damping_moment_coefficient_table = boost::math::interpolators::pchip<std::vector<scalar>>(std::move(machs), std::move(values));
			m_spin_damping_moment_coefficient_source = 5;
			return *this;
		}

		realistic &set_magnus_force_coefficient(const scalar value)
		{
			m_magnus_force_coefficient_constant = value;
			m_magnus_force_coefficient_source = 1;
			return *this;
		}
		realistic &set_magnus_force_coefficient(scalar (*curve)(scalar))
		{
			m_magnus_force_coefficient_curve = curve;
			m_magnus_force_coefficient_source = 2;
			return *this;
		}
		realistic &set_magnus_force_coefficient(std::function<scalar(scalar)> curve)
		{
			m_magnus_force_coefficient_curve_virtual = std::move(curve);
			m_magnus_force_coefficient_source = 3;
			return *this;
		}
		realistic &set_magnus_force_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_magnus_force_coefficient_curve_interpolator = interpolator::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_magnus_force_coefficient_source = 4;
			return *this;
		}
		realistic &set_magnus_force_coefficient(std::vector<scalar> machs, std::vector<scalar> values)
		{
			m_magnus_force_coefficient_table_min = machs.front();
			m_magnus_force_coefficient_table_max = machs.back();
			m_magnus_force_coefficient_table = boost::math::interpolators::pchip<std::vector<scalar>>(std::move(machs), std::move(values));
			m_magnus_force_coefficient_source = 5;
			return *this;
		}
#pragma endregion "CODEGEN PROJ-R-SET"

#pragma region "CODEGEN PROJ-R-GET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		[[nodiscard]] scalar mass() const
		{
			if (m_mass_source == 1) return m_mass_constant;
			throw std::bad_optional_access{};
		}

		[[nodiscard]] scalar diameter() const
		{
			if (m_diameter_source == 1) return m_diameter_constant;
			throw std::bad_optional_access{};
		}

		[[nodiscard]] scalar reference_area() const
		{
			if (m_reference_area_source == 1) return m_reference_area_constant;
			throw std::bad_optional_access{};
		}

		[[nodiscard]] scalar axial_moment_of_inertia() const
		{
			if (m_axial_moment_of_inertia_source == 1) return m_axial_moment_of_inertia_constant;
			throw std::bad_optional_access{};
		}

		[[nodiscard]] scalar drag_force_coefficient(const scalar mach) const
		{
			switch (m_drag_force_coefficient_source)
			{
			case 1: return m_drag_force_coefficient_constant;
			case 2: return m_drag_force_coefficient_curve(mach);
			case 3: return m_drag_force_coefficient_curve_virtual(mach);
			case 4: return m_drag_force_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_drag_force_coefficient_table(std::clamp(mach, m_drag_force_coefficient_table_min, m_drag_force_coefficient_table_max));
			default: throw std::bad_optional_access{};
			}
		}

		[[nodiscard]] scalar lift_force_coefficient(const scalar mach) const
		{
			switch (m_lift_force_coefficient_source)
			{
			case 1: return m_lift_force_coefficient_constant;
			case 2: return m_lift_force_coefficient_curve(mach);
			case 3: return m_lift_force_coefficient_curve_virtual(mach);
			case 4: return m_lift_force_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_lift_force_coefficient_table(std::clamp(mach, m_lift_force_coefficient_table_min, m_lift_force_coefficient_table_max));
			default: throw std::bad_optional_access{};
			}
		}

		[[nodiscard]] scalar overturning_moment_coefficient(const scalar mach) const
		{
			switch (m_overturning_moment_coefficient_source)
			{
			case 1: return m_overturning_moment_coefficient_constant;
			case 2: return m_overturning_moment_coefficient_curve(mach);
			case 3: return m_overturning_moment_coefficient_curve_virtual(mach);
			case 4: return m_overturning_moment_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_overturning_moment_coefficient_table(std::clamp(mach, m_overturning_moment_coefficient_table_min, m_overturning_moment_coefficient_table_max));
			default: throw std::bad_optional_access{};
			}
		}

		[[nodiscard]] scalar spin_damping_moment_coefficient(const scalar mach) const
		{
			switch (m_spin_damping_moment_coefficient_source)
			{
			case 1: return m_spin_damping_moment_coefficient_constant;
			case 2: return m_spin_damping_moment_coefficient_curve(mach);
			case 3: return m_spin_damping_moment_coefficient_curve_virtual(mach);
			case 4: return m_spin_damping_moment_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_spin_damping_moment_coefficient_table(std::clamp(mach, m_spin_damping_moment_coefficient_table_min, m_spin_damping_moment_coefficient_table_max));
			default: throw std::bad_optional_access{};
			}
		}

		[[nodiscard]] scalar magnus_force_coefficient(const scalar mach) const
		{
			switch (m_magnus_force_coefficient_source)
			{
			case 1: return m_magnus_force_coefficient_constant;
			case 2: return m_magnus_force_coefficient_curve(mach);
			case 3: return m_magnus_force_coefficient_curve_virtual(mach);
			case 4: return m_magnus_force_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_magnus_force_coefficient_table(std::clamp(mach, m_magnus_force_coefficient_table_min, m_magnus_force_coefficient_table_max));
			default: throw std::bad_optional_access{};
			}
		}
#pragma endregion "CODEGEN PROJ-R-GET"

	private:
#pragma region "CODEGEN PROJ-R-MEM" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		bool m_mass_source = 0;
		scalar m_mass_constant;

		bool m_diameter_source = 0;
		scalar m_diameter_constant;

		bool m_reference_area_source = 0;
		scalar m_reference_area_constant;

		bool m_axial_moment_of_inertia_source = 0;
		scalar m_axial_moment_of_inertia_constant;

		uint8_t m_drag_force_coefficient_source = 0;
		scalar m_drag_force_coefficient_constant;
		scalar (*m_drag_force_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_drag_force_coefficient_curve_virtual;
		interpolator::lazy_linear<scalar> m_drag_force_coefficient_curve_interpolator;
		boost::math::interpolators::pchip<std::vector<scalar>> m_drag_force_coefficient_table{{1.0, 2.0, 3.0, 4.0}, {0.0, 0.0, 0.0, 0.0}};
		scalar m_drag_force_coefficient_table_min;
		scalar m_drag_force_coefficient_table_max;

		uint8_t m_lift_force_coefficient_source = 0;
		scalar m_lift_force_coefficient_constant;
		scalar (*m_lift_force_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_lift_force_coefficient_curve_virtual;
		interpolator::lazy_linear<scalar> m_lift_force_coefficient_curve_interpolator;
		boost::math::interpolators::pchip<std::vector<scalar>> m_lift_force_coefficient_table{{1.0, 2.0, 3.0, 4.0}, {0.0, 0.0, 0.0, 0.0}};
		scalar m_lift_force_coefficient_table_min;
		scalar m_lift_force_coefficient_table_max;

		uint8_t m_overturning_moment_coefficient_source = 0;
		scalar m_overturning_moment_coefficient_constant;
		scalar (*m_overturning_moment_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_overturning_moment_coefficient_curve_virtual;
		interpolator::lazy_linear<scalar> m_overturning_moment_coefficient_curve_interpolator;
		boost::math::interpolators::pchip<std::vector<scalar>> m_overturning_moment_coefficient_table{{1.0, 2.0, 3.0, 4.0}, {0.0, 0.0, 0.0, 0.0}};
		scalar m_overturning_moment_coefficient_table_min;
		scalar m_overturning_moment_coefficient_table_max;

		uint8_t m_spin_damping_moment_coefficient_source = 0;
		scalar m_spin_damping_moment_coefficient_constant;
		scalar (*m_spin_damping_moment_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_spin_damping_moment_coefficient_curve_virtual;
		interpolator::lazy_linear<scalar> m_spin_damping_moment_coefficient_curve_interpolator;
		boost::math::interpolators::pchip<std::vector<scalar>> m_spin_damping_moment_coefficient_table{{1.0, 2.0, 3.0, 4.0}, {0.0, 0.0, 0.0, 0.0}};
		scalar m_spin_damping_moment_coefficient_table_min;
		scalar m_spin_damping_moment_coefficient_table_max;

		uint8_t m_magnus_force_coefficient_source = 0;
		scalar m_magnus_force_coefficient_constant;
		scalar (*m_magnus_force_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_magnus_force_coefficient_curve_virtual;
		interpolator::lazy_linear<scalar> m_magnus_force_coefficient_curve_interpolator;
		boost::math::interpolators::pchip<std::vector<scalar>> m_magnus_force_coefficient_table{{1.0, 2.0, 3.0, 4.0}, {0.0, 0.0, 0.0, 0.0}};
		scalar m_magnus_force_coefficient_table_min;
		scalar m_magnus_force_coefficient_table_max;
#pragma endregion "CODEGEN PROJ-R-MEM"
	};
}

#endif // OPENBALLISTICS_PROJECTILE_REALISTIC_HPP