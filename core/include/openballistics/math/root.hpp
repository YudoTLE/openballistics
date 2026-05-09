// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef OPENBALLISTICS_MATH_ROOT_HPP
#define OPENBALLISTICS_MATH_ROOT_HPP

#include <cmath>
#include <limits>
#include <cstdint>
#include <utility>
#include <stdexcept>

namespace openballistics::math::root
{

    namespace detail
    {

        template <class F, class T>
        void bracket(F f, T &a, T &b, T c, T &fa, T &fb, T &d, T &fd)
        {
            const T tol = std::numeric_limits<T>::epsilon() * 2;
            if ((b - a) < 2 * tol * a)
                c = a + (b - a) / 2;
            else if (c <= a + std::fabs(a) * tol)
                c = a + std::fabs(a) * tol;
            else if (c >= b - std::fabs(b) * tol)
                c = b - std::fabs(b) * tol;

            T fc = f(c);
            if (fc == 0)
            {
                a = c;
                fa = 0;
                d = 0;
                fd = 0;
                return;
            }

            if (fa * fc < 0)
            {
                d = b;
                fd = fb;
                b = c;
                fb = fc;
            }
            else
            {
                d = a;
                fd = fa;
                a = c;
                fa = fc;
            }
        }

        template <class T>
        inline T safe_div(T num, T denom, T r)
        {
            if (std::fabs(denom) < 1)
                if (std::fabs(denom * std::numeric_limits<T>::max()) <= std::fabs(num))
                    return r;
            return num / denom;
        }

        template <class T>
        inline T secant_interpolate(const T &a, const T &b, const T &fa, const T &fb)
        {
            const T tol = std::numeric_limits<T>::epsilon() * 5;
            T c = a - (fa / (fb - fa)) * (b - a);
            if ((c <= a + std::fabs(a) * tol) || (c >= b - std::fabs(b) * tol))
                return (a + b) / 2;
            return c;
        }

        template <class T>
        T quadratic_interpolate(const T &a, const T &b, const T &d,
                                const T &fa, const T &fb, const T &fd,
                                unsigned count)
        {
            T B = safe_div(T(fb - fa), T(b - a), std::numeric_limits<T>::max());
            T A = safe_div(T(fd - fb), T(d - b), std::numeric_limits<T>::max());
            A = safe_div(T(A - B), T(d - a), T(0));

            if (A == 0)
                return secant_interpolate(a, b, fa, fb);

            T c = (A * fa > 0) ? a : b;
            for (unsigned i = 1; i <= count; ++i)
                c -= safe_div(T(fa + (B + A * (c - b)) * (c - a)), T(B + A * (2 * c - a - b)), T(1 + c - a));

            if ((c <= a) || (c >= b))
                c = secant_interpolate(a, b, fa, fb);
            return c;
        }

        template <class T>
        T cubic_interpolate(const T &a, const T &b, const T &d, const T &e,
                            const T &fa, const T &fb, const T &fd, const T &fe)
        {
            T q11 = (d - e) * fd / (fe - fd);
            T q21 = (b - d) * fb / (fd - fb);
            T q31 = (a - b) * fa / (fb - fa);
            T d21 = (b - d) * fd / (fd - fb);
            T d31 = (a - b) * fb / (fb - fa);
            T q22 = (d21 - q11) * fb / (fe - fb);
            T q32 = (d31 - q21) * fa / (fd - fa);
            T d32 = (d31 - q21) * fd / (fd - fa);
            T q33 = (d32 - q22) * fa / (fe - fa);
            T c = q31 + q32 + q33 + a;

            if ((c <= a) || (c >= b))
                c = quadratic_interpolate(a, b, d, fa, fb, fd, 3);
            return c;
        }

    }

    template <class F, class T, class Tol>
    std::pair<T, T> toms748_solve(F f, const T &ax, const T &bx, const T &fax, const T &fbx, Tol tol, std::uintmax_t &max_iter)
    {
        if (max_iter == 0)
            return {ax, bx};
        if (ax >= bx)
            throw std::domain_error("toms748: a >= b");
        if (fax * fbx > 0)
            throw std::domain_error("toms748: root not bracketed");

        std::uintmax_t count = max_iter;
        static const T mu = T(0.5);
        T a = ax, b = bx, fa = fax, fb = fbx;
        T c, u, fu, a0, b0, d, fd, e, fe;
        fe = e = fd = T(1e5);

        if (tol(a, b) || fa == 0 || fb == 0)
        {
            max_iter = 0;
            if (fa == 0)
                b = a;
            else if (fb == 0)
                a = b;
            return {a, b};
        }

        // step 1: secant
        c = detail::secant_interpolate(a, b, fa, fb);
        detail::bracket(f, a, b, c, fa, fb, d, fd);
        --count;

        if (count && fa != 0 && !tol(a, b))
        {
            // step 2: quadratic
            c = detail::quadratic_interpolate(a, b, d, fa, fb, fd, 2);
            e = d;
            fe = fd;
            detail::bracket(f, a, b, c, fa, fb, d, fd);
            --count;
        }

        while (count && fa != 0 && !tol(a, b))
        {
            a0 = a;
            b0 = b;
            const T min_diff = std::numeric_limits<T>::min() * 32;
            auto nearly_equal = [&](T x, T y)
            { return std::fabs(x - y) < min_diff; };
            bool prof = nearly_equal(fa, fb) || nearly_equal(fa, fd) || nearly_equal(fa, fe) ||
                        nearly_equal(fb, fd) || nearly_equal(fb, fe) || nearly_equal(fd, fe);

            c = prof ? detail::quadratic_interpolate(a, b, d, fa, fb, fd, 2)
                     : detail::cubic_interpolate(a, b, d, e, fa, fb, fd, fe);
            e = d;
            fe = fd;
            detail::bracket(f, a, b, c, fa, fb, d, fd);
            if ((0 == --count) || fa == 0 || tol(a, b))
                break;

            prof = nearly_equal(fa, fb) || nearly_equal(fa, fd) || nearly_equal(fa, fe) ||
                   nearly_equal(fb, fd) || nearly_equal(fb, fe) || nearly_equal(fd, fe);
            c = prof ? detail::quadratic_interpolate(a, b, d, fa, fb, fd, 3)
                     : detail::cubic_interpolate(a, b, d, e, fa, fb, fd, fe);
            detail::bracket(f, a, b, c, fa, fb, d, fd);
            if ((0 == --count) || fa == 0 || tol(a, b))
                break;

            // double-length secant
            if (std::fabs(fa) < std::fabs(fb))
            {
                u = a;
                fu = fa;
            }
            else
            {
                u = b;
                fu = fb;
            }
            c = u - 2 * (fu / (fb - fa)) * (b - a);
            if (std::fabs(c - u) > (b - a) / 2)
                c = a + (b - a) / 2;
            e = d;
            fe = fd;
            detail::bracket(f, a, b, c, fa, fb, d, fd);
            if ((0 == --count) || fa == 0 || tol(a, b))
                break;

            // bisection if not converging fast enough
            if ((b - a) < mu * (b0 - a0))
                continue;
            e = d;
            fe = fd;
            detail::bracket(f, a, b, T(a + (b - a) / 2), fa, fb, d, fd);
            --count;
        }

        max_iter -= count;
        if (fa == 0)
            b = a;
        else if (fb == 0)
            a = b;
        return {a, b};
    }

    // convenience tolerance
    template <class T>
    struct eps_tolerance
    {
        explicit eps_tolerance(unsigned bits = 0)
        {
            eps = bits ? std::max(T(std::ldexp(1.0f, 1 - (int)bits)), T(4 * std::numeric_limits<T>::epsilon()))
                       : T(4 * std::numeric_limits<T>::epsilon());
        }
        bool operator()(const T &a, const T &b) const
        {
            return std::fabs(a - b) <= eps * std::min(std::fabs(a), std::fabs(b));
        }
        T eps;
    };

}

#endif // OPENBALLISTICS_MATH_ROOT_HPP
