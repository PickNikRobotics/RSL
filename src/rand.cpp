#include <rsl/rand.hpp>

#include <algorithm>
#include <array>
#include <functional>
#include <random>
#include <stdexcept>

namespace rsl {

auto rng(std::seed_seq seed_sequence) -> std::mt19937& {
  thread_local bool first = true;
  thread_local std::mt19937 generator = [&seed_sequence]() {
    first = false;
    if (seed_sequence.size() > 0) {
      return std::mt19937(seed_sequence);
    }
    std::array<int, std::mt19937::state_size> seed_data;
    std::random_device random_device;
    std::generate_n(std::data(seed_data), std::size(seed_data),
                    std::ref(random_device));
    std::seed_seq sequence(std::begin(seed_data), std::end(seed_data));
    return std::mt19937(sequence);
  }();
  if (!first && seed_sequence.size() > 0) {
    throw std::runtime_error("rng cannot be re-seeded on this thread");
  }
  return generator;
}

}  // namespace rsl
