#ifndef OPENBALLISTICS_INTERPOLATOR_LINEAR_HPP
#define OPENBALLISTICS_INTERPOLATOR_LINEAR_HPP

#include "../types.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace openballistics::interpolator
{
    template <typename Value>
    class [[nodiscard]] linear
    {
    public:
        using value_type = Value;

    public:
        linear() = delete;

        linear(std::vector<value_type> keys, std::vector<value_type> values)
        {
            const size_t n = keys.size();
            if (n < 1)
                throw std::invalid_argument("linear interpolator requires at least one key-value pair");
            if (values.size() != n)
                throw std::invalid_argument("linear interpolator requires keys and values of equal size");

            for (size_t i = 1; i < n; ++i)
            {
                if (keys[i] <= keys[i - 1])
                    throw std::invalid_argument("linear interpolator requires strictly monotonically increasing keys");
            }

            m_keys = std::move(keys);
            m_values = std::move(values);
            m_slopes.resize(n);

            for (size_t i = 0; i < n; ++i)
            {
                m_slopes[i] = (i + 1 < n)
                                  ? (m_values[i + 1] - m_values[i]) / (m_keys[i + 1] - m_keys[i])
                                  : value_type{};
            }
        }

    public:
        [[nodiscard]] inline value_type evaluate(const value_type key) const noexcept
        {
            if (key <= m_keys.front())
                return m_values.front();
            if (key >= m_keys.back())
                return m_values.back();

            auto it = std::upper_bound(m_keys.begin(), m_keys.end(), key);

            size_t idx = std::distance(m_keys.begin(), it) - 1;

            return m_values[idx] + m_slopes[idx] * (key - m_keys[idx]);
        }

    private:
        std::vector<value_type> m_keys;
        std::vector<value_type> m_values;
        std::vector<value_type> m_slopes;
    };
}
#endif // OPENBALLISTICS_INTERPOLATOR_LINEAR_HPP