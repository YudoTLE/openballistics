#ifndef OPENBALLISTICS_NUMBERS_HPP
#define OPENBALLISTICS_NUMBERS_HPP

namespace openballistics::numbers
{
    template <typename T>
    constexpr T pi = static_cast<T>(3.141592653589793238462643383279502884L);

    template <>
    constexpr float pi<float> = 3.14159265f;

    template <>
    constexpr double pi<double> = 3.1415926535897932;

    template <>
    constexpr long double pi<long double> = 3.141592653589793238462643383279502884L;
}

#endif // OPENBALLISTICS_NUMBERS_HPP