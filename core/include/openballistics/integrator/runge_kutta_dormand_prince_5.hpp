#ifndef OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_DORMAND_PRINCE_5_HPP
#define OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_DORMAND_PRINCE_5_HPP

#include "../types.hpp"
#include <boost/numeric/odeint.hpp>
#include <utility>
#include <limits>
#include <optional>

namespace openballistics::integrator
{
    class runge_kutta_dormand_prince_5
    {
    public:
        template <typename System, typename State>
        void integrate_basic(
            System &&system,
            State &x,
            const scalar t0,
            const scalar t1) const
        {
            auto stepper = boost::numeric::odeint::make_controlled(
                absolute_tolerance(),
                relative_tolerance(),
                max_step(),
                boost::numeric::odeint::runge_kutta_dopri5<State>());

            boost::numeric::odeint::integrate_adaptive(
                stepper,
                std::forward<System>(system),
                x,
                t0,
                t1,
                first_step());
        }

        template <typename System, typename State, typename Callback>
        void integrate_basic(
            System &&system,
            State &x,
            const scalar t0,
            const scalar t1,
            Callback &&callback) const
        {
            auto stepper = boost::numeric::odeint::make_controlled(
                absolute_tolerance(),
                relative_tolerance(),
                max_step(),
                boost::numeric::odeint::runge_kutta_dopri5<State>());

            boost::numeric::odeint::integrate_adaptive(
                stepper,
                std::forward<System>(system),
                x,
                t0,
                t1,
                first_step(),
                std::forward<Callback>(callback));
        }

        template <typename System, typename State, typename Callback>
        void integrate_dense(
            System &&system,
            State &x,
            const scalar t0,
            const scalar t1,
            Callback &&callback) const
        {
            auto stepper = boost::numeric::odeint::make_dense_output(
                absolute_tolerance(),
                relative_tolerance(),
                max_step(),
                boost::numeric::odeint::runge_kutta_dopri5<State>());

            const auto observer = [&](const State &x_curr, const scalar t)
            {
                const auto interpolate = [stepper](const scalar t_interp) -> State
                {
                    State out;
                    stepper.calc_state(t_interp, out);
                    return out;
                };

                callback(interpolate, t);
            };

            boost::numeric::odeint::integrate_adaptive(
                stepper,
                std::forward<System>(system),
                x,
                t0,
                t1,
                first_step(),
                observer);
        }

    public:
        runge_kutta_dormand_prince_5()
        {
#pragma region "CODEGEN INT-RK45-DEF" // AUTO-GENERATED - DO NOT EDIT MANUALLY
			set_absolute_tolerance(1e-6);
			set_relative_tolerance(1e-6);
			set_max_step(std::numeric_limits<scalar>::infinity());
			set_first_step(1e-3);
#pragma endregion "CODEGEN INT-RK45-DEF"
        }

    public:
#pragma region "CODEGEN INT-RK45-SET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		runge_kutta_dormand_prince_5 &set_absolute_tolerance(const scalar value)
		{
			m_absolute_tolerance_constant = value;
			return *this;
		}

		runge_kutta_dormand_prince_5 &set_relative_tolerance(const scalar value)
		{
			m_relative_tolerance_constant = value;
			return *this;
		}

		runge_kutta_dormand_prince_5 &set_max_step(const scalar value)
		{
			m_max_step_constant = value;
			return *this;
		}

		runge_kutta_dormand_prince_5 &set_first_step(const scalar value)
		{
			m_first_step_constant = value;
			return *this;
		}
#pragma endregion "CODEGEN INT-RK45-SET"

#pragma region "CODEGEN INT-RK45-GET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		[[nodiscard]] scalar absolute_tolerance() const
		{
			return m_absolute_tolerance_constant;
		}

		[[nodiscard]] scalar relative_tolerance() const
		{
			return m_relative_tolerance_constant;
		}

		[[nodiscard]] scalar max_step() const
		{
			return m_max_step_constant;
		}

		[[nodiscard]] scalar first_step() const
		{
			return m_first_step_constant;
		}
#pragma endregion "CODEGEN INT-RK45-GET"

    private:
#pragma region "CODEGEN INT-RK45-MEM" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		scalar m_absolute_tolerance_constant;

		scalar m_relative_tolerance_constant;

		scalar m_max_step_constant;

		scalar m_first_step_constant;
#pragma endregion "CODEGEN INT-RK45-MEM"
    };
}

#endif // OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_DORMAND_PRINCE_5_HPP