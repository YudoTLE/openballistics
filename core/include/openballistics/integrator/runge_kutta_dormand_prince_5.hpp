#ifndef OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_DORMAND_PRINCE_5_HPP
#define OPENBALLISTICS_INTEGRATOR_RUNGE_KUTTA_DORMAND_PRINCE_5_HPP

#include "../types.hpp"
#include <utility>
#include <algorithm>
#include <cmath>
#include <limits>

namespace openballistics::integrator
{
    class runge_kutta_dormand_prince_5
    {
    private:
        static constexpr scalar c2 = 1.0 / 5.0;
        static constexpr scalar c3 = 3.0 / 10.0;
        static constexpr scalar c4 = 4.0 / 5.0;
        static constexpr scalar c5 = 8.0 / 9.0;

        static constexpr scalar a21 = 1.0 / 5.0;
        static constexpr scalar a31 = 3.0 / 40.0;
        static constexpr scalar a32 = 9.0 / 40.0;
        static constexpr scalar a41 = 44.0 / 45.0;
        static constexpr scalar a42 = -56.0 / 15.0;
        static constexpr scalar a43 = 32.0 / 9.0;
        static constexpr scalar a51 = 19372.0 / 6561.0;
        static constexpr scalar a52 = -25360.0 / 2187.0;
        static constexpr scalar a53 = 64448.0 / 6561.0;
        static constexpr scalar a54 = -212.0 / 729.0;
        static constexpr scalar a61 = 9017.0 / 3168.0;
        static constexpr scalar a62 = -355.0 / 33.0;
        static constexpr scalar a63 = 46732.0 / 5247.0;
        static constexpr scalar a64 = 49.0 / 176.0;
        static constexpr scalar a65 = -5103.0 / 18656.0;

        static constexpr scalar b1 = 35.0 / 384.0;
        static constexpr scalar b3 = 500.0 / 1113.0;
        static constexpr scalar b4 = 125.0 / 192.0;
        static constexpr scalar b5 = -2187.0 / 6784.0;
        static constexpr scalar b6 = 11.0 / 84.0;

        static constexpr scalar e1 = 71.0 / 57600.0;
        static constexpr scalar e3 = -71.0 / 16695.0;
        static constexpr scalar e4 = 71.0 / 1920.0;
        static constexpr scalar e5 = -17253.0 / 339200.0;
        static constexpr scalar e6 = 22.0 / 525.0;
        static constexpr scalar e7 = -1.0 / 40.0;

        static constexpr scalar d1 = -12715105075.0 / 11282082432.0;
        static constexpr scalar d3 = 87487479700.0 / 32700410799.0;
        static constexpr scalar d4 = -10690763975.0 / 1880347072.0;
        static constexpr scalar d5 = 701980252875.0 / 199316789632.0;
        static constexpr scalar d6 = -1453857185.0 / 822651844.0;
        static constexpr scalar d7 = 69997945.0 / 29380423.0;

        template <typename System, typename State>
        static scalar do_step(
            System &&sys,
            const State &in,
            const scalar t,
            State &out,
            const scalar dt,
            State &k1, State &k2, State &k3, State &k4, State &k5, State &k6, State &k7,
            State &xtmp,
            const scalar atol, const scalar rtol,
            const bool k1_valid = false)
        {
            const std::size_t n = in.size();

            if (!k1_valid)
                sys(in, k1, t);

            for (std::size_t i = 0; i < n; ++i)
                xtmp[i] = in[i] + dt * a21 * k1[i];
            sys(xtmp, k2, t + c2 * dt);

            for (std::size_t i = 0; i < n; ++i)
                xtmp[i] = in[i] + dt * (a31 * k1[i] + a32 * k2[i]);
            sys(xtmp, k3, t + c3 * dt);

            for (std::size_t i = 0; i < n; ++i)
                xtmp[i] = in[i] + dt * (a41 * k1[i] + a42 * k2[i] + a43 * k3[i]);
            sys(xtmp, k4, t + c4 * dt);

            for (std::size_t i = 0; i < n; ++i)
                xtmp[i] = in[i] + dt * (a51 * k1[i] + a52 * k2[i] + a53 * k3[i] + a54 * k4[i]);
            sys(xtmp, k5, t + c5 * dt);

            for (std::size_t i = 0; i < n; ++i)
                xtmp[i] = in[i] + dt * (a61 * k1[i] + a62 * k2[i] + a63 * k3[i] + a64 * k4[i] + a65 * k5[i]);
            sys(xtmp, k6, t + dt);

            for (std::size_t i = 0; i < n; ++i)
                out[i] = in[i] + dt * (b1 * k1[i] + b3 * k3[i] + b4 * k4[i] + b5 * k5[i] + b6 * k6[i]);

            sys(out, k7, t + dt);

            scalar err_sq = 0.0;
            for (std::size_t i = 0; i < n; ++i)
            {
                const scalar sc = atol + rtol * std::max(std::abs(in[i]), std::abs(out[i]));
                const scalar ei = dt * (e1 * k1[i] + e3 * k3[i] + e4 * k4[i] + e5 * k5[i] + e6 * k6[i] + e7 * k7[i]);
                err_sq += (ei / sc) * (ei / sc);
            }
            return std::sqrt(err_sq / static_cast<scalar>(n));
        }

        static scalar next_dt(const scalar dt, const scalar err, const scalar dtmax)
        {
            const scalar factor = (err == 0.0)
                                      ? 5.0
                                      : std::clamp(0.9 * std::pow(err, -0.2), 0.1, 5.0);
            return std::min(dt * factor, dtmax);
        }

    public:
        template <typename System, typename State>
        void integrate_basic(
            System &&system,
            State &x,
            const scalar t0,
            const scalar t1) const
        {
            State k1 = x, k2 = x, k3 = x, k4 = x, k5 = x, k6 = x, k7 = x, xtmp = x, xnew = x;

            const scalar atol = absolute_tolerance();
            const scalar rtol = relative_tolerance();
            const scalar dtmax = max_step();
            scalar t = t0;
            scalar dt = std::min(first_step(), t1 - t0);
            bool k1_valid = false;

            while (t < t1)
            {
                dt = std::min(dt, t1 - t);
                const scalar err = do_step(system, x, t, xnew, dt, k1, k2, k3, k4, k5, k6, k7, xtmp, atol, rtol, k1_valid);

                if (err <= 1.0)
                {
                    t += dt;
                    std::swap(x, xnew);
                    std::swap(k1, k7);
                    k1_valid = true;
                }

                dt = next_dt(dt, err, dtmax);
            }
        }

        template <typename System, typename State, typename Callback>
        void integrate_basic(
            System &&system,
            State &x,
            const scalar t0,
            const scalar t1,
            Callback &&callback) const
        {
            State k1 = x, k2 = x, k3 = x, k4 = x, k5 = x, k6 = x, k7 = x, xtmp = x, xnew = x;

            const scalar atol = absolute_tolerance();
            const scalar rtol = relative_tolerance();
            const scalar dtmax = max_step();
            scalar t = t0;
            scalar dt = std::min(first_step(), t1 - t0);
            bool k1_valid = false;

            while (t < t1)
            {
                callback(x, t);
                dt = std::min(dt, t1 - t);
                const scalar err = do_step(system, x, t, xnew, dt, k1, k2, k3, k4, k5, k6, k7, xtmp, atol, rtol, k1_valid);

                if (err <= 1.0)
                {
                    t += dt;
                    std::swap(x, xnew);
                    std::swap(k1, k7);
                    k1_valid = true;
                }

                dt = next_dt(dt, err, dtmax);
            }
            callback(x, t);
        }

        template <typename System, typename State, typename Callback>
        void integrate_dense(
            System &&system,
            State &x,
            const scalar t0,
            const scalar t1,
            Callback &&callback) const
        {
            State k1 = x, k2 = x, k3 = x, k4 = x, k5 = x, k6 = x, k7 = x, xtmp = x, xnew = x;

            const scalar atol = absolute_tolerance();
            const scalar rtol = relative_tolerance();
            const scalar dtmax = max_step();
            scalar t = t0;
            scalar dt = std::min(first_step(), t1 - t0);
            bool k1_valid = false;

            while (t < t1)
            {
                dt = std::min(dt, t1 - t);
                const scalar err = do_step(system, x, t, xnew, dt, k1, k2, k3, k4, k5, k6, k7, xtmp, atol, rtol, k1_valid);

                if (err <= 1.0)
                {
                    const std::size_t n = x.size();
                    State r0 = x, r1 = x, r2 = x, r3 = x, r4 = x;
                    for (std::size_t i = 0; i < n; ++i)
                    {
                        const scalar ydiff = xnew[i] - x[i];
                        const scalar bspl = dt * k1[i] - ydiff;
                        r0[i] = x[i];
                        r1[i] = ydiff;
                        r2[i] = bspl;
                        r3[i] = ydiff - dt * k7[i] - bspl;
                        r4[i] = dt * (d1 * k1[i] + d3 * k3[i] + d4 * k4[i] + d5 * k5[i] + d6 * k6[i] + d7 * k7[i]);
                    }

                    callback(
                        [r0 = std::move(r0), r1 = std::move(r1), r2 = std::move(r2),
                         r3 = std::move(r3), r4 = std::move(r4), ts = t, hs = dt](State& out, const scalar ti) -> void
                        {
                            const scalar theta = (ti - ts) / hs;
                            const scalar theta1 = scalar{1} - theta;
                            for (std::size_t i = 0; i < out.size(); ++i)
                                out[i] = r0[i] + theta * (r1[i] + theta1 * (r2[i] + theta * (r3[i] + theta1 * r4[i])));
                        },
                        t,
                        t + dt);

                    t += dt;
                    std::swap(x, xnew);
                    std::swap(k1, k7);
                    k1_valid = true;
                }

                dt = next_dt(dt, err, dtmax);
            }
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