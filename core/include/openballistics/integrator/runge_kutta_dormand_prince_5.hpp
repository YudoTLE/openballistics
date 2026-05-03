#ifndef OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_DORMAND_PRINCE_5_HPP
#define OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_DORMAND_PRINCE_5_HPP

#include "../types.hpp"
#include <boost/numeric/odeint.hpp>
#include <utility>
#include <limits>
#include <optional>

namespace openballistics
{
    template <template <typename> class, typename, typename, typename>
    class ballistics;
}

namespace openballistics::integrator
{
    class runge_kutta_dormand_prince_5
    {
        template <template <typename> class, typename, typename, typename>
        friend class openballistics::ballistics;

    private:
        template <typename System, typename State>
        void integrate_basic(
            System &&system,
            State &x,
            const scalar t0,
            const scalar t1) const
        {
            auto stepper = boost::numeric::odeint::make_controlled<boost::numeric::odeint::runge_kutta_dopri5<State>>(absolute_tolerance(), relative_tolerance(), max_step());

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
            auto stepper = boost::numeric::odeint::make_controlled<boost::numeric::odeint::runge_kutta_dopri5<State>>(absolute_tolerance(), relative_tolerance(), max_step());

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
            auto stepper = boost::numeric::odeint::make_dense_output<boost::numeric::odeint::runge_kutta_dopri5<State>>(absolute_tolerance(), relative_tolerance(), max_step());

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
#pragma region "CODEGEN INT-RKDP5-SET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		runge_kutta_dormand_prince_5 &set_absolute_tolerance(const scalar value)
		{
			m_absolute_tolerance_constant = value;
			m_absolute_tolerance_source = 1;
			return *this;
		}

		runge_kutta_dormand_prince_5 &set_relative_tolerance(const scalar value)
		{
			m_relative_tolerance_constant = value;
			m_relative_tolerance_source = 1;
			return *this;
		}

		runge_kutta_dormand_prince_5 &set_max_step(const scalar value)
		{
			m_max_step_constant = value;
			m_max_step_source = 1;
			return *this;
		}

		runge_kutta_dormand_prince_5 &set_first_step(const scalar value)
		{
			m_first_step_constant = value;
			m_first_step_source = 1;
			return *this;
		}
#pragma endregion "CODEGEN INT-RKDP5-SET"

#pragma region "CODEGEN INT-RKDP5-GET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		[[nodiscard]] scalar absolute_tolerance() const
		{
			if (m_absolute_tolerance_source == 1) return m_absolute_tolerance_constant;
			throw std::bad_optional_access{};
		}

		[[nodiscard]] scalar relative_tolerance() const
		{
			if (m_relative_tolerance_source == 1) return m_relative_tolerance_constant;
			throw std::bad_optional_access{};
		}

		[[nodiscard]] scalar max_step() const
		{
			if (m_max_step_source == 1) return m_max_step_constant;
			throw std::bad_optional_access{};
		}

		[[nodiscard]] scalar first_step() const
		{
			if (m_first_step_source == 1) return m_first_step_constant;
			throw std::bad_optional_access{};
		}
#pragma endregion "CODEGEN INT-RKDP5-GET"

    private:
#pragma region "CODEGEN INT-RKDP5-MEM" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		bool m_absolute_tolerance_source = 0;
		scalar m_absolute_tolerance_constant;

		bool m_relative_tolerance_source = 0;
		scalar m_relative_tolerance_constant;

		bool m_max_step_source = 0;
		scalar m_max_step_constant;

		bool m_first_step_source = 0;
		scalar m_first_step_constant;
#pragma endregion "CODEGEN INT-RKDP5-MEM"
    };
}

#endif // OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_DORMAND_PRINCE_5_HPP