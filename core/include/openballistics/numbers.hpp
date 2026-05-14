#ifndef OPENBALLISTICS_NUMBERS_HPP
#define OPENBALLISTICS_NUMBERS_HPP

namespace openballistics::numbers
{
    template <typename T>
    inline constexpr T pi_v = static_cast<T>(3.141592653589793238462643383279502884L);

    inline constexpr double pi = pi_v<double>;
}

#endif // OPENBALLISTICS_NUMBERS_HPP