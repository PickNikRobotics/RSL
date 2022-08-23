#pragma once

#include <cassert>
#include <random>

namespace rsl {

// The first time this function is called it creates a thread_local random
// number generator. If a seed sequence is provided on that first call it is
// used to create the generator, otherwise the random device is used to seed
// the generator. After the first call to this function, if a seed sequence is
// provided this function throws.
// The returned value is a reference to a thread_local static generator.
auto rng(std::seed_seq seed_sequence = {}) -> std::mt19937&;

template <typename T>
auto uniform_real(T lower, T upper) -> T {
  assert(lower < upper);
  return std::uniform_real_distribution<T>{lower, upper}(rng());
}

template <typename T>
auto uniform_int(T lower, T upper) -> T {
  assert(lower <= upper);
  return std::uniform_int_distribution<T>{lower, upper}(rng());
}

}  // namespace rsl
