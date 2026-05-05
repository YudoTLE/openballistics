#ifndef OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_4_HPP
#define OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_4_HPP

#include "../types.hpp"
#include <boost/numeric/odeint.hpp>
#include <utility>
#include <optional>

namespace openballistics
{
    template <template <typename> class, typename, typename>
    class ballistics;
}

namespace openballistics::integrator
{
    class runge_kutta_4
    {
        template <template <typename> class, typename, typename>
        friend class openballistics::ballistics;

    private:
        template <typename System, typename State>
        void integrate_basic(
            System &&system,
            State &x,
            const scalar t0,
            const scalar t1) const
        {
            const boost::numeric::odeint::runge_kutta4<State> stepper;

            boost::numeric::odeint::integrate_const(
                stepper,
                std::forward<System>(system),
                x, t0, t1, step());
        }

        template <typename System, typename State, typename Callback>
        void integrate_basic(
            System &&system,
            State &x,
            const scalar t0,
            const scalar t1,
            Callback &&callback) const
        {
            const boost::numeric::odeint::runge_kutta4<State> stepper;

            boost::numeric::odeint::integrate_const(
                stepper,
                std::forward<System>(system),
                x, t0, t1, step(),
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
            boost::numeric::odeint::runge_kutta4<State> stepper;
            State x_prev = x;
            scalar t_prev = t0;

            const auto observer = [&](const State &x_curr, const scalar t) -> void
            {
                const auto interpolate = [system, x_prev, t_prev](const scalar t_interp) -> State
                {
                    State out = x_prev;
                    boost::numeric::odeint::runge_kutta4<State>().do_step(
                        system, out, t_prev, t_interp - t_prev);
                    return out;
                };

                callback(interpolate, t);
                x_prev = x_curr;
                t_prev = t;
            };

            boost::numeric::odeint::integrate_const(
                stepper,
                std::forward<System>(system),
                x, t0, t1, step(),
                observer);
        }

    public:
        runge_kutta_4()
        {
#pragma region "CODEGEN INT-RK4-DEF" // AUTO-GENERATED - DO NOT EDIT MANUALLY
			set_step(1e-3);
#pragma endregion "CODEGEN INT-RK4-DEF"
        }

    public:
#pragma region "CODEGEN INT-RK4-SET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		runge_kutta_4 &set_step(const scalar value)
		{
			m_step_constant = value;
			m_step_source = 1;
			return *this;
		}
#pragma endregion "CODEGEN INT-RK4-SET"

#pragma region "CODEGEN INT-RK4-GET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		[[nodiscard]] scalar step() const
		{
			if (m_step_source == 1) return m_step_constant;
			throw std::bad_optional_access{};
		}
#pragma endregion "CODEGEN INT-RK4-GET"

    private:
#pragma region "CODEGEN INT-RK4-MEM" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		bool m_step_source = 0;
		scalar m_step_constant;
#pragma endregion "CODEGEN INT-RK4-MEM"
    };
}

#endif // OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_4_HPP