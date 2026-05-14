#ifndef OPENBALLISTICS_INTERPOLATORS_LAZY_TRILINEAR_HPP
#define OPENBALLISTICS_INTERPOLATORS_LAZY_TRILINEAR_HPP

#include "../types.hpp"
#include <array>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <functional>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>

namespace openballistics::interpolators
{
    template <typename Value, size_t ChunkBits = 4>
    class [[nodiscard]] lazy_trilinear
    {
    public:
        using value_type = Value;

    private:
        static constexpr size_t chunk_bits = ChunkBits;
        static constexpr size_t chunk_dimension = 1ULL << chunk_bits;
        static constexpr size_t chunk_size = chunk_dimension * chunk_dimension * chunk_dimension;

        struct chunk
        {
            std::array<value_type, chunk_size> values;
            std::bitset<chunk_size> evaluated;
        };

    public:
        lazy_trilinear() = default;

        lazy_trilinear(std::function<value_type(vector3)> function, const scalar step)
            : m_function(std::move(function)), m_step(step)
        {
            if (m_step <= 1e-3)
                throw std::invalid_argument("lazy_trilinear: step size must be > 1e-3");
        }

    public:
        [[nodiscard]] value_type evaluate(const vector3 &position) const
        {
            const scalar x = position.x();
            const scalar y = position.y();
            const scalar z = position.z();

            const int64_t ix0 = static_cast<int64_t>(std::floor(x / m_step));
            const int64_t iy0 = static_cast<int64_t>(std::floor(y / m_step));
            const int64_t iz0 = static_cast<int64_t>(std::floor(z / m_step));
            const int64_t ix1 = ix0 + 1;
            const int64_t iy1 = iy0 + 1;
            const int64_t iz1 = iz0 + 1;

            const scalar xd = (x / m_step) - scalar(ix0);
            const scalar yd = (y / m_step) - scalar(iy0);
            const scalar zd = (z / m_step) - scalar(iz0);

            const int64_t cx0 = floor_div(ix0, int64_t(chunk_dimension));
            const int64_t cy0 = floor_div(iy0, int64_t(chunk_dimension));
            const int64_t cz0 = floor_div(iz0, int64_t(chunk_dimension));
            const int64_t cx1 = floor_div(ix1, int64_t(chunk_dimension));
            const int64_t cy1 = floor_div(iy1, int64_t(chunk_dimension));
            const int64_t cz1 = floor_div(iz1, int64_t(chunk_dimension));

            const size_t lx0 = size_t(ix0 - cx0 * int64_t(chunk_dimension));
            const size_t ly0 = size_t(iy0 - cy0 * int64_t(chunk_dimension));
            const size_t lz0 = size_t(iz0 - cz0 * int64_t(chunk_dimension));
            const size_t lx1 = size_t(ix1 - cx1 * int64_t(chunk_dimension));
            const size_t ly1 = size_t(iy1 - cy1 * int64_t(chunk_dimension));
            const size_t lz1 = size_t(iz1 - cz1 * int64_t(chunk_dimension));

            const bool xs = (cx0 != cx1);
            const bool ys = (cy0 != cy1);
            const bool zs = (cz0 != cz1);

            chunk *chunk_grid[2][2][2];

            if (!xs && !ys && !zs)
            {
                // 1 chunk
                chunk *c = &get_or_create_chunk(cx0, cy0, cz0);
                chunk_grid[0][0][0] = chunk_grid[1][0][0] =
                    chunk_grid[0][1][0] = chunk_grid[1][1][0] =
                        chunk_grid[0][0][1] = chunk_grid[1][0][1] =
                            chunk_grid[0][1][1] = chunk_grid[1][1][1] = c;
            }
            else if (xs && !ys && !zs)
            {
                // 2 chunks, x-split
                chunk *c0 = &get_or_create_chunk(cx0, cy0, cz0);
                chunk *c1 = &get_or_create_chunk(cx1, cy0, cz0);
                chunk_grid[0][0][0] = chunk_grid[0][1][0] =
                    chunk_grid[0][0][1] = chunk_grid[0][1][1] = c0;
                chunk_grid[1][0][0] = chunk_grid[1][1][0] =
                    chunk_grid[1][0][1] = chunk_grid[1][1][1] = c1;
            }
            else if (!xs && ys && !zs)
            {
                // 2 chunks, y-split
                chunk *c0 = &get_or_create_chunk(cx0, cy0, cz0);
                chunk *c1 = &get_or_create_chunk(cx0, cy1, cz0);
                chunk_grid[0][0][0] = chunk_grid[1][0][0] =
                    chunk_grid[0][0][1] = chunk_grid[1][0][1] = c0;
                chunk_grid[0][1][0] = chunk_grid[1][1][0] =
                    chunk_grid[0][1][1] = chunk_grid[1][1][1] = c1;
            }
            else if (!xs && !ys && zs)
            {
                // 2 chunks, z-split
                chunk *c0 = &get_or_create_chunk(cx0, cy0, cz0);
                chunk *c1 = &get_or_create_chunk(cx0, cy0, cz1);
                chunk_grid[0][0][0] = chunk_grid[1][0][0] =
                    chunk_grid[0][1][0] = chunk_grid[1][1][0] = c0;
                chunk_grid[0][0][1] = chunk_grid[1][0][1] =
                    chunk_grid[0][1][1] = chunk_grid[1][1][1] = c1;
            }
            else if (xs && ys && !zs)
            {
                // 4 chunks, xy-split
                chunk *c00 = &get_or_create_chunk(cx0, cy0, cz0);
                chunk *c10 = &get_or_create_chunk(cx1, cy0, cz0);
                chunk *c01 = &get_or_create_chunk(cx0, cy1, cz0);
                chunk *c11 = &get_or_create_chunk(cx1, cy1, cz0);
                chunk_grid[0][0][0] = chunk_grid[0][0][1] = c00;
                chunk_grid[1][0][0] = chunk_grid[1][0][1] = c10;
                chunk_grid[0][1][0] = chunk_grid[0][1][1] = c01;
                chunk_grid[1][1][0] = chunk_grid[1][1][1] = c11;
            }
            else if (xs && !ys && zs)
            {
                // 4 chunks, xz-split
                chunk *c00 = &get_or_create_chunk(cx0, cy0, cz0);
                chunk *c10 = &get_or_create_chunk(cx1, cy0, cz0);
                chunk *c01 = &get_or_create_chunk(cx0, cy0, cz1);
                chunk *c11 = &get_or_create_chunk(cx1, cy0, cz1);
                chunk_grid[0][0][0] = chunk_grid[0][1][0] = c00;
                chunk_grid[1][0][0] = chunk_grid[1][1][0] = c10;
                chunk_grid[0][0][1] = chunk_grid[0][1][1] = c01;
                chunk_grid[1][0][1] = chunk_grid[1][1][1] = c11;
            }
            else if (!xs && ys && zs)
            {
                // 4 chunks, yz-split
                chunk *c00 = &get_or_create_chunk(cx0, cy0, cz0);
                chunk *c10 = &get_or_create_chunk(cx0, cy1, cz0);
                chunk *c01 = &get_or_create_chunk(cx0, cy0, cz1);
                chunk *c11 = &get_or_create_chunk(cx0, cy1, cz1);
                chunk_grid[0][0][0] = chunk_grid[1][0][0] = c00;
                chunk_grid[0][1][0] = chunk_grid[1][1][0] = c10;
                chunk_grid[0][0][1] = chunk_grid[1][0][1] = c01;
                chunk_grid[0][1][1] = chunk_grid[1][1][1] = c11;
            }
            else // xs && ys && zs
            {
                // 8 chunks, all axes split
                chunk_grid[0][0][0] = &get_or_create_chunk(cx0, cy0, cz0);
                chunk_grid[1][0][0] = &get_or_create_chunk(cx1, cy0, cz0);
                chunk_grid[0][1][0] = &get_or_create_chunk(cx0, cy1, cz0);
                chunk_grid[1][1][0] = &get_or_create_chunk(cx1, cy1, cz0);
                chunk_grid[0][0][1] = &get_or_create_chunk(cx0, cy0, cz1);
                chunk_grid[1][0][1] = &get_or_create_chunk(cx1, cy0, cz1);
                chunk_grid[0][1][1] = &get_or_create_chunk(cx0, cy1, cz1);
                chunk_grid[1][1][1] = &get_or_create_chunk(cx1, cy1, cz1);
            }

            const value_type c000 = get_or_evaluate(*chunk_grid[0][0][0], lx0, ly0, lz0, ix0, iy0, iz0);
            const value_type c100 = get_or_evaluate(*chunk_grid[1][0][0], lx1, ly0, lz0, ix1, iy0, iz0);
            const value_type c010 = get_or_evaluate(*chunk_grid[0][1][0], lx0, ly1, lz0, ix0, iy1, iz0);
            const value_type c110 = get_or_evaluate(*chunk_grid[1][1][0], lx1, ly1, lz0, ix1, iy1, iz0);
            const value_type c001 = get_or_evaluate(*chunk_grid[0][0][1], lx0, ly0, lz1, ix0, iy0, iz1);
            const value_type c101 = get_or_evaluate(*chunk_grid[1][0][1], lx1, ly0, lz1, ix1, iy0, iz1);
            const value_type c011 = get_or_evaluate(*chunk_grid[0][1][1], lx0, ly1, lz1, ix0, iy1, iz1);
            const value_type c111 = get_or_evaluate(*chunk_grid[1][1][1], lx1, ly1, lz1, ix1, iy1, iz1);

            return trilerp(c000, c100, c010, c110, c001, c101, c011, c111, xd, yd, zd);
        }

    private:
        static int64_t floor_div(const int64_t a, const int64_t b)
        {
            return a / b - (a % b != 0 && (a ^ b) < 0);
        }

        static uint64_t pack_key(const int64_t cx, const int64_t cy, const int64_t cz)
        {
            auto zigzag = [](const int64_t v) -> uint64_t
            {
                return (v >= 0) ? uint64_t(v) << 1 : (uint64_t(-v) << 1) - 1;
            };
            return (zigzag(cx) << 42) | (zigzag(cy) << 21) | zigzag(cz);
        }

        chunk &get_or_create_chunk(const int64_t cx, const int64_t cy, const int64_t cz) const
        {
            auto &sptr = m_chunks[pack_key(cx, cy, cz)];
            if (!sptr)
                sptr = std::make_shared<chunk>();
            return *sptr;
        }

        value_type get_or_evaluate(chunk &chunk,
                                   const size_t lx, const size_t ly, const size_t lz,
                                   const int64_t gx, const int64_t gy, const int64_t gz) const
        {
            const size_t flat = lx * chunk_dimension * chunk_dimension + ly * chunk_dimension + lz;
            if (!chunk.evaluated[flat])
            {
                chunk.values[flat] = m_function(vector3(gx * m_step, gy * m_step, gz * m_step));
                chunk.evaluated[flat] = true;
            }
            return chunk.values[flat];
        }

        static value_type trilerp(const value_type &c000, const value_type &c100,
                                  const value_type &c010, const value_type &c110,
                                  const value_type &c001, const value_type &c101,
                                  const value_type &c011, const value_type &c111,
                                  const scalar xd, const scalar yd, const scalar zd)
        {
            const value_type c00 = c000 + xd * (c100 - c000);
            const value_type c01 = c001 + xd * (c101 - c001);
            const value_type c10 = c010 + xd * (c110 - c010);
            const value_type c11 = c011 + xd * (c111 - c011);
            const value_type c0 = c00 + yd * (c10 - c00);
            const value_type c1 = c01 + yd * (c11 - c01);
            return c0 + zd * (c1 - c0);
        }

    private:
        std::function<value_type(vector3)> m_function;
        scalar m_step;

        mutable std::unordered_map<uint64_t, std::shared_ptr<chunk>> m_chunks;
    };
}

#endif // OPENBALLISTICS_INTERPOLATORS_LAZY_TRILINEAR_HPP