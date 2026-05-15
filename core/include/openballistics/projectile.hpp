#ifndef OPENBALLISTICS_PROJECTILE_HPP
#define OPENBALLISTICS_PROJECTILE_HPP

#include "./types.hpp"
#include "./interpolators/lazy_linear.hpp"
#include "./interpolators/linear.hpp"
#include <algorithm>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>
#include <optional>

namespace openballistics
{
	class projectile
	{
	public:
		projectile()
		{
#pragma region "CODEGEN PROJECTILE-DEF" // AUTO-GENERATED - DO NOT EDIT MANUALLY
			set_form_factor(1.0);
			set_drag_factor(1.0);
			set_lift_factor(1.0);
			set_yaw_drag_factor(1.0);
			set_magnus_force_factor(1.0);
			set_drag_force_coefficient(0.0);
			set_quadratic_yaw_drag_force_coefficient(0.0);
			set_quartic_yaw_drag_force_coefficient(0.0);
			set_lift_force_coefficient(0.0);
			set_cubic_lift_force_coefficient(0.0);
			set_quintic_lift_force_coefficient(0.0);
			set_magnus_force_coefficient(0.0);
			set_overturning_moment_coefficient(0.0);
			set_cubic_overturning_moment_coefficient(0.0);
			set_spin_damping_moment_coefficient(0.0);
#pragma endregion "CODEGEN PROJECTILE-DEF"
		}

	public:
#pragma region "CODEGEN PROJECTILE-SET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		/// @brief Sets the `mass`
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_mass(const scalar value)
		{
			m_mass_constant = value;
			m_mass_source = 1;
			return *this;
		}

		/// @brief Sets the `diameter`
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_diameter(const scalar value)
		{
			m_diameter_constant = value;
			m_diameter_source = 1;
			return *this;
		}

		/// @brief Sets the `axial_moment_of_inertia`
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_axial_moment_of_inertia(const scalar value)
		{
			m_axial_moment_of_inertia_constant = value;
			m_axial_moment_of_inertia_source = 1;
			return *this;
		}

		/// @brief Sets the `form_factor`
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_form_factor(const scalar value)
		{
			m_form_factor_constant = value;
			return *this;
		}

		/// @brief Sets the `drag_factor`
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_drag_factor(const scalar value)
		{
			m_drag_factor_constant = value;
			return *this;
		}

		/// @brief Sets the `lift_factor`
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_lift_factor(const scalar value)
		{
			m_lift_factor_constant = value;
			return *this;
		}

		/// @brief Sets the `yaw_drag_factor`
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_yaw_drag_factor(const scalar value)
		{
			m_yaw_drag_factor_constant = value;
			return *this;
		}

		/// @brief Sets the `magnus_force_factor`
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_magnus_force_factor(const scalar value)
		{
			m_magnus_force_factor_constant = value;
			return *this;
		}

		/// @brief Sets the `drag_force_coefficient` as a constant value.
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_drag_force_coefficient(const scalar value)
		{
			m_drag_force_coefficient_constant = value;
			m_drag_force_coefficient_source = 1;
			return *this;
		}
		/// @brief Sets the `drag_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_drag_force_coefficient(scalar (*curve)(scalar))
		{
			m_drag_force_coefficient_curve = curve;
			m_drag_force_coefficient_source = 2;
			return *this;
		}
		/// @brief Sets the `drag_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_drag_force_coefficient(std::function<scalar(scalar)> curve)
		{
			m_drag_force_coefficient_curve_virtual = std::move(curve);
			m_drag_force_coefficient_source = 3;
			return *this;
		}
		/// @brief Sets the `drag_force_coefficient` as a linearly interpolated function of Mach number.
		/// @param curve Function of Mach number.
		/// @param interpolator_step Interpolation step size.
		/// @return Reference to the current object.
		projectile &set_drag_force_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_drag_force_coefficient_curve_interpolator = interpolators::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_drag_force_coefficient_source = 4;
			return *this;
		}
		/// @brief Sets the `drag_force_coefficient` as a linearly interpolated function of Mach number from a table.
		/// @param mach_numbers Sorted list of Mach number sample points.
		/// @param values Corresponding values at each Mach number sample point.
		/// @return Reference to the current object.
		projectile &set_drag_force_coefficient(std::vector<scalar> mach_numbers, std::vector<scalar> values)
		{
			m_drag_force_coefficient_table = interpolators::linear<scalar>(std::move(mach_numbers), std::move(values));
			m_drag_force_coefficient_source = 5;
			return *this;
		}

		/// @brief Sets the `quadratic_yaw_drag_force_coefficient` as a constant value.
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_quadratic_yaw_drag_force_coefficient(const scalar value)
		{
			m_quadratic_yaw_drag_force_coefficient_constant = value;
			m_quadratic_yaw_drag_force_coefficient_source = 1;
			return *this;
		}
		/// @brief Sets the `quadratic_yaw_drag_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_quadratic_yaw_drag_force_coefficient(scalar (*curve)(scalar))
		{
			m_quadratic_yaw_drag_force_coefficient_curve = curve;
			m_quadratic_yaw_drag_force_coefficient_source = 2;
			return *this;
		}
		/// @brief Sets the `quadratic_yaw_drag_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_quadratic_yaw_drag_force_coefficient(std::function<scalar(scalar)> curve)
		{
			m_quadratic_yaw_drag_force_coefficient_curve_virtual = std::move(curve);
			m_quadratic_yaw_drag_force_coefficient_source = 3;
			return *this;
		}
		/// @brief Sets the `quadratic_yaw_drag_force_coefficient` as a linearly interpolated function of Mach number.
		/// @param curve Function of Mach number.
		/// @param interpolator_step Interpolation step size.
		/// @return Reference to the current object.
		projectile &set_quadratic_yaw_drag_force_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_quadratic_yaw_drag_force_coefficient_curve_interpolator = interpolators::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_quadratic_yaw_drag_force_coefficient_source = 4;
			return *this;
		}
		/// @brief Sets the `quadratic_yaw_drag_force_coefficient` as a linearly interpolated function of Mach number from a table.
		/// @param mach_numbers Sorted list of Mach number sample points.
		/// @param values Corresponding values at each Mach number sample point.
		/// @return Reference to the current object.
		projectile &set_quadratic_yaw_drag_force_coefficient(std::vector<scalar> mach_numbers, std::vector<scalar> values)
		{
			m_quadratic_yaw_drag_force_coefficient_table = interpolators::linear<scalar>(std::move(mach_numbers), std::move(values));
			m_quadratic_yaw_drag_force_coefficient_source = 5;
			return *this;
		}

		/// @brief Sets the `quartic_yaw_drag_force_coefficient` as a constant value.
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_quartic_yaw_drag_force_coefficient(const scalar value)
		{
			m_quartic_yaw_drag_force_coefficient_constant = value;
			m_quartic_yaw_drag_force_coefficient_source = 1;
			return *this;
		}
		/// @brief Sets the `quartic_yaw_drag_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_quartic_yaw_drag_force_coefficient(scalar (*curve)(scalar))
		{
			m_quartic_yaw_drag_force_coefficient_curve = curve;
			m_quartic_yaw_drag_force_coefficient_source = 2;
			return *this;
		}
		/// @brief Sets the `quartic_yaw_drag_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_quartic_yaw_drag_force_coefficient(std::function<scalar(scalar)> curve)
		{
			m_quartic_yaw_drag_force_coefficient_curve_virtual = std::move(curve);
			m_quartic_yaw_drag_force_coefficient_source = 3;
			return *this;
		}
		/// @brief Sets the `quartic_yaw_drag_force_coefficient` as a linearly interpolated function of Mach number.
		/// @param curve Function of Mach number.
		/// @param interpolator_step Interpolation step size.
		/// @return Reference to the current object.
		projectile &set_quartic_yaw_drag_force_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_quartic_yaw_drag_force_coefficient_curve_interpolator = interpolators::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_quartic_yaw_drag_force_coefficient_source = 4;
			return *this;
		}
		/// @brief Sets the `quartic_yaw_drag_force_coefficient` as a linearly interpolated function of Mach number from a table.
		/// @param mach_numbers Sorted list of Mach number sample points.
		/// @param values Corresponding values at each Mach number sample point.
		/// @return Reference to the current object.
		projectile &set_quartic_yaw_drag_force_coefficient(std::vector<scalar> mach_numbers, std::vector<scalar> values)
		{
			m_quartic_yaw_drag_force_coefficient_table = interpolators::linear<scalar>(std::move(mach_numbers), std::move(values));
			m_quartic_yaw_drag_force_coefficient_source = 5;
			return *this;
		}

		/// @brief Sets the `lift_force_coefficient` as a constant value.
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_lift_force_coefficient(const scalar value)
		{
			m_lift_force_coefficient_constant = value;
			m_lift_force_coefficient_source = 1;
			return *this;
		}
		/// @brief Sets the `lift_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_lift_force_coefficient(scalar (*curve)(scalar))
		{
			m_lift_force_coefficient_curve = curve;
			m_lift_force_coefficient_source = 2;
			return *this;
		}
		/// @brief Sets the `lift_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_lift_force_coefficient(std::function<scalar(scalar)> curve)
		{
			m_lift_force_coefficient_curve_virtual = std::move(curve);
			m_lift_force_coefficient_source = 3;
			return *this;
		}
		/// @brief Sets the `lift_force_coefficient` as a linearly interpolated function of Mach number.
		/// @param curve Function of Mach number.
		/// @param interpolator_step Interpolation step size.
		/// @return Reference to the current object.
		projectile &set_lift_force_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_lift_force_coefficient_curve_interpolator = interpolators::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_lift_force_coefficient_source = 4;
			return *this;
		}
		/// @brief Sets the `lift_force_coefficient` as a linearly interpolated function of Mach number from a table.
		/// @param mach_numbers Sorted list of Mach number sample points.
		/// @param values Corresponding values at each Mach number sample point.
		/// @return Reference to the current object.
		projectile &set_lift_force_coefficient(std::vector<scalar> mach_numbers, std::vector<scalar> values)
		{
			m_lift_force_coefficient_table = interpolators::linear<scalar>(std::move(mach_numbers), std::move(values));
			m_lift_force_coefficient_source = 5;
			return *this;
		}

		/// @brief Sets the `cubic_lift_force_coefficient` as a constant value.
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_cubic_lift_force_coefficient(const scalar value)
		{
			m_cubic_lift_force_coefficient_constant = value;
			m_cubic_lift_force_coefficient_source = 1;
			return *this;
		}
		/// @brief Sets the `cubic_lift_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_cubic_lift_force_coefficient(scalar (*curve)(scalar))
		{
			m_cubic_lift_force_coefficient_curve = curve;
			m_cubic_lift_force_coefficient_source = 2;
			return *this;
		}
		/// @brief Sets the `cubic_lift_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_cubic_lift_force_coefficient(std::function<scalar(scalar)> curve)
		{
			m_cubic_lift_force_coefficient_curve_virtual = std::move(curve);
			m_cubic_lift_force_coefficient_source = 3;
			return *this;
		}
		/// @brief Sets the `cubic_lift_force_coefficient` as a linearly interpolated function of Mach number.
		/// @param curve Function of Mach number.
		/// @param interpolator_step Interpolation step size.
		/// @return Reference to the current object.
		projectile &set_cubic_lift_force_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_cubic_lift_force_coefficient_curve_interpolator = interpolators::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_cubic_lift_force_coefficient_source = 4;
			return *this;
		}
		/// @brief Sets the `cubic_lift_force_coefficient` as a linearly interpolated function of Mach number from a table.
		/// @param mach_numbers Sorted list of Mach number sample points.
		/// @param values Corresponding values at each Mach number sample point.
		/// @return Reference to the current object.
		projectile &set_cubic_lift_force_coefficient(std::vector<scalar> mach_numbers, std::vector<scalar> values)
		{
			m_cubic_lift_force_coefficient_table = interpolators::linear<scalar>(std::move(mach_numbers), std::move(values));
			m_cubic_lift_force_coefficient_source = 5;
			return *this;
		}

		/// @brief Sets the `quintic_lift_force_coefficient` as a constant value.
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_quintic_lift_force_coefficient(const scalar value)
		{
			m_quintic_lift_force_coefficient_constant = value;
			m_quintic_lift_force_coefficient_source = 1;
			return *this;
		}
		/// @brief Sets the `quintic_lift_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_quintic_lift_force_coefficient(scalar (*curve)(scalar))
		{
			m_quintic_lift_force_coefficient_curve = curve;
			m_quintic_lift_force_coefficient_source = 2;
			return *this;
		}
		/// @brief Sets the `quintic_lift_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_quintic_lift_force_coefficient(std::function<scalar(scalar)> curve)
		{
			m_quintic_lift_force_coefficient_curve_virtual = std::move(curve);
			m_quintic_lift_force_coefficient_source = 3;
			return *this;
		}
		/// @brief Sets the `quintic_lift_force_coefficient` as a linearly interpolated function of Mach number.
		/// @param curve Function of Mach number.
		/// @param interpolator_step Interpolation step size.
		/// @return Reference to the current object.
		projectile &set_quintic_lift_force_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_quintic_lift_force_coefficient_curve_interpolator = interpolators::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_quintic_lift_force_coefficient_source = 4;
			return *this;
		}
		/// @brief Sets the `quintic_lift_force_coefficient` as a linearly interpolated function of Mach number from a table.
		/// @param mach_numbers Sorted list of Mach number sample points.
		/// @param values Corresponding values at each Mach number sample point.
		/// @return Reference to the current object.
		projectile &set_quintic_lift_force_coefficient(std::vector<scalar> mach_numbers, std::vector<scalar> values)
		{
			m_quintic_lift_force_coefficient_table = interpolators::linear<scalar>(std::move(mach_numbers), std::move(values));
			m_quintic_lift_force_coefficient_source = 5;
			return *this;
		}

		/// @brief Sets the `magnus_force_coefficient` as a constant value.
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_magnus_force_coefficient(const scalar value)
		{
			m_magnus_force_coefficient_constant = value;
			m_magnus_force_coefficient_source = 1;
			return *this;
		}
		/// @brief Sets the `magnus_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_magnus_force_coefficient(scalar (*curve)(scalar))
		{
			m_magnus_force_coefficient_curve = curve;
			m_magnus_force_coefficient_source = 2;
			return *this;
		}
		/// @brief Sets the `magnus_force_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_magnus_force_coefficient(std::function<scalar(scalar)> curve)
		{
			m_magnus_force_coefficient_curve_virtual = std::move(curve);
			m_magnus_force_coefficient_source = 3;
			return *this;
		}
		/// @brief Sets the `magnus_force_coefficient` as a linearly interpolated function of Mach number.
		/// @param curve Function of Mach number.
		/// @param interpolator_step Interpolation step size.
		/// @return Reference to the current object.
		projectile &set_magnus_force_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_magnus_force_coefficient_curve_interpolator = interpolators::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_magnus_force_coefficient_source = 4;
			return *this;
		}
		/// @brief Sets the `magnus_force_coefficient` as a linearly interpolated function of Mach number from a table.
		/// @param mach_numbers Sorted list of Mach number sample points.
		/// @param values Corresponding values at each Mach number sample point.
		/// @return Reference to the current object.
		projectile &set_magnus_force_coefficient(std::vector<scalar> mach_numbers, std::vector<scalar> values)
		{
			m_magnus_force_coefficient_table = interpolators::linear<scalar>(std::move(mach_numbers), std::move(values));
			m_magnus_force_coefficient_source = 5;
			return *this;
		}

		/// @brief Sets the `overturning_moment_coefficient` as a constant value.
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_overturning_moment_coefficient(const scalar value)
		{
			m_overturning_moment_coefficient_constant = value;
			m_overturning_moment_coefficient_source = 1;
			return *this;
		}
		/// @brief Sets the `overturning_moment_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_overturning_moment_coefficient(scalar (*curve)(scalar))
		{
			m_overturning_moment_coefficient_curve = curve;
			m_overturning_moment_coefficient_source = 2;
			return *this;
		}
		/// @brief Sets the `overturning_moment_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_overturning_moment_coefficient(std::function<scalar(scalar)> curve)
		{
			m_overturning_moment_coefficient_curve_virtual = std::move(curve);
			m_overturning_moment_coefficient_source = 3;
			return *this;
		}
		/// @brief Sets the `overturning_moment_coefficient` as a linearly interpolated function of Mach number.
		/// @param curve Function of Mach number.
		/// @param interpolator_step Interpolation step size.
		/// @return Reference to the current object.
		projectile &set_overturning_moment_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_overturning_moment_coefficient_curve_interpolator = interpolators::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_overturning_moment_coefficient_source = 4;
			return *this;
		}
		/// @brief Sets the `overturning_moment_coefficient` as a linearly interpolated function of Mach number from a table.
		/// @param mach_numbers Sorted list of Mach number sample points.
		/// @param values Corresponding values at each Mach number sample point.
		/// @return Reference to the current object.
		projectile &set_overturning_moment_coefficient(std::vector<scalar> mach_numbers, std::vector<scalar> values)
		{
			m_overturning_moment_coefficient_table = interpolators::linear<scalar>(std::move(mach_numbers), std::move(values));
			m_overturning_moment_coefficient_source = 5;
			return *this;
		}

		/// @brief Sets the `cubic_overturning_moment_coefficient` as a constant value.
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_cubic_overturning_moment_coefficient(const scalar value)
		{
			m_cubic_overturning_moment_coefficient_constant = value;
			m_cubic_overturning_moment_coefficient_source = 1;
			return *this;
		}
		/// @brief Sets the `cubic_overturning_moment_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_cubic_overturning_moment_coefficient(scalar (*curve)(scalar))
		{
			m_cubic_overturning_moment_coefficient_curve = curve;
			m_cubic_overturning_moment_coefficient_source = 2;
			return *this;
		}
		/// @brief Sets the `cubic_overturning_moment_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_cubic_overturning_moment_coefficient(std::function<scalar(scalar)> curve)
		{
			m_cubic_overturning_moment_coefficient_curve_virtual = std::move(curve);
			m_cubic_overturning_moment_coefficient_source = 3;
			return *this;
		}
		/// @brief Sets the `cubic_overturning_moment_coefficient` as a linearly interpolated function of Mach number.
		/// @param curve Function of Mach number.
		/// @param interpolator_step Interpolation step size.
		/// @return Reference to the current object.
		projectile &set_cubic_overturning_moment_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_cubic_overturning_moment_coefficient_curve_interpolator = interpolators::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_cubic_overturning_moment_coefficient_source = 4;
			return *this;
		}
		/// @brief Sets the `cubic_overturning_moment_coefficient` as a linearly interpolated function of Mach number from a table.
		/// @param mach_numbers Sorted list of Mach number sample points.
		/// @param values Corresponding values at each Mach number sample point.
		/// @return Reference to the current object.
		projectile &set_cubic_overturning_moment_coefficient(std::vector<scalar> mach_numbers, std::vector<scalar> values)
		{
			m_cubic_overturning_moment_coefficient_table = interpolators::linear<scalar>(std::move(mach_numbers), std::move(values));
			m_cubic_overturning_moment_coefficient_source = 5;
			return *this;
		}

		/// @brief Sets the `spin_damping_moment_coefficient` as a constant value.
		/// @param value Constant value.
		/// @return Reference to the current object.
		projectile &set_spin_damping_moment_coefficient(const scalar value)
		{
			m_spin_damping_moment_coefficient_constant = value;
			m_spin_damping_moment_coefficient_source = 1;
			return *this;
		}
		/// @brief Sets the `spin_damping_moment_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_spin_damping_moment_coefficient(scalar (*curve)(scalar))
		{
			m_spin_damping_moment_coefficient_curve = curve;
			m_spin_damping_moment_coefficient_source = 2;
			return *this;
		}
		/// @brief Sets the `spin_damping_moment_coefficient` as a function of Mach number.
		/// @param curve Function of Mach number.
		/// @return Reference to the current object.
		projectile &set_spin_damping_moment_coefficient(std::function<scalar(scalar)> curve)
		{
			m_spin_damping_moment_coefficient_curve_virtual = std::move(curve);
			m_spin_damping_moment_coefficient_source = 3;
			return *this;
		}
		/// @brief Sets the `spin_damping_moment_coefficient` as a linearly interpolated function of Mach number.
		/// @param curve Function of Mach number.
		/// @param interpolator_step Interpolation step size.
		/// @return Reference to the current object.
		projectile &set_spin_damping_moment_coefficient(std::function<scalar(scalar)> curve, const scalar interpolator_step)
		{
			m_spin_damping_moment_coefficient_curve_interpolator = interpolators::lazy_linear<scalar>(std::move(curve), interpolator_step);
			m_spin_damping_moment_coefficient_source = 4;
			return *this;
		}
		/// @brief Sets the `spin_damping_moment_coefficient` as a linearly interpolated function of Mach number from a table.
		/// @param mach_numbers Sorted list of Mach number sample points.
		/// @param values Corresponding values at each Mach number sample point.
		/// @return Reference to the current object.
		projectile &set_spin_damping_moment_coefficient(std::vector<scalar> mach_numbers, std::vector<scalar> values)
		{
			m_spin_damping_moment_coefficient_table = interpolators::linear<scalar>(std::move(mach_numbers), std::move(values));
			m_spin_damping_moment_coefficient_source = 5;
			return *this;
		}
#pragma endregion "CODEGEN PROJECTILE-SET"

#pragma region "CODEGEN PROJECTILE-GET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		/// @brief Gets the `mass`.
		/// @return `mass`.
		[[nodiscard]] scalar mass() const
		{
			if (m_mass_source == 1) return m_mass_constant;
			throw std::bad_optional_access{};
		}

		/// @brief Gets the `diameter`.
		/// @return `diameter`.
		[[nodiscard]] scalar diameter() const
		{
			if (m_diameter_source == 1) return m_diameter_constant;
			throw std::bad_optional_access{};
		}

		/// @brief Gets the `axial_moment_of_inertia`.
		/// @return `axial_moment_of_inertia`.
		[[nodiscard]] scalar axial_moment_of_inertia() const
		{
			if (m_axial_moment_of_inertia_source == 1) return m_axial_moment_of_inertia_constant;
			throw std::bad_optional_access{};
		}

		/// @brief Gets the `form_factor`.
		/// @return `form_factor`.
		[[nodiscard]] scalar form_factor() const
		{
			return m_form_factor_constant;
		}

		/// @brief Gets the `drag_factor`.
		/// @return `drag_factor`.
		[[nodiscard]] scalar drag_factor() const
		{
			return m_drag_factor_constant;
		}

		/// @brief Gets the `lift_factor`.
		/// @return `lift_factor`.
		[[nodiscard]] scalar lift_factor() const
		{
			return m_lift_factor_constant;
		}

		/// @brief Gets the `yaw_drag_factor`.
		/// @return `yaw_drag_factor`.
		[[nodiscard]] scalar yaw_drag_factor() const
		{
			return m_yaw_drag_factor_constant;
		}

		/// @brief Gets the `magnus_force_factor`.
		/// @return `magnus_force_factor`.
		[[nodiscard]] scalar magnus_force_factor() const
		{
			return m_magnus_force_factor_constant;
		}

		/// @brief Gets the `drag_force_coefficient` at a given Mach number.
		/// @param mach Mach number.
		/// @return `drag_force_coefficient` evaluated at the specified Mach number.
		[[nodiscard]] scalar drag_force_coefficient(const scalar mach) const
		{
			switch (m_drag_force_coefficient_source)
			{
			case 1: return m_drag_force_coefficient_constant;
			case 2: return m_drag_force_coefficient_curve(mach);
			case 3: return m_drag_force_coefficient_curve_virtual(mach);
			case 4: return m_drag_force_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_drag_force_coefficient_table.evaluate(mach);
			default: throw std::bad_optional_access{};
			}
		}

		/// @brief Gets the `quadratic_yaw_drag_force_coefficient` at a given Mach number.
		/// @param mach Mach number.
		/// @return `quadratic_yaw_drag_force_coefficient` evaluated at the specified Mach number.
		[[nodiscard]] scalar quadratic_yaw_drag_force_coefficient(const scalar mach) const
		{
			switch (m_quadratic_yaw_drag_force_coefficient_source)
			{
			case 1: return m_quadratic_yaw_drag_force_coefficient_constant;
			case 2: return m_quadratic_yaw_drag_force_coefficient_curve(mach);
			case 3: return m_quadratic_yaw_drag_force_coefficient_curve_virtual(mach);
			case 4: return m_quadratic_yaw_drag_force_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_quadratic_yaw_drag_force_coefficient_table.evaluate(mach);
			default: throw std::bad_optional_access{};
			}
		}

		/// @brief Gets the `quartic_yaw_drag_force_coefficient` at a given Mach number.
		/// @param mach Mach number.
		/// @return `quartic_yaw_drag_force_coefficient` evaluated at the specified Mach number.
		[[nodiscard]] scalar quartic_yaw_drag_force_coefficient(const scalar mach) const
		{
			switch (m_quartic_yaw_drag_force_coefficient_source)
			{
			case 1: return m_quartic_yaw_drag_force_coefficient_constant;
			case 2: return m_quartic_yaw_drag_force_coefficient_curve(mach);
			case 3: return m_quartic_yaw_drag_force_coefficient_curve_virtual(mach);
			case 4: return m_quartic_yaw_drag_force_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_quartic_yaw_drag_force_coefficient_table.evaluate(mach);
			default: throw std::bad_optional_access{};
			}
		}

		/// @brief Gets the `lift_force_coefficient` at a given Mach number.
		/// @param mach Mach number.
		/// @return `lift_force_coefficient` evaluated at the specified Mach number.
		[[nodiscard]] scalar lift_force_coefficient(const scalar mach) const
		{
			switch (m_lift_force_coefficient_source)
			{
			case 1: return m_lift_force_coefficient_constant;
			case 2: return m_lift_force_coefficient_curve(mach);
			case 3: return m_lift_force_coefficient_curve_virtual(mach);
			case 4: return m_lift_force_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_lift_force_coefficient_table.evaluate(mach);
			default: throw std::bad_optional_access{};
			}
		}

		/// @brief Gets the `cubic_lift_force_coefficient` at a given Mach number.
		/// @param mach Mach number.
		/// @return `cubic_lift_force_coefficient` evaluated at the specified Mach number.
		[[nodiscard]] scalar cubic_lift_force_coefficient(const scalar mach) const
		{
			switch (m_cubic_lift_force_coefficient_source)
			{
			case 1: return m_cubic_lift_force_coefficient_constant;
			case 2: return m_cubic_lift_force_coefficient_curve(mach);
			case 3: return m_cubic_lift_force_coefficient_curve_virtual(mach);
			case 4: return m_cubic_lift_force_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_cubic_lift_force_coefficient_table.evaluate(mach);
			default: throw std::bad_optional_access{};
			}
		}

		/// @brief Gets the `quintic_lift_force_coefficient` at a given Mach number.
		/// @param mach Mach number.
		/// @return `quintic_lift_force_coefficient` evaluated at the specified Mach number.
		[[nodiscard]] scalar quintic_lift_force_coefficient(const scalar mach) const
		{
			switch (m_quintic_lift_force_coefficient_source)
			{
			case 1: return m_quintic_lift_force_coefficient_constant;
			case 2: return m_quintic_lift_force_coefficient_curve(mach);
			case 3: return m_quintic_lift_force_coefficient_curve_virtual(mach);
			case 4: return m_quintic_lift_force_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_quintic_lift_force_coefficient_table.evaluate(mach);
			default: throw std::bad_optional_access{};
			}
		}

		/// @brief Gets the `magnus_force_coefficient` at a given Mach number.
		/// @param mach Mach number.
		/// @return `magnus_force_coefficient` evaluated at the specified Mach number.
		[[nodiscard]] scalar magnus_force_coefficient(const scalar mach) const
		{
			switch (m_magnus_force_coefficient_source)
			{
			case 1: return m_magnus_force_coefficient_constant;
			case 2: return m_magnus_force_coefficient_curve(mach);
			case 3: return m_magnus_force_coefficient_curve_virtual(mach);
			case 4: return m_magnus_force_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_magnus_force_coefficient_table.evaluate(mach);
			default: throw std::bad_optional_access{};
			}
		}

		/// @brief Gets the `overturning_moment_coefficient` at a given Mach number.
		/// @param mach Mach number.
		/// @return `overturning_moment_coefficient` evaluated at the specified Mach number.
		[[nodiscard]] scalar overturning_moment_coefficient(const scalar mach) const
		{
			switch (m_overturning_moment_coefficient_source)
			{
			case 1: return m_overturning_moment_coefficient_constant;
			case 2: return m_overturning_moment_coefficient_curve(mach);
			case 3: return m_overturning_moment_coefficient_curve_virtual(mach);
			case 4: return m_overturning_moment_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_overturning_moment_coefficient_table.evaluate(mach);
			default: throw std::bad_optional_access{};
			}
		}

		/// @brief Gets the `cubic_overturning_moment_coefficient` at a given Mach number.
		/// @param mach Mach number.
		/// @return `cubic_overturning_moment_coefficient` evaluated at the specified Mach number.
		[[nodiscard]] scalar cubic_overturning_moment_coefficient(const scalar mach) const
		{
			switch (m_cubic_overturning_moment_coefficient_source)
			{
			case 1: return m_cubic_overturning_moment_coefficient_constant;
			case 2: return m_cubic_overturning_moment_coefficient_curve(mach);
			case 3: return m_cubic_overturning_moment_coefficient_curve_virtual(mach);
			case 4: return m_cubic_overturning_moment_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_cubic_overturning_moment_coefficient_table.evaluate(mach);
			default: throw std::bad_optional_access{};
			}
		}

		/// @brief Gets the `spin_damping_moment_coefficient` at a given Mach number.
		/// @param mach Mach number.
		/// @return `spin_damping_moment_coefficient` evaluated at the specified Mach number.
		[[nodiscard]] scalar spin_damping_moment_coefficient(const scalar mach) const
		{
			switch (m_spin_damping_moment_coefficient_source)
			{
			case 1: return m_spin_damping_moment_coefficient_constant;
			case 2: return m_spin_damping_moment_coefficient_curve(mach);
			case 3: return m_spin_damping_moment_coefficient_curve_virtual(mach);
			case 4: return m_spin_damping_moment_coefficient_curve_interpolator.evaluate(mach);
			case 5: return m_spin_damping_moment_coefficient_table.evaluate(mach);
			default: throw std::bad_optional_access{};
			}
		}
#pragma endregion "CODEGEN PROJECTILE-GET"

	private:
#pragma region "CODEGEN PROJECTILE-MEM" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		bool m_mass_source = 0;
		scalar m_mass_constant;

		bool m_diameter_source = 0;
		scalar m_diameter_constant;

		bool m_axial_moment_of_inertia_source = 0;
		scalar m_axial_moment_of_inertia_constant;

		scalar m_form_factor_constant;

		scalar m_drag_factor_constant;

		scalar m_lift_factor_constant;

		scalar m_yaw_drag_factor_constant;

		scalar m_magnus_force_factor_constant;

		uint8_t m_drag_force_coefficient_source = 0;
		scalar m_drag_force_coefficient_constant;
		scalar (*m_drag_force_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_drag_force_coefficient_curve_virtual;
		interpolators::lazy_linear<scalar> m_drag_force_coefficient_curve_interpolator;
		interpolators::linear<scalar> m_drag_force_coefficient_table{{0.0}, {0.0}};

		uint8_t m_quadratic_yaw_drag_force_coefficient_source = 0;
		scalar m_quadratic_yaw_drag_force_coefficient_constant;
		scalar (*m_quadratic_yaw_drag_force_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_quadratic_yaw_drag_force_coefficient_curve_virtual;
		interpolators::lazy_linear<scalar> m_quadratic_yaw_drag_force_coefficient_curve_interpolator;
		interpolators::linear<scalar> m_quadratic_yaw_drag_force_coefficient_table{{0.0}, {0.0}};

		uint8_t m_quartic_yaw_drag_force_coefficient_source = 0;
		scalar m_quartic_yaw_drag_force_coefficient_constant;
		scalar (*m_quartic_yaw_drag_force_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_quartic_yaw_drag_force_coefficient_curve_virtual;
		interpolators::lazy_linear<scalar> m_quartic_yaw_drag_force_coefficient_curve_interpolator;
		interpolators::linear<scalar> m_quartic_yaw_drag_force_coefficient_table{{0.0}, {0.0}};

		uint8_t m_lift_force_coefficient_source = 0;
		scalar m_lift_force_coefficient_constant;
		scalar (*m_lift_force_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_lift_force_coefficient_curve_virtual;
		interpolators::lazy_linear<scalar> m_lift_force_coefficient_curve_interpolator;
		interpolators::linear<scalar> m_lift_force_coefficient_table{{0.0}, {0.0}};

		uint8_t m_cubic_lift_force_coefficient_source = 0;
		scalar m_cubic_lift_force_coefficient_constant;
		scalar (*m_cubic_lift_force_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_cubic_lift_force_coefficient_curve_virtual;
		interpolators::lazy_linear<scalar> m_cubic_lift_force_coefficient_curve_interpolator;
		interpolators::linear<scalar> m_cubic_lift_force_coefficient_table{{0.0}, {0.0}};

		uint8_t m_quintic_lift_force_coefficient_source = 0;
		scalar m_quintic_lift_force_coefficient_constant;
		scalar (*m_quintic_lift_force_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_quintic_lift_force_coefficient_curve_virtual;
		interpolators::lazy_linear<scalar> m_quintic_lift_force_coefficient_curve_interpolator;
		interpolators::linear<scalar> m_quintic_lift_force_coefficient_table{{0.0}, {0.0}};

		uint8_t m_magnus_force_coefficient_source = 0;
		scalar m_magnus_force_coefficient_constant;
		scalar (*m_magnus_force_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_magnus_force_coefficient_curve_virtual;
		interpolators::lazy_linear<scalar> m_magnus_force_coefficient_curve_interpolator;
		interpolators::linear<scalar> m_magnus_force_coefficient_table{{0.0}, {0.0}};

		uint8_t m_overturning_moment_coefficient_source = 0;
		scalar m_overturning_moment_coefficient_constant;
		scalar (*m_overturning_moment_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_overturning_moment_coefficient_curve_virtual;
		interpolators::lazy_linear<scalar> m_overturning_moment_coefficient_curve_interpolator;
		interpolators::linear<scalar> m_overturning_moment_coefficient_table{{0.0}, {0.0}};

		uint8_t m_cubic_overturning_moment_coefficient_source = 0;
		scalar m_cubic_overturning_moment_coefficient_constant;
		scalar (*m_cubic_overturning_moment_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_cubic_overturning_moment_coefficient_curve_virtual;
		interpolators::lazy_linear<scalar> m_cubic_overturning_moment_coefficient_curve_interpolator;
		interpolators::linear<scalar> m_cubic_overturning_moment_coefficient_table{{0.0}, {0.0}};

		uint8_t m_spin_damping_moment_coefficient_source = 0;
		scalar m_spin_damping_moment_coefficient_constant;
		scalar (*m_spin_damping_moment_coefficient_curve)(scalar);
		std::function<scalar(scalar)> m_spin_damping_moment_coefficient_curve_virtual;
		interpolators::lazy_linear<scalar> m_spin_damping_moment_coefficient_curve_interpolator;
		interpolators::linear<scalar> m_spin_damping_moment_coefficient_table{{0.0}, {0.0}};
#pragma endregion "CODEGEN PROJECTILE-MEM"
	};
}

#endif // OPENBALLISTICS_PROJECTILE_HPP