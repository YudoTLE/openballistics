#ifndef OPENBALLISTICS_BALLISTICS_HPP
#define OPENBALLISTICS_BALLISTICS_HPP

#include "./types.hpp"
#include "./numbers.hpp"
#include "./math/root.hpp"
#include "./angles.hpp"
#include "./environment.hpp"
#include "./projectile.hpp"
#include "./api/ballistics.hpp"
#include <unsupported/Eigen/LevenbergMarquardt>
#include <cmath>
#include <cstdint>
#include <functional>
#include <limits>
#include <optional>
#include <utility>
#include <vector>

namespace openballistics
{
    template <template <typename> class Model, typename Integrator>
    class ballistics : public Model<ballistics<Model, Integrator>>,
                       public api::detail::ballistics<ballistics<Model, Integrator>, Model<ballistics<Model, Integrator>>>
    {
    public:
        using model = Model<ballistics<Model, Integrator>>;
        using typename model::state;
        using typename model::weapon_parameters;

        template <typename, typename>
        friend class api::detail::ballistics;

    public:
        Integrator integrator;
        environment environment;
        projectile projectile;

    private:
        [[nodiscard]] vector3 compute_final_position_impl(
            const vector3 &launch_position,
            const vector3 &launch_direction,
            const vector3 &platform_velocity,
            const weapon_parameters &extra_parameters,
            const scalar time_of_flight) const
        {
            state x;
            this->initialize(x, launch_position, launch_direction, platform_velocity, extra_parameters);

            integrator.integrate_basic(
                [this](const state &x, state &dxdt, const scalar t) -> void
                {
                    this->derivative(x, dxdt, t);
                },
                x,
                0.0,
                time_of_flight);

            return x.template head<3>();
        }

        [[nodiscard]] std::vector<vector3> compute_trajectory_impl(
            const vector3 &launch_position,
            const vector3 &launch_direction,
            const vector3 &platform_velocity,
            const weapon_parameters &extra_parameters,
            const scalar start_time,
            const scalar end_time,
            const scalar sample_interval) const
        {
            state x;
            this->initialize(x, launch_position, launch_direction, platform_velocity, extra_parameters);

            std::vector<vector3> trajectory;

            scalar accumulator = start_time;

            integrator.integrate_dense(
                [this](const state &x, state &dxdt, const scalar t) -> void
                {
                    this->derivative(x, dxdt, t);
                },
                x,
                start_time,
                end_time,
                [&](auto interpolate, const scalar t0, const scalar t1)
                {
                    while (accumulator <= t1)
                    {
                        state x;
                        interpolate(x, accumulator);
                        trajectory.emplace_back(x.template head<3>());
                        accumulator += sample_interval;
                    }
                });

            return trajectory;
        }

        [[nodiscard]] vector3 optimize_launch_direction_impl(
            const vector3 &launch_position,
            const vector3 &platform_velocity,
            const vector3 &target_position,
            const weapon_parameters &extra_parameters,
            const scalar time_of_flight,
            const uint32_t max_iterations) const
        {
            struct Functor : public Eigen::DenseFunctor<scalar>
            {
                const ballistics *self;
                const vector3 &launch_position;
                const vector3 &platform_velocity;
                const vector3 &target_position;
                const weapon_parameters &extra_parameters;
                const scalar time_of_flight;

                Functor(
                    const ballistics *self,
                    const vector3 &launch_position,
                    const vector3 &platform_velocity,
                    const vector3 &target_position,
                    const weapon_parameters &extra_parameters,
                    const scalar time_of_flight)
                    : Eigen::DenseFunctor<scalar>(2, 3),
                      self(self),
                      launch_position(launch_position),
                      platform_velocity(platform_velocity),
                      target_position(target_position),
                      extra_parameters(extra_parameters),
                      time_of_flight(time_of_flight)
                {
                }

                int operator()(const InputType &x, ValueType &fvec) const
                {
                    const vector3 launch_direction = angles(x[0], x[1]).to_unit_direction();
                    const vector3 final_position = self->compute_final_position_impl(
                        launch_position,
                        launch_direction,
                        platform_velocity,
                        extra_parameters,
                        time_of_flight);

                    fvec = target_position - final_position;

                    return 0;
                }
            };

            const vector3 vacuum_displacement =
                target_position -
                launch_position -
                platform_velocity * time_of_flight -
                0.5 * environment.gravity(launch_position) * time_of_flight * time_of_flight;

            const angles initial_guess = angles::from_direction(vacuum_displacement);

            vectorx x(2);
            x << initial_guess.azimuth(), initial_guess.elevation();

            Functor functor(this, launch_position, platform_velocity, target_position, extra_parameters, time_of_flight);

            Eigen::NumericalDiff<Functor> diffFunctor(functor, 1e-7);
            Eigen::LevenbergMarquardt<Eigen::NumericalDiff<Functor>> lm(diffFunctor);

            lm.setFactor(numbers::pi<scalar> * 0.1);
            lm.setMaxfev(max_iterations);

            lm.minimize(x);

            return angles(x[0], x[1]).to_unit_direction();
        }

        [[nodiscard]] std::optional<vector3> solve_launch_direction_impl(
            const vector3 &launch_position,
            const vector3 &platform_velocity,
            const vector3 &target_position,
            const weapon_parameters &extra_parameters,
            const scalar time_of_flight,
            const scalar miss_distance_threshold,
            const uint32_t max_iterations) const
        {
            const vector3 launch_direction = optimize_launch_direction_impl(
                launch_position,
                platform_velocity,
                target_position,
                extra_parameters,
                time_of_flight,
                max_iterations);
            const vector3 final_position = compute_final_position_impl(
                launch_position,
                launch_direction,
                platform_velocity,
                extra_parameters,
                time_of_flight);

            if ((target_position - final_position).squaredNorm() > miss_distance_threshold * miss_distance_threshold)
                return std::nullopt;

            return launch_direction;
        }

        [[nodiscard]] std::optional<std::pair<vector3, scalar>> solve_launch_direction_and_time_of_flight_impl(
            const vector3 &launch_position,
            const vector3 &platform_velocity,
            const std::function<vector3(scalar)> &target_motion,
            const weapon_parameters &extra_parameters,
            const scalar min_time_of_flight,
            const scalar max_time_of_flight,
            const scalar miss_distance_threshold,
            const scalar time_of_flight_segment_size,
            const uint32_t time_of_flight_max_iterations,
            const uint32_t launch_direction_max_iterations) const
        {
            const scalar sq_miss_distance_threshold = miss_distance_threshold * miss_distance_threshold;

            auto proxy = [&](const scalar time_of_flight) -> scalar
            {
                const vector3 target_position = target_motion(time_of_flight);
                const vector3 launch_direction = optimize_launch_direction_impl(
                    launch_position,
                    platform_velocity,
                    target_position,
                    extra_parameters,
                    time_of_flight,
                    launch_direction_max_iterations);
                const vector3 final_position = compute_final_position_impl(
                    launch_position,
                    launch_direction,
                    platform_velocity,
                    extra_parameters,
                    time_of_flight);

                const vector3 target_position_to_final_position = final_position - target_position;

                return (target_position - launch_position).dot(target_position_to_final_position);
            };

            scalar segment_lo_time = min_time_of_flight;
            scalar segment_lo_proxy = proxy(min_time_of_flight);
            scalar segment_hi_time;
            scalar segment_hi_proxy;

            const math::root::eps_tolerance<scalar> tol(std::numeric_limits<scalar>::digits);
            auto solution = [&]() -> std::optional<std::pair<vector3, scalar>>
            {
                segment_hi_proxy = proxy(segment_hi_time);

                if (segment_lo_proxy * segment_hi_proxy > 0)
                    return std::nullopt;

                std::uintmax_t max_iter = time_of_flight_max_iterations;
                auto [lo, hi] = math::root::toms748_solve(
                    proxy,
                    segment_lo_time,
                    segment_hi_time,
                    segment_lo_proxy,
                    segment_hi_proxy,
                    tol,
                    max_iter);

                const scalar time_of_flight = lo;
                const vector3 target_position = target_motion(lo);
                const vector3 launch_direction = optimize_launch_direction_impl(
                    launch_position,
                    platform_velocity,
                    target_position,
                    extra_parameters,
                    time_of_flight,
                    launch_direction_max_iterations);
                const vector3 final_position = compute_final_position_impl(
                    launch_position,
                    launch_direction,
                    platform_velocity,
                    extra_parameters,
                    time_of_flight);

                if ((target_position - final_position).squaredNorm() > sq_miss_distance_threshold)
                    return std::nullopt;

                return std::make_pair(launch_direction, time_of_flight);
            };

            for (uint32_t i = 1;; ++i)
            {
                segment_hi_time = min_time_of_flight + i * time_of_flight_segment_size;
                if (segment_hi_time >= max_time_of_flight)
                    break;

                auto result = solution();
                if (result.has_value())
                    return std::move(result).value();

                segment_lo_time = segment_hi_time;
                segment_lo_proxy = segment_hi_proxy;
            }
            if (segment_lo_time < max_time_of_flight)
            {
                segment_hi_time = max_time_of_flight;

                auto result = solution();
                if (result.has_value())
                    return std::move(result).value();
            }

            return std::nullopt;
        }
    };
}

#endif // OPENBALLISTICS_BALLISTICS_HPP