#ifndef OPENBALLISTICS_API_BALLISTICS_HPP
#define OPENBALLISTICS_API_BALLISTICS_HPP

#include "../types.hpp"
#include "../enums.hpp"
#include "../models.hpp"

namespace openballistics::api::detail
{
    template <typename Derived, typename Model>
    struct ballistics;

#pragma region "CODEGEN MODEL-PM-API" // AUTO-GENERATED - DO NOT EDIT MANUALLY
	template <typename Derived>
	struct ballistics<Derived, models::point_mass<Derived>>
	{
		/// @brief Computes the final position of the projectile at a specified time of flight.
		/// @details Integrates the projectile's equations of motion from the initial launch state over the exact duration specified by the time of flight, returning the resulting 3D position vector.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @returns 3D position vector of the projectile at the specified time of flight [m]
		[[nodiscard]] vector3 compute_final_position(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			scalar muzzle_velocity,
			scalar time_of_flight) const
		{
			return static_cast<const Derived *>(this)->compute_final_position_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				{muzzle_velocity},
				time_of_flight);
		}
		/// @brief Computes the final position of the projectile at a specified time of flight.
		/// @details Integrates the projectile's equations of motion from the initial launch state over the exact duration specified by the time of flight, returning the resulting 3D position vector.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @returns 3D position vector of the projectile at the specified time of flight [m]
		[[nodiscard]] vector3 compute_final_position(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			scalar muzzle_velocity,
			scalar time_of_flight) const
		{
			return static_cast<const Derived *>(this)->compute_final_position_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				{muzzle_velocity},
				time_of_flight);
		}
		/// @brief Computes a discrete sequence of positions representing the projectile's flight path.
		/// @details Integrates the projectile's equations of motion from the initial launch state over the specified time of flight, sampling and returning the 3D position vectors at fixed time intervals.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @param sample_interval Time step interval for sampling points along the computed trajectory [s]
		/// @returns Sequence of 3D position vectors sampled at fixed time intervals along the flight path [m]
		[[nodiscard]] std::vector<vector3> compute_trajectory(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			scalar muzzle_velocity,
			scalar time_of_flight,
			scalar sample_interval = 0.2) const
		{
			return static_cast<const Derived *>(this)->compute_trajectory_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				{muzzle_velocity},
				time_of_flight,
				sample_interval);
		}
		/// @brief Computes a discrete sequence of positions representing the projectile's flight path.
		/// @details Integrates the projectile's equations of motion from the initial launch state over the specified time of flight, sampling and returning the 3D position vectors at fixed time intervals.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @param sample_interval Time step interval for sampling points along the computed trajectory [s]
		/// @returns Sequence of 3D position vectors sampled at fixed time intervals along the flight path [m]
		[[nodiscard]] std::vector<vector3> compute_trajectory(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			scalar muzzle_velocity,
			scalar time_of_flight,
			scalar sample_interval = 0.2) const
		{
			return static_cast<const Derived *>(this)->compute_trajectory_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				{muzzle_velocity},
				time_of_flight,
				sample_interval);
		}
		/// @brief Solves for the optimal time of flight that minimizes the miss distance to a target for a fixed launch direction.
		/// @details Integrates the trajectory for a fixed launch direction within the specified time bounds and uses numerical minimization to find the exact time of flight at which the projectile's point of closest approach to the target occurs.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param min_time_of_flight Lower time of flight bound [s]
		/// @param max_time_of_flight Upper time of flight bound [s]
		/// @param solution_priority Criteria used to select a solution when multiple valid trajectories exist
		/// @param max_iterations Maximum number of allowed iterations for the time of flight numerical solver
		/// @returns Time of flight that minimizes the miss distance to the target [s]
		template <typename TargetPosition>
		[[nodiscard]] scalar optimize_time_of_flight(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar min_time_of_flight,
			scalar max_time_of_flight,
			priority solution_priority = priority::earliest,
			uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				solution_priority,
				max_iterations);
		}
		/// @brief Solves for the optimal time of flight that minimizes the miss distance to a target for a fixed launch direction.
		/// @details Integrates the trajectory for a fixed launch direction within the specified time bounds and uses numerical minimization to find the exact time of flight at which the projectile's point of closest approach to the target occurs.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param min_time_of_flight Lower time of flight bound [s]
		/// @param max_time_of_flight Upper time of flight bound [s]
		/// @param solution_priority Criteria used to select a solution when multiple valid trajectories exist
		/// @param max_iterations Maximum number of allowed iterations for the time of flight numerical solver
		/// @returns Time of flight that minimizes the miss distance to the target [s]
		template <typename TargetPosition>
		[[nodiscard]] scalar optimize_time_of_flight(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar min_time_of_flight,
			scalar max_time_of_flight,
			priority solution_priority = priority::earliest,
			uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				solution_priority,
				max_iterations);
		}
		/// @brief Solves for a time of flight that successfully intercepts a target for a fixed launch direction.
		/// @details Integrates the trajectory for a fixed launch direction within the specified time bounds and evaluates the proximity to the target, returning the time of flight if it results in a final distance less than or equal to the miss distance threshold. Returns empty if no valid time of flight satisfies the threshold constraint.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param min_time_of_flight Lower time of flight bound [s]
		/// @param max_time_of_flight Upper time of flight bound [s]
		/// @param miss_distance_threshold Maximum acceptable distance tolerance for identifying a successful target hit [m]
		/// @param solution_priority Criteria used to select a solution when multiple valid trajectories exist
		/// @param max_iterations Maximum number of allowed iterations for the time of flight numerical solver
		/// @returns Time of flight that intercepts the target within the miss distance threshold, or empty if no such solution exists [s]
		template <typename TargetPosition>
		[[nodiscard]] std::optional<scalar> solve_time_of_flight(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar min_time_of_flight,
			scalar max_time_of_flight,
			scalar miss_distance_threshold = 1.0,
			priority solution_priority = priority::earliest,
			uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->solve_time_of_flight_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				solution_priority,
				max_iterations);
		}
		/// @brief Solves for a time of flight that successfully intercepts a target for a fixed launch direction.
		/// @details Integrates the trajectory for a fixed launch direction within the specified time bounds and evaluates the proximity to the target, returning the time of flight if it results in a final distance less than or equal to the miss distance threshold. Returns empty if no valid time of flight satisfies the threshold constraint.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param min_time_of_flight Lower time of flight bound [s]
		/// @param max_time_of_flight Upper time of flight bound [s]
		/// @param miss_distance_threshold Maximum acceptable distance tolerance for identifying a successful target hit [m]
		/// @param solution_priority Criteria used to select a solution when multiple valid trajectories exist
		/// @param max_iterations Maximum number of allowed iterations for the time of flight numerical solver
		/// @returns Time of flight that intercepts the target within the miss distance threshold, or empty if no such solution exists [s]
		template <typename TargetPosition>
		[[nodiscard]] std::optional<scalar> solve_time_of_flight(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar min_time_of_flight,
			scalar max_time_of_flight,
			scalar miss_distance_threshold = 1.0,
			priority solution_priority = priority::earliest,
			uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->solve_time_of_flight_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				solution_priority,
				max_iterations);
		}
		/// @brief Solves for the optimal launch direction vector that minimizes the miss distance to a target for a fixed time of flight.
		/// @details Uses the Levenberg-Marquardt algorithm to iteratively adjust the launch direction vector, minimizing the distance between the projectile's final position and the target's position exactly at the specified time of flight.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @param max_iterations Maximum number of allowed iterations for the launch direction numerical solver
		/// @returns Direction vector that minimizes the miss distance to the target at the specified time of flight
		template <typename TargetPosition>
		[[nodiscard]] vector3 optimize_launch_direction(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar time_of_flight,
			uint32_t max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->optimize_launch_direction_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity},
				time_of_flight,
				max_iterations);
		}
		/// @brief Solves for the optimal launch direction vector that minimizes the miss distance to a target for a fixed time of flight.
		/// @details Uses the Levenberg-Marquardt algorithm to iteratively adjust the launch direction vector, minimizing the distance between the projectile's final position and the target's position exactly at the specified time of flight.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @param max_iterations Maximum number of allowed iterations for the launch direction numerical solver
		/// @returns Direction vector that minimizes the miss distance to the target at the specified time of flight
		template <typename TargetPosition>
		[[nodiscard]] vector3 optimize_launch_direction(
			const vector3 &launch_position,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar time_of_flight,
			uint32_t max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->optimize_launch_direction_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity},
				time_of_flight,
				max_iterations);
		}
		/// @brief Solves for a launch direction vector that successfully intercepts a target at a fixed time of flight.
		/// @details Optimizes the launch direction vector numerically and verifies if the resulting trajectory terminates within the specified miss distance threshold of the target. Returns empty if no valid orientation satisfies the threshold constraint.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @param miss_distance_threshold Maximum acceptable distance tolerance for identifying a successful target hit [m]
		/// @param max_iterations Maximum number of allowed iterations for the launch direction numerical solver
		/// @returns Direction vector that intercepts the target within the miss distance threshold at the specified time of flight, or empty if no such solution exists
		template <typename TargetPosition>
		[[nodiscard]] std::optional<vector3> solve_launch_direction(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar time_of_flight,
			scalar miss_distance_threshold = 1.0,
			uint32_t max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity},
				time_of_flight,
				miss_distance_threshold,
				max_iterations);
		}
		/// @brief Solves for a launch direction vector that successfully intercepts a target at a fixed time of flight.
		/// @details Optimizes the launch direction vector numerically and verifies if the resulting trajectory terminates within the specified miss distance threshold of the target. Returns empty if no valid orientation satisfies the threshold constraint.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @param miss_distance_threshold Maximum acceptable distance tolerance for identifying a successful target hit [m]
		/// @param max_iterations Maximum number of allowed iterations for the launch direction numerical solver
		/// @returns Direction vector that intercepts the target within the miss distance threshold at the specified time of flight, or empty if no such solution exists
		template <typename TargetPosition>
		[[nodiscard]] std::optional<vector3> solve_launch_direction(
			const vector3 &launch_position,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar time_of_flight,
			scalar miss_distance_threshold = 1.0,
			uint32_t max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity},
				time_of_flight,
				miss_distance_threshold,
				max_iterations);
		}
		/// @brief Solves simultaneously for the launch direction vector and time of flight required to intercept a target.
		/// @details Combines a root-finding algorithm (TOMS-748) for the time of flight with Levenberg-Marquardt optimization for the launch direction, progressively refining both iteratively until the projectile trajectory intersects the target within the allowable miss distance threshold.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param min_time_of_flight Lower time of flight bound [s]
		/// @param max_time_of_flight Upper time of flight bound [s]
		/// @param miss_distance_threshold Maximum acceptable distance tolerance for identifying a successful target hit [m]
		/// @param solution_priority Criteria used to select a solution when multiple valid trajectories exist
		/// @param time_of_flight_segment_size Duration size of each segment used to subdivide the search space during time of flight solving [s]
		/// @param time_of_flight_max_iterations Maximum number of allowed iterations for the time of flight numerical solver
		/// @param launch_direction_max_iterations Maximum number of allowed iterations for the launch direction numerical solver
		/// @returns Direction vector and time of flight that intercept the target within the miss distance threshold, or empty if no such solution exists
		template <typename TargetPosition>
		[[nodiscard]] std::optional<std::pair<vector3, scalar>> solve_launch_direction_and_time_of_flight(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			TargetPosition &&target_position,
			scalar muzzle_velocity,
			scalar min_time_of_flight,
			scalar max_time_of_flight,
			scalar miss_distance_threshold = 1.0,
			priority solution_priority = priority::earliest,
			scalar time_of_flight_segment_size = 0.5,
			uint32_t time_of_flight_max_iterations = 30,
			uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				solution_priority,
				time_of_flight_segment_size,
				time_of_flight_max_iterations,
				launch_direction_max_iterations);
		}
		/// @brief Solves simultaneously for the launch direction vector and time of flight required to intercept a target.
		/// @details Combines a root-finding algorithm (TOMS-748) for the time of flight with Levenberg-Marquardt optimization for the launch direction, progressively refining both iteratively until the projectile trajectory intersects the target within the allowable miss distance threshold.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param min_time_of_flight Lower time of flight bound [s]
		/// @param max_time_of_flight Upper time of flight bound [s]
		/// @param miss_distance_threshold Maximum acceptable distance tolerance for identifying a successful target hit [m]
		/// @param solution_priority Criteria used to select a solution when multiple valid trajectories exist
		/// @param time_of_flight_segment_size Duration size of each segment used to subdivide the search space during time of flight solving [s]
		/// @param time_of_flight_max_iterations Maximum number of allowed iterations for the time of flight numerical solver
		/// @param launch_direction_max_iterations Maximum number of allowed iterations for the launch direction numerical solver
		/// @returns Direction vector and time of flight that intercept the target within the miss distance threshold, or empty if no such solution exists
		template <typename TargetPosition>
		[[nodiscard]] std::optional<std::pair<vector3, scalar>> solve_launch_direction_and_time_of_flight(
			const vector3 &launch_position,
			TargetPosition &&target_position,
			scalar muzzle_velocity,
			scalar min_time_of_flight,
			scalar max_time_of_flight,
			scalar miss_distance_threshold = 1.0,
			priority solution_priority = priority::earliest,
			scalar time_of_flight_segment_size = 0.5,
			uint32_t time_of_flight_max_iterations = 30,
			uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				solution_priority,
				time_of_flight_segment_size,
				time_of_flight_max_iterations,
				launch_direction_max_iterations);
		}
	};
#pragma endregion "CODEGEN MODEL-PM-API"

#pragma region "CODEGEN MODEL-MPM-API" // AUTO-GENERATED - DO NOT EDIT MANUALLY
	template <typename Derived>
	struct ballistics<Derived, models::modified_point_mass<Derived>>
	{
		/// @brief Computes the final position of the projectile at a specified time of flight.
		/// @details Integrates the projectile's equations of motion from the initial launch state over the exact duration specified by the time of flight, returning the resulting 3D position vector.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @returns 3D position vector of the projectile at the specified time of flight [m]
		[[nodiscard]] vector3 compute_final_position(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar time_of_flight) const
		{
			return static_cast<const Derived *>(this)->compute_final_position_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight);
		}
		/// @brief Computes the final position of the projectile at a specified time of flight.
		/// @details Integrates the projectile's equations of motion from the initial launch state over the exact duration specified by the time of flight, returning the resulting 3D position vector.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @returns 3D position vector of the projectile at the specified time of flight [m]
		[[nodiscard]] vector3 compute_final_position(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar time_of_flight) const
		{
			return static_cast<const Derived *>(this)->compute_final_position_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				{muzzle_velocity, twist_of_rifling},
				time_of_flight);
		}
		/// @brief Computes a discrete sequence of positions representing the projectile's flight path.
		/// @details Integrates the projectile's equations of motion from the initial launch state over the specified time of flight, sampling and returning the 3D position vectors at fixed time intervals.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @param sample_interval Time step interval for sampling points along the computed trajectory [s]
		/// @returns Sequence of 3D position vectors sampled at fixed time intervals along the flight path [m]
		[[nodiscard]] std::vector<vector3> compute_trajectory(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar time_of_flight,
			scalar sample_interval = 0.2) const
		{
			return static_cast<const Derived *>(this)->compute_trajectory_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				sample_interval);
		}
		/// @brief Computes a discrete sequence of positions representing the projectile's flight path.
		/// @details Integrates the projectile's equations of motion from the initial launch state over the specified time of flight, sampling and returning the 3D position vectors at fixed time intervals.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @param sample_interval Time step interval for sampling points along the computed trajectory [s]
		/// @returns Sequence of 3D position vectors sampled at fixed time intervals along the flight path [m]
		[[nodiscard]] std::vector<vector3> compute_trajectory(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar time_of_flight,
			scalar sample_interval = 0.2) const
		{
			return static_cast<const Derived *>(this)->compute_trajectory_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				sample_interval);
		}
		/// @brief Solves for the optimal time of flight that minimizes the miss distance to a target for a fixed launch direction.
		/// @details Integrates the trajectory for a fixed launch direction within the specified time bounds and uses numerical minimization to find the exact time of flight at which the projectile's point of closest approach to the target occurs.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param min_time_of_flight Lower time of flight bound [s]
		/// @param max_time_of_flight Upper time of flight bound [s]
		/// @param solution_priority Criteria used to select a solution when multiple valid trajectories exist
		/// @param max_iterations Maximum number of allowed iterations for the time of flight numerical solver
		/// @returns Time of flight that minimizes the miss distance to the target [s]
		template <typename TargetPosition>
		[[nodiscard]] scalar optimize_time_of_flight(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar min_time_of_flight,
			scalar max_time_of_flight,
			priority solution_priority = priority::earliest,
			uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				solution_priority,
				max_iterations);
		}
		/// @brief Solves for the optimal time of flight that minimizes the miss distance to a target for a fixed launch direction.
		/// @details Integrates the trajectory for a fixed launch direction within the specified time bounds and uses numerical minimization to find the exact time of flight at which the projectile's point of closest approach to the target occurs.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param min_time_of_flight Lower time of flight bound [s]
		/// @param max_time_of_flight Upper time of flight bound [s]
		/// @param solution_priority Criteria used to select a solution when multiple valid trajectories exist
		/// @param max_iterations Maximum number of allowed iterations for the time of flight numerical solver
		/// @returns Time of flight that minimizes the miss distance to the target [s]
		template <typename TargetPosition>
		[[nodiscard]] scalar optimize_time_of_flight(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar min_time_of_flight,
			scalar max_time_of_flight,
			priority solution_priority = priority::earliest,
			uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				solution_priority,
				max_iterations);
		}
		/// @brief Solves for a time of flight that successfully intercepts a target for a fixed launch direction.
		/// @details Integrates the trajectory for a fixed launch direction within the specified time bounds and evaluates the proximity to the target, returning the time of flight if it results in a final distance less than or equal to the miss distance threshold. Returns empty if no valid time of flight satisfies the threshold constraint.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param min_time_of_flight Lower time of flight bound [s]
		/// @param max_time_of_flight Upper time of flight bound [s]
		/// @param miss_distance_threshold Maximum acceptable distance tolerance for identifying a successful target hit [m]
		/// @param solution_priority Criteria used to select a solution when multiple valid trajectories exist
		/// @param max_iterations Maximum number of allowed iterations for the time of flight numerical solver
		/// @returns Time of flight that intercepts the target within the miss distance threshold, or empty if no such solution exists [s]
		template <typename TargetPosition>
		[[nodiscard]] std::optional<scalar> solve_time_of_flight(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const vector3 &platform_velocity,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar min_time_of_flight,
			scalar max_time_of_flight,
			scalar miss_distance_threshold = 1.0,
			priority solution_priority = priority::earliest,
			uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->solve_time_of_flight_impl(
				launch_position,
				launch_direction.stableNormalized(),
				platform_velocity,
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				solution_priority,
				max_iterations);
		}
		/// @brief Solves for a time of flight that successfully intercepts a target for a fixed launch direction.
		/// @details Integrates the trajectory for a fixed launch direction within the specified time bounds and evaluates the proximity to the target, returning the time of flight if it results in a final distance less than or equal to the miss distance threshold. Returns empty if no valid time of flight satisfies the threshold constraint.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param launch_direction Direction vector representing the orientation of the launch
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param min_time_of_flight Lower time of flight bound [s]
		/// @param max_time_of_flight Upper time of flight bound [s]
		/// @param miss_distance_threshold Maximum acceptable distance tolerance for identifying a successful target hit [m]
		/// @param solution_priority Criteria used to select a solution when multiple valid trajectories exist
		/// @param max_iterations Maximum number of allowed iterations for the time of flight numerical solver
		/// @returns Time of flight that intercepts the target within the miss distance threshold, or empty if no such solution exists [s]
		template <typename TargetPosition>
		[[nodiscard]] std::optional<scalar> solve_time_of_flight(
			const vector3 &launch_position,
			const vector3 &launch_direction,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar min_time_of_flight,
			scalar max_time_of_flight,
			scalar miss_distance_threshold = 1.0,
			priority solution_priority = priority::earliest,
			uint32_t max_iterations = 30) const
		{
			return static_cast<const Derived *>(this)->solve_time_of_flight_impl(
				launch_position,
				launch_direction.stableNormalized(),
				vector3::Zero(),
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				solution_priority,
				max_iterations);
		}
		/// @brief Solves for the optimal launch direction vector that minimizes the miss distance to a target for a fixed time of flight.
		/// @details Uses the Levenberg-Marquardt algorithm to iteratively adjust the launch direction vector, minimizing the distance between the projectile's final position and the target's position exactly at the specified time of flight.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @param max_iterations Maximum number of allowed iterations for the launch direction numerical solver
		/// @returns Direction vector that minimizes the miss distance to the target at the specified time of flight
		template <typename TargetPosition>
		[[nodiscard]] vector3 optimize_launch_direction(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar time_of_flight,
			uint32_t max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->optimize_launch_direction_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				max_iterations);
		}
		/// @brief Solves for the optimal launch direction vector that minimizes the miss distance to a target for a fixed time of flight.
		/// @details Uses the Levenberg-Marquardt algorithm to iteratively adjust the launch direction vector, minimizing the distance between the projectile's final position and the target's position exactly at the specified time of flight.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @param max_iterations Maximum number of allowed iterations for the launch direction numerical solver
		/// @returns Direction vector that minimizes the miss distance to the target at the specified time of flight
		template <typename TargetPosition>
		[[nodiscard]] vector3 optimize_launch_direction(
			const vector3 &launch_position,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar time_of_flight,
			uint32_t max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->optimize_launch_direction_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				max_iterations);
		}
		/// @brief Solves for a launch direction vector that successfully intercepts a target at a fixed time of flight.
		/// @details Optimizes the launch direction vector numerically and verifies if the resulting trajectory terminates within the specified miss distance threshold of the target. Returns empty if no valid orientation satisfies the threshold constraint.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @param miss_distance_threshold Maximum acceptable distance tolerance for identifying a successful target hit [m]
		/// @param max_iterations Maximum number of allowed iterations for the launch direction numerical solver
		/// @returns Direction vector that intercepts the target within the miss distance threshold at the specified time of flight, or empty if no such solution exists
		template <typename TargetPosition>
		[[nodiscard]] std::optional<vector3> solve_launch_direction(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar time_of_flight,
			scalar miss_distance_threshold = 1.0,
			uint32_t max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				miss_distance_threshold,
				max_iterations);
		}
		/// @brief Solves for a launch direction vector that successfully intercepts a target at a fixed time of flight.
		/// @details Optimizes the launch direction vector numerically and verifies if the resulting trajectory terminates within the specified miss distance threshold of the target. Returns empty if no valid orientation satisfies the threshold constraint.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param time_of_flight Total duration of the projectile's flight from launch [s]
		/// @param miss_distance_threshold Maximum acceptable distance tolerance for identifying a successful target hit [m]
		/// @param max_iterations Maximum number of allowed iterations for the launch direction numerical solver
		/// @returns Direction vector that intercepts the target within the miss distance threshold at the specified time of flight, or empty if no such solution exists
		template <typename TargetPosition>
		[[nodiscard]] std::optional<vector3> solve_launch_direction(
			const vector3 &launch_position,
			const TargetPosition &target_position,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar time_of_flight,
			scalar miss_distance_threshold = 1.0,
			uint32_t max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity, twist_of_rifling},
				time_of_flight,
				miss_distance_threshold,
				max_iterations);
		}
		/// @brief Solves simultaneously for the launch direction vector and time of flight required to intercept a target.
		/// @details Combines a root-finding algorithm (TOMS-748) for the time of flight with Levenberg-Marquardt optimization for the launch direction, progressively refining both iteratively until the projectile trajectory intersects the target within the allowable miss distance threshold.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param platform_velocity Velocity vector of the launching platform relative to the global environment [m/s]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param min_time_of_flight Lower time of flight bound [s]
		/// @param max_time_of_flight Upper time of flight bound [s]
		/// @param miss_distance_threshold Maximum acceptable distance tolerance for identifying a successful target hit [m]
		/// @param solution_priority Criteria used to select a solution when multiple valid trajectories exist
		/// @param time_of_flight_segment_size Duration size of each segment used to subdivide the search space during time of flight solving [s]
		/// @param time_of_flight_max_iterations Maximum number of allowed iterations for the time of flight numerical solver
		/// @param launch_direction_max_iterations Maximum number of allowed iterations for the launch direction numerical solver
		/// @returns Direction vector and time of flight that intercept the target within the miss distance threshold, or empty if no such solution exists
		template <typename TargetPosition>
		[[nodiscard]] std::optional<std::pair<vector3, scalar>> solve_launch_direction_and_time_of_flight(
			const vector3 &launch_position,
			const vector3 &platform_velocity,
			TargetPosition &&target_position,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar min_time_of_flight,
			scalar max_time_of_flight,
			scalar miss_distance_threshold = 1.0,
			priority solution_priority = priority::earliest,
			scalar time_of_flight_segment_size = 0.5,
			uint32_t time_of_flight_max_iterations = 30,
			uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(
				launch_position,
				platform_velocity,
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				solution_priority,
				time_of_flight_segment_size,
				time_of_flight_max_iterations,
				launch_direction_max_iterations);
		}
		/// @brief Solves simultaneously for the launch direction vector and time of flight required to intercept a target.
		/// @details Combines a root-finding algorithm (TOMS-748) for the time of flight with Levenberg-Marquardt optimization for the launch direction, progressively refining both iteratively until the projectile trajectory intersects the target within the allowable miss distance threshold.
		/// @param launch_position Position vector representing the origin of the launch [m]
		/// @param target_position Static position vector or a time-dependent callable function representing the target's position over time [m]
		/// @param min_time_of_flight Lower time of flight bound [s]
		/// @param max_time_of_flight Upper time of flight bound [s]
		/// @param miss_distance_threshold Maximum acceptable distance tolerance for identifying a successful target hit [m]
		/// @param solution_priority Criteria used to select a solution when multiple valid trajectories exist
		/// @param time_of_flight_segment_size Duration size of each segment used to subdivide the search space during time of flight solving [s]
		/// @param time_of_flight_max_iterations Maximum number of allowed iterations for the time of flight numerical solver
		/// @param launch_direction_max_iterations Maximum number of allowed iterations for the launch direction numerical solver
		/// @returns Direction vector and time of flight that intercept the target within the miss distance threshold, or empty if no such solution exists
		template <typename TargetPosition>
		[[nodiscard]] std::optional<std::pair<vector3, scalar>> solve_launch_direction_and_time_of_flight(
			const vector3 &launch_position,
			TargetPosition &&target_position,
			scalar muzzle_velocity,
			scalar twist_of_rifling,
			scalar min_time_of_flight,
			scalar max_time_of_flight,
			scalar miss_distance_threshold = 1.0,
			priority solution_priority = priority::earliest,
			scalar time_of_flight_segment_size = 0.5,
			uint32_t time_of_flight_max_iterations = 30,
			uint32_t launch_direction_max_iterations = 25) const
		{
			return static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(
				launch_position,
				vector3::Zero(),
				target_position,
				{muzzle_velocity, twist_of_rifling},
				min_time_of_flight,
				max_time_of_flight,
				miss_distance_threshold,
				solution_priority,
				time_of_flight_segment_size,
				time_of_flight_max_iterations,
				launch_direction_max_iterations);
		}
	};
#pragma endregion "CODEGEN MODEL-MPM-API"
}

#endif // OPENBALLISTICS_API_BALLISTICS_HPP