#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/function.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/pair.h>
#include <openballistics.hpp>

namespace nb = nanobind;

NB_MODULE(_core, m)
{
    using namespace openballistics;
    {
        using Class = angles;
        nb::class_<Class>(m, "Angles")
            .def(nb::init<scalar, scalar>())
            .def_prop_ro("azimuth", &Class::azimuth)
            .def_prop_ro("elevation", &Class::elevation)
            .def("to_direction", &Class::to_unit_direction)
            .def_static("from_direction", &Class::from_direction);
    }

#pragma region "CODEGEN BIND" // AUTO-GENERATED - DO NOT EDIT MANUALLY
	{
		using Class = ballistics<trajectory_model::modified_point_mass, integrator::runge_kutta_4>;
		auto nb_class = nb::class_<Class>(m, "MPMRK4").def(nb::init<>());
		nb_class
			.def_rw("integrator", &Class::integrator)
			.def_rw("environment", &Class::environment)
			.def_rw("projectile", &Class::projectile);
		nb_class
			.def("compute_final_position", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, const scalar, scalar>(&Class::compute_final_position, nb::const_))
			.def("compute_final_position", nb::overload_cast<const vector3 &, const angles &, const vector3 &, const scalar, const scalar, scalar>(&Class::compute_final_position, nb::const_))
			.def("compute_trajectory", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, const scalar, scalar, scalar, scalar>(&Class::compute_trajectory, nb::const_))
			.def("compute_trajectory", nb::overload_cast<const vector3 &, const angles &, const vector3 &, const scalar, const scalar, scalar, scalar, scalar>(&Class::compute_trajectory, nb::const_))
			.def("optimize_launch_direction", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, const scalar, scalar, uint32_t>(&Class::optimize_launch_direction, nb::const_))
			.def("optimize_launch_angles", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, const scalar, scalar, uint32_t>(&Class::optimize_launch_angles, nb::const_))
			.def("solve_launch_direction", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, const scalar, scalar, scalar, uint32_t>(&Class::solve_launch_direction, nb::const_))
			.def("solve_launch_angles", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, const scalar, scalar, scalar, uint32_t>(&Class::solve_launch_angles, nb::const_))
			.def("solve_launch_direction_and_time_of_flight", nb::overload_cast<const vector3 &, const vector3 &, const std::function<vector3(scalar)> &, const scalar, const scalar, scalar, scalar, scalar, scalar, uint32_t, uint32_t>(&Class::solve_launch_direction_and_time_of_flight, nb::const_))
			.def("solve_launch_angles_and_time_of_flight", nb::overload_cast<const vector3 &, const vector3 &, const std::function<vector3(scalar)> &, const scalar, const scalar, scalar, scalar, scalar, scalar, uint32_t, uint32_t>(&Class::solve_launch_angles_and_time_of_flight, nb::const_));
	}
	{
		using Class = ballistics<trajectory_model::modified_point_mass, integrator::runge_kutta_dormand_prince_5>;
		auto nb_class = nb::class_<Class>(m, "MPMRKDP5").def(nb::init<>());
		nb_class
			.def_rw("integrator", &Class::integrator)
			.def_rw("environment", &Class::environment)
			.def_rw("projectile", &Class::projectile);
		nb_class
			.def("compute_final_position", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, const scalar, scalar>(&Class::compute_final_position, nb::const_))
			.def("compute_final_position", nb::overload_cast<const vector3 &, const angles &, const vector3 &, const scalar, const scalar, scalar>(&Class::compute_final_position, nb::const_))
			.def("compute_trajectory", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, const scalar, scalar, scalar, scalar>(&Class::compute_trajectory, nb::const_))
			.def("compute_trajectory", nb::overload_cast<const vector3 &, const angles &, const vector3 &, const scalar, const scalar, scalar, scalar, scalar>(&Class::compute_trajectory, nb::const_))
			.def("optimize_launch_direction", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, const scalar, scalar, uint32_t>(&Class::optimize_launch_direction, nb::const_))
			.def("optimize_launch_angles", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, const scalar, scalar, uint32_t>(&Class::optimize_launch_angles, nb::const_))
			.def("solve_launch_direction", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, const scalar, scalar, scalar, uint32_t>(&Class::solve_launch_direction, nb::const_))
			.def("solve_launch_angles", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, const scalar, scalar, scalar, uint32_t>(&Class::solve_launch_angles, nb::const_))
			.def("solve_launch_direction_and_time_of_flight", nb::overload_cast<const vector3 &, const vector3 &, const std::function<vector3(scalar)> &, const scalar, const scalar, scalar, scalar, scalar, scalar, uint32_t, uint32_t>(&Class::solve_launch_direction_and_time_of_flight, nb::const_))
			.def("solve_launch_angles_and_time_of_flight", nb::overload_cast<const vector3 &, const vector3 &, const std::function<vector3(scalar)> &, const scalar, const scalar, scalar, scalar, scalar, scalar, uint32_t, uint32_t>(&Class::solve_launch_angles_and_time_of_flight, nb::const_));
	}
	{
		using Class = ballistics<trajectory_model::point_mass, integrator::runge_kutta_4>;
		auto nb_class = nb::class_<Class>(m, "PMRK4").def(nb::init<>());
		nb_class
			.def_rw("integrator", &Class::integrator)
			.def_rw("environment", &Class::environment)
			.def_rw("projectile", &Class::projectile);
		nb_class
			.def("compute_final_position", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, scalar>(&Class::compute_final_position, nb::const_))
			.def("compute_final_position", nb::overload_cast<const vector3 &, const angles &, const vector3 &, const scalar, scalar>(&Class::compute_final_position, nb::const_))
			.def("compute_trajectory", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, scalar, scalar, scalar>(&Class::compute_trajectory, nb::const_))
			.def("compute_trajectory", nb::overload_cast<const vector3 &, const angles &, const vector3 &, const scalar, scalar, scalar, scalar>(&Class::compute_trajectory, nb::const_))
			.def("optimize_launch_direction", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, scalar, uint32_t>(&Class::optimize_launch_direction, nb::const_))
			.def("optimize_launch_angles", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, scalar, uint32_t>(&Class::optimize_launch_angles, nb::const_))
			.def("solve_launch_direction", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, scalar, scalar, uint32_t>(&Class::solve_launch_direction, nb::const_))
			.def("solve_launch_angles", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, scalar, scalar, uint32_t>(&Class::solve_launch_angles, nb::const_))
			.def("solve_launch_direction_and_time_of_flight", nb::overload_cast<const vector3 &, const vector3 &, const std::function<vector3(scalar)> &, const scalar, scalar, scalar, scalar, scalar, uint32_t, uint32_t>(&Class::solve_launch_direction_and_time_of_flight, nb::const_))
			.def("solve_launch_angles_and_time_of_flight", nb::overload_cast<const vector3 &, const vector3 &, const std::function<vector3(scalar)> &, const scalar, scalar, scalar, scalar, scalar, uint32_t, uint32_t>(&Class::solve_launch_angles_and_time_of_flight, nb::const_));
	}
	{
		using Class = ballistics<trajectory_model::point_mass, integrator::runge_kutta_dormand_prince_5>;
		auto nb_class = nb::class_<Class>(m, "PMRKDP5").def(nb::init<>());
		nb_class
			.def_rw("integrator", &Class::integrator)
			.def_rw("environment", &Class::environment)
			.def_rw("projectile", &Class::projectile);
		nb_class
			.def("compute_final_position", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, scalar>(&Class::compute_final_position, nb::const_))
			.def("compute_final_position", nb::overload_cast<const vector3 &, const angles &, const vector3 &, const scalar, scalar>(&Class::compute_final_position, nb::const_))
			.def("compute_trajectory", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, scalar, scalar, scalar>(&Class::compute_trajectory, nb::const_))
			.def("compute_trajectory", nb::overload_cast<const vector3 &, const angles &, const vector3 &, const scalar, scalar, scalar, scalar>(&Class::compute_trajectory, nb::const_))
			.def("optimize_launch_direction", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, scalar, uint32_t>(&Class::optimize_launch_direction, nb::const_))
			.def("optimize_launch_angles", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, scalar, uint32_t>(&Class::optimize_launch_angles, nb::const_))
			.def("solve_launch_direction", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, scalar, scalar, uint32_t>(&Class::solve_launch_direction, nb::const_))
			.def("solve_launch_angles", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, const scalar, scalar, scalar, uint32_t>(&Class::solve_launch_angles, nb::const_))
			.def("solve_launch_direction_and_time_of_flight", nb::overload_cast<const vector3 &, const vector3 &, const std::function<vector3(scalar)> &, const scalar, scalar, scalar, scalar, scalar, uint32_t, uint32_t>(&Class::solve_launch_direction_and_time_of_flight, nb::const_))
			.def("solve_launch_angles_and_time_of_flight", nb::overload_cast<const vector3 &, const vector3 &, const std::function<vector3(scalar)> &, const scalar, scalar, scalar, scalar, scalar, uint32_t, uint32_t>(&Class::solve_launch_angles_and_time_of_flight, nb::const_));
	}
	{
		using Class = integrator::runge_kutta_4;
		auto nb_class = nb::class_<Class>(m, "RK4").def(nb::init<>());
		nb_class
			.def("set_step", &Class::set_step)
			.def("step", &Class::step);
	}
	{
		using Class = integrator::runge_kutta_dormand_prince_5;
		auto nb_class = nb::class_<Class>(m, "RKDP5").def(nb::init<>());
		nb_class
			.def("set_absolute_tolerance", &Class::set_absolute_tolerance)
			.def("absolute_tolerance", &Class::absolute_tolerance);
		nb_class
			.def("set_relative_tolerance", &Class::set_relative_tolerance)
			.def("relative_tolerance", &Class::relative_tolerance);
		nb_class
			.def("set_max_step", &Class::set_max_step)
			.def("max_step", &Class::max_step);
		nb_class
			.def("set_first_step", &Class::set_first_step)
			.def("first_step", &Class::first_step);
	}
	{
		using Class = environment;
		auto nb_class = nb::class_<Class>(m, "Environment").def(nb::init<>());
		nb_class
			.def("set_adiabatic_index", &Class::set_adiabatic_index)
			.def("adiabatic_index", &Class::adiabatic_index);
		nb_class
			.def("set_specific_gas_constant", &Class::set_specific_gas_constant)
			.def("specific_gas_constant", &Class::specific_gas_constant);
		nb_class
			.def("set_temperature", nb::overload_cast<scalar>(&Class::set_temperature))
			.def("set_temperature", [](Class &self, std::function<scalar(scalar)> profile) -> Class & { return self.set_temperature(std::move(profile)); })
			.def("set_temperature", [](Class &self, std::function<scalar(vector3)> field) -> Class & { return self.set_temperature(std::move(field)); })
			.def("set_temperature", [](Class &self, std::function<scalar(scalar)> profile, scalar interpolator_step) -> Class & { return self.set_temperature(std::move(profile), interpolator_step); })
			.def("set_temperature", [](Class &self, std::function<scalar(vector3)> field, scalar interpolator_step) -> Class & { return self.set_temperature(std::move(field), interpolator_step); })
			.def("temperature", &Class::temperature);
		nb_class
			.def("set_pressure", nb::overload_cast<scalar>(&Class::set_pressure))
			.def("set_pressure", [](Class &self, std::function<scalar(scalar)> profile) -> Class & { return self.set_pressure(std::move(profile)); })
			.def("set_pressure", [](Class &self, std::function<scalar(vector3)> field) -> Class & { return self.set_pressure(std::move(field)); })
			.def("set_pressure", [](Class &self, std::function<scalar(scalar)> profile, scalar interpolator_step) -> Class & { return self.set_pressure(std::move(profile), interpolator_step); })
			.def("set_pressure", [](Class &self, std::function<scalar(vector3)> field, scalar interpolator_step) -> Class & { return self.set_pressure(std::move(field), interpolator_step); })
			.def("pressure", &Class::pressure);
		nb_class
			.def("set_gravity", nb::overload_cast<vector3>(&Class::set_gravity))
			.def("set_gravity", [](Class &self, std::function<vector3(scalar)> profile) -> Class & { return self.set_gravity(std::move(profile)); })
			.def("set_gravity", [](Class &self, std::function<vector3(vector3)> field) -> Class & { return self.set_gravity(std::move(field)); })
			.def("set_gravity", [](Class &self, std::function<vector3(scalar)> profile, scalar interpolator_step) -> Class & { return self.set_gravity(std::move(profile), interpolator_step); })
			.def("set_gravity", [](Class &self, std::function<vector3(vector3)> field, scalar interpolator_step) -> Class & { return self.set_gravity(std::move(field), interpolator_step); })
			.def("gravity", &Class::gravity);
		nb_class
			.def("set_wind_velocity", nb::overload_cast<vector3>(&Class::set_wind_velocity))
			.def("set_wind_velocity", [](Class &self, std::function<vector3(scalar)> profile) -> Class & { return self.set_wind_velocity(std::move(profile)); })
			.def("set_wind_velocity", [](Class &self, std::function<vector3(vector3)> field) -> Class & { return self.set_wind_velocity(std::move(field)); })
			.def("set_wind_velocity", [](Class &self, std::function<vector3(scalar)> profile, scalar interpolator_step) -> Class & { return self.set_wind_velocity(std::move(profile), interpolator_step); })
			.def("set_wind_velocity", [](Class &self, std::function<vector3(vector3)> field, scalar interpolator_step) -> Class & { return self.set_wind_velocity(std::move(field), interpolator_step); })
			.def("wind_velocity", &Class::wind_velocity);
	}
	{
		using Class = projectile;
		auto nb_class = nb::class_<Class>(m, "Projectile").def(nb::init<>());
		nb_class
			.def("set_mass", &Class::set_mass)
			.def("mass", &Class::mass);
		nb_class
			.def("set_diameter", &Class::set_diameter)
			.def("diameter", &Class::diameter);
		nb_class
			.def("set_axial_moment_of_inertia", &Class::set_axial_moment_of_inertia)
			.def("axial_moment_of_inertia", &Class::axial_moment_of_inertia);
		nb_class
			.def("set_form_factor", &Class::set_form_factor)
			.def("form_factor", &Class::form_factor);
		nb_class
			.def("set_drag_factor", &Class::set_drag_factor)
			.def("drag_factor", &Class::drag_factor);
		nb_class
			.def("set_lift_factor", &Class::set_lift_factor)
			.def("lift_factor", &Class::lift_factor);
		nb_class
			.def("set_yaw_drag_factor", &Class::set_yaw_drag_factor)
			.def("yaw_drag_factor", &Class::yaw_drag_factor);
		nb_class
			.def("set_magnus_force_factor", &Class::set_magnus_force_factor)
			.def("magnus_force_factor", &Class::magnus_force_factor);
		nb_class
			.def("set_drag_force_coefficient", nb::overload_cast<scalar>(&Class::set_drag_force_coefficient))
			.def("set_drag_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve) -> Class & { return self.set_drag_force_coefficient(std::move(curve)); })
			.def("set_drag_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve, scalar interpolator_step) -> Class & { return self.set_drag_force_coefficient(std::move(curve), interpolator_step); })
			.def("set_drag_force_coefficient", [](Class &self, std::vector<scalar> keys, std::vector<scalar> values) -> Class & { return self.set_drag_force_coefficient(std::move(keys), std::move(values)); })
			.def("drag_force_coefficient", &Class::drag_force_coefficient);
		nb_class
			.def("set_quadratic_yaw_drag_force_coefficient", nb::overload_cast<scalar>(&Class::set_quadratic_yaw_drag_force_coefficient))
			.def("set_quadratic_yaw_drag_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve) -> Class & { return self.set_quadratic_yaw_drag_force_coefficient(std::move(curve)); })
			.def("set_quadratic_yaw_drag_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve, scalar interpolator_step) -> Class & { return self.set_quadratic_yaw_drag_force_coefficient(std::move(curve), interpolator_step); })
			.def("set_quadratic_yaw_drag_force_coefficient", [](Class &self, std::vector<scalar> keys, std::vector<scalar> values) -> Class & { return self.set_quadratic_yaw_drag_force_coefficient(std::move(keys), std::move(values)); })
			.def("quadratic_yaw_drag_force_coefficient", &Class::quadratic_yaw_drag_force_coefficient);
		nb_class
			.def("set_quartic_yaw_drag_force_coefficient", nb::overload_cast<scalar>(&Class::set_quartic_yaw_drag_force_coefficient))
			.def("set_quartic_yaw_drag_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve) -> Class & { return self.set_quartic_yaw_drag_force_coefficient(std::move(curve)); })
			.def("set_quartic_yaw_drag_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve, scalar interpolator_step) -> Class & { return self.set_quartic_yaw_drag_force_coefficient(std::move(curve), interpolator_step); })
			.def("set_quartic_yaw_drag_force_coefficient", [](Class &self, std::vector<scalar> keys, std::vector<scalar> values) -> Class & { return self.set_quartic_yaw_drag_force_coefficient(std::move(keys), std::move(values)); })
			.def("quartic_yaw_drag_force_coefficient", &Class::quartic_yaw_drag_force_coefficient);
		nb_class
			.def("set_lift_force_coefficient", nb::overload_cast<scalar>(&Class::set_lift_force_coefficient))
			.def("set_lift_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve) -> Class & { return self.set_lift_force_coefficient(std::move(curve)); })
			.def("set_lift_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve, scalar interpolator_step) -> Class & { return self.set_lift_force_coefficient(std::move(curve), interpolator_step); })
			.def("set_lift_force_coefficient", [](Class &self, std::vector<scalar> keys, std::vector<scalar> values) -> Class & { return self.set_lift_force_coefficient(std::move(keys), std::move(values)); })
			.def("lift_force_coefficient", &Class::lift_force_coefficient);
		nb_class
			.def("set_cubic_lift_force_coefficient", nb::overload_cast<scalar>(&Class::set_cubic_lift_force_coefficient))
			.def("set_cubic_lift_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve) -> Class & { return self.set_cubic_lift_force_coefficient(std::move(curve)); })
			.def("set_cubic_lift_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve, scalar interpolator_step) -> Class & { return self.set_cubic_lift_force_coefficient(std::move(curve), interpolator_step); })
			.def("set_cubic_lift_force_coefficient", [](Class &self, std::vector<scalar> keys, std::vector<scalar> values) -> Class & { return self.set_cubic_lift_force_coefficient(std::move(keys), std::move(values)); })
			.def("cubic_lift_force_coefficient", &Class::cubic_lift_force_coefficient);
		nb_class
			.def("set_quintic_lift_force_coefficient", nb::overload_cast<scalar>(&Class::set_quintic_lift_force_coefficient))
			.def("set_quintic_lift_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve) -> Class & { return self.set_quintic_lift_force_coefficient(std::move(curve)); })
			.def("set_quintic_lift_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve, scalar interpolator_step) -> Class & { return self.set_quintic_lift_force_coefficient(std::move(curve), interpolator_step); })
			.def("set_quintic_lift_force_coefficient", [](Class &self, std::vector<scalar> keys, std::vector<scalar> values) -> Class & { return self.set_quintic_lift_force_coefficient(std::move(keys), std::move(values)); })
			.def("quintic_lift_force_coefficient", &Class::quintic_lift_force_coefficient);
		nb_class
			.def("set_magnus_force_coefficient", nb::overload_cast<scalar>(&Class::set_magnus_force_coefficient))
			.def("set_magnus_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve) -> Class & { return self.set_magnus_force_coefficient(std::move(curve)); })
			.def("set_magnus_force_coefficient", [](Class &self, std::function<scalar(scalar)> curve, scalar interpolator_step) -> Class & { return self.set_magnus_force_coefficient(std::move(curve), interpolator_step); })
			.def("set_magnus_force_coefficient", [](Class &self, std::vector<scalar> keys, std::vector<scalar> values) -> Class & { return self.set_magnus_force_coefficient(std::move(keys), std::move(values)); })
			.def("magnus_force_coefficient", &Class::magnus_force_coefficient);
		nb_class
			.def("set_overturning_moment_coefficient", nb::overload_cast<scalar>(&Class::set_overturning_moment_coefficient))
			.def("set_overturning_moment_coefficient", [](Class &self, std::function<scalar(scalar)> curve) -> Class & { return self.set_overturning_moment_coefficient(std::move(curve)); })
			.def("set_overturning_moment_coefficient", [](Class &self, std::function<scalar(scalar)> curve, scalar interpolator_step) -> Class & { return self.set_overturning_moment_coefficient(std::move(curve), interpolator_step); })
			.def("set_overturning_moment_coefficient", [](Class &self, std::vector<scalar> keys, std::vector<scalar> values) -> Class & { return self.set_overturning_moment_coefficient(std::move(keys), std::move(values)); })
			.def("overturning_moment_coefficient", &Class::overturning_moment_coefficient);
		nb_class
			.def("set_cubic_overturning_moment_coefficient", nb::overload_cast<scalar>(&Class::set_cubic_overturning_moment_coefficient))
			.def("set_cubic_overturning_moment_coefficient", [](Class &self, std::function<scalar(scalar)> curve) -> Class & { return self.set_cubic_overturning_moment_coefficient(std::move(curve)); })
			.def("set_cubic_overturning_moment_coefficient", [](Class &self, std::function<scalar(scalar)> curve, scalar interpolator_step) -> Class & { return self.set_cubic_overturning_moment_coefficient(std::move(curve), interpolator_step); })
			.def("set_cubic_overturning_moment_coefficient", [](Class &self, std::vector<scalar> keys, std::vector<scalar> values) -> Class & { return self.set_cubic_overturning_moment_coefficient(std::move(keys), std::move(values)); })
			.def("cubic_overturning_moment_coefficient", &Class::cubic_overturning_moment_coefficient);
		nb_class
			.def("set_spin_damping_moment_coefficient", nb::overload_cast<scalar>(&Class::set_spin_damping_moment_coefficient))
			.def("set_spin_damping_moment_coefficient", [](Class &self, std::function<scalar(scalar)> curve) -> Class & { return self.set_spin_damping_moment_coefficient(std::move(curve)); })
			.def("set_spin_damping_moment_coefficient", [](Class &self, std::function<scalar(scalar)> curve, scalar interpolator_step) -> Class & { return self.set_spin_damping_moment_coefficient(std::move(curve), interpolator_step); })
			.def("set_spin_damping_moment_coefficient", [](Class &self, std::vector<scalar> keys, std::vector<scalar> values) -> Class & { return self.set_spin_damping_moment_coefficient(std::move(keys), std::move(values)); })
			.def("spin_damping_moment_coefficient", &Class::spin_damping_moment_coefficient);
	}
#pragma endregion "CODEGEN BIND"

	{
		using Class = environment;
		nb::borrow<nb::class_<Class>>(nb::type<Class>()).def_static("isa", &Class::isa);
	}
}
