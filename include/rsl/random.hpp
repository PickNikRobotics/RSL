#pragma once

#include <cassert>
#include <random>
#include <type_traits>

namespace rsl {

/**
 * @brief Get a random number generator
 *
 * The first time this function is called it creates a thread_local random number generator. If a
 * seed sequence is provided on that first call it is used to create the generator, otherwise the
 * random device is used to seed the generator. After the first call to this function, if a seed
 * sequence is provided this function throws. The returned value is a reference to a thread_local
 * static generator.
 *
 * @param[in] seed_sequence Seed sequence for random number generator
 *
 * @return Seeded random number generator
 */
auto rng(std::seed_seq seed_sequence = {}) -> std::mt19937&;

/**
 * @brief Get a uniform real number in a given range
 *
 * @param[in] lower Lower bound, inclusive
 * @param[in] upper Upper bound, exclusive
 *
 * @tparam RealType Floating point type
 *
 * @return Uniform real in range [lower, upper)
 */
template <typename RealType>
auto uniform_real(RealType lower, RealType upper) {
    static_assert(std::is_floating_point_v<RealType>);
    assert(lower < upper);
    return std::uniform_real_distribution(lower, upper)(rng());
}

/**
 * @brief Get a uniform integer number in a given range
 *
 * @param[in] lower Lower bound, inclusive
 * @param[in] upper Upper bound, inclusive
 *
 * @tparam IntType Integral type
 *
 * @return Uniform integer in range [lower, upper]
 */
template <typename IntType>
auto uniform_int(IntType lower, IntType upper) {
    static_assert(std::is_integral_v<IntType>);
    assert(lower <= upper);
    return std::uniform_int_distribution(lower, upper)(rng());
}

}  // namespace rsl
