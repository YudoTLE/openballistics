#ifndef OPENBALLISTICS_API_BALLISTICS_HPP
#define OPENBALLISTICS_API_BALLISTICS_HPP

#include "../types.hpp"
#include "../trajectory_model.hpp"

namespace openballistics::api::detail
{
    template <typename Derived, typename Model>
    struct ballistics;

#pragma region "CODEGEN TM-PM-API" // AUTO-GENERATED - DO NOT EDIT MANUALLY
	template <typename Derived>
	struct ballistics<Derived, trajectory_model::point_mass<Derived>>
	{
		[[nodiscard]] vector3 compute_final_position(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			const scalar muzzle_velocity,
			const scalar time_of_flight) const
		{
			return static_cast<const Derived *>(this)->compute_final_position_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				{muzzle_velocity},
				time_of_flight);
		}
		[[nodiscard]] vector3 compute_final_position(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const scalar muzzle_velocity,
			const scalar time_of_flight) const
		{
			return static_cast<const Derived *>(this)->compute_final_position_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				{muzzle_velocity},
				time_of_flight);
		}
		[[nodiscard]] vector3 compute_final_position(
			const vector3 &launch_position,
			const angles &launch_angles,
			const vector3 &platform_velocity,
			const scalar muzzle_velocity,
			const scalar time_of_flight) const
		{
			return static_cast<const Derived *>(this)->compute_final_position_impl(
				launch_position,
				launch_angles.to_unit_direction(),
				platform_velocity,
				{muzzle_velocity},
				time_of_flight);
		}
		[[nodiscard]] vector3 compute_final_position(
			const vector3 &launch_position,
			const angles &launch_angles,
			const scalar muzzle_velocity,
			const scalar time_of_flight) const
		{
			return static_cast<const Derived *>(this)->compute_final_position_impl(
				launch_position,
				launch_angles.to_unit_direction(),
				vector3::Zero(),
				{muzzle_velocity},
				time_of_flight);
		}
		[[nodiscard]] std::vector<vector3> compute_trajectory(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			const scalar muzzle_velocity,
			const scalar time_of_flight,
			const scalar sample_interval = 0.2) const
		{
			return static_cast<const Derived *>(this)->compute_trajectory_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				{muzzle_velocity},
				time_of_flight,
				sample_interval);
		}
		[[nodiscard]] std::vector<vector3> compute_trajectory(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const scalar muzzle_velocity,
			const scalar time_of_flight,
			const scalar sample_interval = 0.2) const
		{
			return static_cast<const Derived *>(this)->compute_trajectory_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				{muzzle_velocity},
				time_of_flight,
				sample_interval);
		}
		[[nodiscard]] std::vector<vector3> compute_trajectory(
			const vector3 &launch_position,
			const angles &launch_angles,
			const vector3 &platform_velocity,
			const scalar muzzle_velocity,
			const scalar time_of_flight,
			const scalar sample_interval = 0.2) const
		{
			return static_cast<const Derived *>(this)->compute_trajectory_impl(
				launch_position,
				launch_angles.to_unit_direction(),
				platform_velocity,
				{muzzle_velocity},
				time_of_flight,
				sample_interval);
		}
		[[nodiscard]] std::vector<vector3> compute_trajectory(
			const vector3 &launch_position,
			const angles &launch_angles,
			const scalar muzzle_velocity,
			const scalar time_of_flight,
			const scalar sample_interval = 0.2) const
		{
			return static_cast<const Derived *>(this)->compute_trajectory_impl(
				launch_position,
				launch_angles.to_unit_direction(),
				vector3::Zero(),
				{muzzle_velocity},
				time_of_flight,
				sample_interval);
		}
		[[nodiscard]] scalar optimize_time_of_flight(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				max_iterations);
		}
		[[nodiscard]] scalar optimize_time_of_flight(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				max_iterations);
		}
		[[nodiscard]] scalar optimize_time_of_flight(
			const vector3 &launch_position,
			const angles &launch_angles,
			const vector3 &platform_velocity,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(
				launch_position,
				launch_angles.to_unit_direction(),
				platform_velocity,
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				max_iterations);
		}
		[[nodiscard]] scalar optimize_time_of_flight(
			const vector3 &launch_position,
			const angles &launch_angles,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(
				launch_position,
				launch_angles.to_unit_direction(),
				vector3::Zero(),
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				max_iterations);
		}
		[[nodiscard]] vector3 optimize_launch_direction(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar time_of_flight,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->optimize_launch_direction_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity},
				time_of_flight,
				launch_direction_max_iterations);
		}
		[[nodiscard]] vector3 optimize_launch_direction(
			const vector3 &launch_position,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar time_of_flight,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->optimize_launch_direction_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity},
				time_of_flight,
				launch_direction_max_iterations);
		}
		[[nodiscard]] angles optimize_launch_angles(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar time_of_flight,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return angles::from_unit_direction(
				static_cast<const Derived *>(this)->optimize_launch_direction_impl(
					launch_position,
					platform_velocity,
					target_position,
					{muzzle_velocity},
					time_of_flight,
					launch_direction_max_iterations));
		}
		[[nodiscard]] angles optimize_launch_angles(
			const vector3 &launch_position,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar time_of_flight,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return angles::from_unit_direction(
				static_cast<const Derived *>(this)->optimize_launch_direction_impl(
					launch_position,
					vector3::Zero(),
					target_position,
					{muzzle_velocity},
					time_of_flight,
					launch_direction_max_iterations));
		}
		[[nodiscard]] std::optional<vector3> solve_launch_direction(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity},
				time_of_flight,
				miss_distance_threshold,
				launch_direction_max_iterations);
		}
		[[nodiscard]] std::optional<vector3> solve_launch_direction(
			const vector3 &launch_position,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity},
				time_of_flight,
				miss_distance_threshold,
				launch_direction_max_iterations);
		}
		[[nodiscard]] std::optional<angles> solve_launch_angles(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			std::optional<vector3> launch_direction = static_cast<const Derived *>(this)->solve_launch_direction_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity},
				time_of_flight,
				miss_distance_threshold,
				launch_direction_max_iterations);
			if (!launch_direction.has_value())
				return std::nullopt;
			return angles::from_unit_direction(launch_direction.value());
		}
		[[nodiscard]] std::optional<angles> solve_launch_angles(
			const vector3 &launch_position,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			std::optional<vector3> launch_direction = static_cast<const Derived *>(this)->solve_launch_direction_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity},
				time_of_flight,
				miss_distance_threshold,
				launch_direction_max_iterations);
			if (!launch_direction.has_value())
				return std::nullopt;
			return angles::from_unit_direction(launch_direction.value());
		}
		template <typename TargetPosition>
		[[nodiscard]] std::optional<std::pair<vector3, scalar>> solve_launch_direction_and_time_of_flight(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			TargetPosition &&target_position,
			const scalar muzzle_velocity,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const scalar time_of_flight_segment_size = 0.5,
			const uint32_t time_of_flight_max_iterations = 30,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				time_of_flight_segment_size,
				time_of_flight_max_iterations,
				launch_direction_max_iterations);
		}
		template <typename TargetPosition>
		[[nodiscard]] std::optional<std::pair<vector3, scalar>> solve_launch_direction_and_time_of_flight(
			const vector3 &launch_position,
			TargetPosition &&target_position,
			const scalar muzzle_velocity,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const scalar time_of_flight_segment_size = 0.5,
			const uint32_t time_of_flight_max_iterations = 30,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				time_of_flight_segment_size,
				time_of_flight_max_iterations,
				launch_direction_max_iterations);
		}
		template <typename TargetPosition>
		[[nodiscard]] std::optional<std::pair<angles, scalar>> solve_launch_angles_and_time_of_flight(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			TargetPosition &&target_position,
			const scalar muzzle_velocity,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const scalar time_of_flight_segment_size = 0.5,
			const uint32_t time_of_flight_max_iterations = 30,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			auto result = static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				time_of_flight_segment_size,
				time_of_flight_max_iterations,
				launch_direction_max_iterations);
			if (!result.has_value())
				return std::nullopt;
			return std::make_pair(angles::from_unit_direction(result->first), result->second);
		}
		template <typename TargetPosition>
		[[nodiscard]] std::optional<std::pair<angles, scalar>> solve_launch_angles_and_time_of_flight(
			const vector3 &launch_position,
			TargetPosition &&target_position,
			const scalar muzzle_velocity,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const scalar time_of_flight_segment_size = 0.5,
			const uint32_t time_of_flight_max_iterations = 30,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			auto result = static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				time_of_flight_segment_size,
				time_of_flight_max_iterations,
				launch_direction_max_iterations);
			if (!result.has_value())
				return std::nullopt;
			return std::make_pair(angles::from_unit_direction(result->first), result->second);
		}
	};
#pragma endregion "CODEGEN TM-PM-API"

#pragma region "CODEGEN TM-MPM-API" // AUTO-GENERATED - DO NOT EDIT MANUALLY
	template <typename Derived>
	struct ballistics<Derived, trajectory_model::modified_point_mass<Derived>>
	{
		[[nodiscard]] vector3 compute_final_position(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight) const
		{
			return static_cast<const Derived *>(this)->compute_final_position_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight);
		}
		[[nodiscard]] vector3 compute_final_position(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight) const
		{
			return static_cast<const Derived *>(this)->compute_final_position_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				{muzzle_velocity, twist_of_rifling},
				time_of_flight);
		}
		[[nodiscard]] vector3 compute_final_position(
			const vector3 &launch_position,
			const angles &launch_angles,
			const vector3 &platform_velocity,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight) const
		{
			return static_cast<const Derived *>(this)->compute_final_position_impl(
				launch_position,
				launch_angles.to_unit_direction(),
				platform_velocity,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight);
		}
		[[nodiscard]] vector3 compute_final_position(
			const vector3 &launch_position,
			const angles &launch_angles,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight) const
		{
			return static_cast<const Derived *>(this)->compute_final_position_impl(
				launch_position,
				launch_angles.to_unit_direction(),
				vector3::Zero(),
				{muzzle_velocity, twist_of_rifling},
				time_of_flight);
		}
		[[nodiscard]] std::vector<vector3> compute_trajectory(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight,
			const scalar sample_interval = 0.2) const
		{
			return static_cast<const Derived *>(this)->compute_trajectory_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				sample_interval);
		}
		[[nodiscard]] std::vector<vector3> compute_trajectory(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight,
			const scalar sample_interval = 0.2) const
		{
			return static_cast<const Derived *>(this)->compute_trajectory_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				sample_interval);
		}
		[[nodiscard]] std::vector<vector3> compute_trajectory(
			const vector3 &launch_position,
			const angles &launch_angles,
			const vector3 &platform_velocity,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight,
			const scalar sample_interval = 0.2) const
		{
			return static_cast<const Derived *>(this)->compute_trajectory_impl(
				launch_position,
				launch_angles.to_unit_direction(),
				platform_velocity,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				sample_interval);
		}
		[[nodiscard]] std::vector<vector3> compute_trajectory(
			const vector3 &launch_position,
			const angles &launch_angles,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight,
			const scalar sample_interval = 0.2) const
		{
			return static_cast<const Derived *>(this)->compute_trajectory_impl(
				launch_position,
				launch_angles.to_unit_direction(),
				vector3::Zero(),
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				sample_interval);
		}
		[[nodiscard]] scalar optimize_time_of_flight(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				max_iterations);
		}
		[[nodiscard]] scalar optimize_time_of_flight(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				max_iterations);
		}
		[[nodiscard]] scalar optimize_time_of_flight(
			const vector3 &launch_position,
			const angles &launch_angles,
			const vector3 &platform_velocity,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(
				launch_position,
				launch_angles.to_unit_direction(),
				platform_velocity,
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				max_iterations);
		}
		[[nodiscard]] scalar optimize_time_of_flight(
			const vector3 &launch_position,
			const angles &launch_angles,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(
				launch_position,
				launch_angles.to_unit_direction(),
				vector3::Zero(),
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				max_iterations);
		}
		[[nodiscard]] vector3 optimize_launch_direction(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->optimize_launch_direction_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				launch_direction_max_iterations);
		}
		[[nodiscard]] vector3 optimize_launch_direction(
			const vector3 &launch_position,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->optimize_launch_direction_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				launch_direction_max_iterations);
		}
		[[nodiscard]] angles optimize_launch_angles(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return angles::from_unit_direction(
				static_cast<const Derived *>(this)->optimize_launch_direction_impl(
					launch_position,
					platform_velocity,
					target_position,
					{muzzle_velocity, twist_of_rifling},
					time_of_flight,
					launch_direction_max_iterations));
		}
		[[nodiscard]] angles optimize_launch_angles(
			const vector3 &launch_position,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return angles::from_unit_direction(
				static_cast<const Derived *>(this)->optimize_launch_direction_impl(
					launch_position,
					vector3::Zero(),
					target_position,
					{muzzle_velocity, twist_of_rifling},
					time_of_flight,
					launch_direction_max_iterations));
		}
		[[nodiscard]] std::optional<vector3> solve_launch_direction(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				miss_distance_threshold,
				launch_direction_max_iterations);
		}
		[[nodiscard]] std::optional<vector3> solve_launch_direction(
			const vector3 &launch_position,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				miss_distance_threshold,
				launch_direction_max_iterations);
		}
		[[nodiscard]] std::optional<angles> solve_launch_angles(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			std::optional<vector3> launch_direction = static_cast<const Derived *>(this)->solve_launch_direction_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				miss_distance_threshold,
				launch_direction_max_iterations);
			if (!launch_direction.has_value())
				return std::nullopt;
			return angles::from_unit_direction(launch_direction.value());
		}
		[[nodiscard]] std::optional<angles> solve_launch_angles(
			const vector3 &launch_position,
			const vector3 &target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			std::optional<vector3> launch_direction = static_cast<const Derived *>(this)->solve_launch_direction_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				miss_distance_threshold,
				launch_direction_max_iterations);
			if (!launch_direction.has_value())
				return std::nullopt;
			return angles::from_unit_direction(launch_direction.value());
		}
		template <typename TargetPosition>
		[[nodiscard]] std::optional<std::pair<vector3, scalar>> solve_launch_direction_and_time_of_flight(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			TargetPosition &&target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const scalar time_of_flight_segment_size = 0.5,
			const uint32_t time_of_flight_max_iterations = 30,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				time_of_flight_segment_size,
				time_of_flight_max_iterations,
				launch_direction_max_iterations);
		}
		template <typename TargetPosition>
		[[nodiscard]] std::optional<std::pair<vector3, scalar>> solve_launch_direction_and_time_of_flight(
			const vector3 &launch_position,
			TargetPosition &&target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const scalar time_of_flight_segment_size = 0.5,
			const uint32_t time_of_flight_max_iterations = 30,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				time_of_flight_segment_size,
				time_of_flight_max_iterations,
				launch_direction_max_iterations);
		}
		template <typename TargetPosition>
		[[nodiscard]] std::optional<std::pair<angles, scalar>> solve_launch_angles_and_time_of_flight(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			TargetPosition &&target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const scalar time_of_flight_segment_size = 0.5,
			const uint32_t time_of_flight_max_iterations = 30,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			auto result = static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				time_of_flight_segment_size,
				time_of_flight_max_iterations,
				launch_direction_max_iterations);
			if (!result.has_value())
				return std::nullopt;
			return std::make_pair(angles::from_unit_direction(result->first), result->second);
		}
		template <typename TargetPosition>
		[[nodiscard]] std::optional<std::pair<angles, scalar>> solve_launch_angles_and_time_of_flight(
			const vector3 &launch_position,
			TargetPosition &&target_position,
			const scalar muzzle_velocity,
			const scalar twist_of_rifling,
			const scalar min_time_of_flight,
			const scalar max_time_of_flight,
			const scalar miss_distance_threshold = 1.0,
			const scalar time_of_flight_segment_size = 0.5,
			const uint32_t time_of_flight_max_iterations = 30,
			const uint32_t launch_direction_max_iterations = 25) const
		{
			auto result = static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				time_of_flight_segment_size,
				time_of_flight_max_iterations,
				launch_direction_max_iterations);
			if (!result.has_value())
				return std::nullopt;
			return std::make_pair(angles::from_unit_direction(result->first), result->second);
		}
	};
#pragma endregion "CODEGEN TM-MPM-API"
}

#endif // OPENBALLISTICS_API_BALLISTICS_HPP