#ifndef OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_4_HPP
#define OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_4_HPP

#include "../types.hpp"
#include <utility>
#include <optional>
#include <algorithm>

namespace openballistics::integrator
{
    class runge_kutta_4
    {
    private:
        template <typename System, typename State>
        static void do_step(System &&sys, const State &in, const scalar t, State &out, scalar dt, State &k1, State &k2, State &k3, State &k4, State &xtmp)
        {
            sys(in, k1, t);

            for (std::size_t i = 0; i < in.size(); ++i)
                xtmp[i] = in[i] + (dt * 0.5) * k1[i];
            sys(xtmp, k2, t + dt * 0.5);

            for (std::size_t i = 0; i < in.size(); ++i)
                xtmp[i] = in[i] + (dt * 0.5) * k2[i];
            sys(xtmp, k3, t + dt * 0.5);

            for (std::size_t i = 0; i < in.size(); ++i)
                xtmp[i] = in[i] + dt * k3[i];
            sys(xtmp, k4, t + dt);

            const scalar dt6 = dt / 6.0;
            const scalar dt3 = dt / 3.0;
            for (std::size_t i = 0; i < in.size(); ++i)
                out[i] = in[i] + dt6 * k1[i] + dt3 * k2[i] + dt3 * k3[i] + dt6 * k4[i];
        }

    public:
        template <typename System, typename State>
        int integrate_basic(
            System &&system,
            State &x,
            const scalar t0,
            const scalar t1) const
        {
            State k1 = x, k2 = x, k3 = x, k4 = x, xtmp = x;
            scalar t = t0;
            const scalar dt = step();

            while (t < t1)
            {
                const scalar current_dt = std::min(dt, t1 - t);
                do_step(system, x, t, x, current_dt, k1, k2, k3, k4, xtmp);
                t += current_dt;
            }

            return 0;
        }

        template <typename System, typename State, typename Callback>
        int integrate_basic(
            System &&system,
            State &x,
            const scalar t0,
            const scalar t1,
            Callback &&callback) const
        {
            int status = 0;

            State k1 = x, k2 = x, k3 = x, k4 = x, xtmp = x;
            scalar t = t0;
            const scalar dt = step();

            status = callback(x, t);
            if (status)
                return status;
            while (t < t1)
            {
                const scalar current_dt = std::min(dt, t1 - t);
                do_step(system, x, t, x, current_dt, k1, k2, k3, k4, xtmp);
                t += current_dt;
                status = callback(x, t);
                if (status)
                    return status;
            }

            return status;
        }

        template <typename System, typename State, typename Callback>
        int integrate_dense(
            System &&system,
            State &x,
            const scalar t0,
            const scalar t1,
            Callback &&callback) const
        {
            int status = 0;

            State k1 = x, k2 = x, k3 = x, k4 = x, xtmp = x;
            scalar t = t0;
            const scalar dt = step();

            while (t < t1)
            {
                const scalar current_dt = std::min(dt, t1 - t);
                status = callback(
                    [this, system, xs = x, ts = t](State &out, const scalar ti) -> void
                    {
                        State lk1 = xs, lk2 = xs, lk3 = xs, lk4 = xs, lxtmp = xs;
                        do_step(system, xs, ts, out, ti - ts, lk1, lk2, lk3, lk4, lxtmp);
                    },
                    t,
                    t + current_dt);

                do_step(system, x, t, x, current_dt, k1, k2, k3, k4, xtmp);
                if (status)
                    return status;
                t += current_dt;
            }

            return status;
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
			return *this;
		}
#pragma endregion "CODEGEN INT-RK4-SET"

#pragma region "CODEGEN INT-RK4-GET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		[[nodiscard]] scalar step() const
		{
			return m_step_constant;
		}
#pragma endregion "CODEGEN INT-RK4-GET"

    private:
#pragma region "CODEGEN INT-RK4-MEM" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		scalar m_step_constant;
#pragma endregion "CODEGEN INT-RK4-MEM"
    };
}

#endif // OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_4_HPP