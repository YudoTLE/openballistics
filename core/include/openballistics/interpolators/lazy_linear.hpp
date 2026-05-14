#ifndef OPENBALLISTICS_INTERPOLATORS_LAZY_LINEAR_HPP
#define OPENBALLISTICS_INTERPOLATORS_LAZY_LINEAR_HPP

#include "../types.hpp"
#include <array>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <functional>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace openballistics::interpolators
{
    template <typename Value, size_t ChunkBits = 20>
    class [[nodiscard]] lazy_linear
    {
    public:
        using value_type = Value;

    private:
        static constexpr size_t chunk_bits = ChunkBits;
        static constexpr size_t chunk_size = 1ULL << chunk_bits;
        static constexpr size_t chunk_mask = chunk_size - 1;

        struct chunk
        {
            std::array<value_type, chunk_size> values;
            std::bitset<chunk_size> evaluated;
        };

    public:
        lazy_linear() = default;

        lazy_linear(std::function<value_type(scalar)> function, const scalar step)
            : m_function(std::move(function)), m_step(step)
        {
            if (m_step <= 1e-3)
                throw std::invalid_argument("lazy_linear: Step size must be > 1e-3");
        }

    public:
        [[nodiscard]] value_type evaluate(const scalar value) const
        {
            const int64_t i0 = static_cast<int64_t>(std::floor(value / m_step));
            const int64_t i1 = i0 + 1;

            const scalar d = (value - (i0 * m_step)) / m_step;

            const value_type c0 = get_or_evaluate(i0);
            const value_type c1 = get_or_evaluate(i1);

            return lerp(c0, c1, d);
        }

    private:
        chunk &get_or_create_chunk(const int64_t index) const
        {
            const int64_t signed_chunk = index >> chunk_bits;
            const size_t mapped_chunk = (signed_chunk >= 0)
                                            ? (signed_chunk << 1)
                                            : ((-signed_chunk << 1) - 1);

            if (mapped_chunk >= m_chunks.size())
                m_chunks.resize(mapped_chunk + 1);

            if (!m_chunks[mapped_chunk])
                m_chunks[mapped_chunk] = std::make_shared<chunk>();

            return *m_chunks[mapped_chunk];
        }

        value_type get_or_evaluate(const int64_t index) const
        {
            const size_t local_index = index & chunk_mask;
            chunk &chunk = get_or_create_chunk(index);

            if (!chunk.evaluated[local_index])
            {
                chunk.values[local_index] = m_function(index * m_step);
                chunk.evaluated[local_index] = true;
            }

            return chunk.values[local_index];
        }

        static value_type lerp(const value_type &c0, const value_type &c1, const scalar d)
        {
            return c0 + d * (c1 - c0);
        }

    private:
        std::function<value_type(scalar)> m_function;
        scalar m_step;

        mutable std::vector<std::shared_ptr<chunk>> m_chunks;
    };
}

#endif // OPENBALLISTICS_INTERPOLATORS_LAZY_LINEAR_HPP