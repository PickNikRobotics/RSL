#include <rsl/rand.hpp>

#include <algorithm>
#include <array>
#include <functional>
#include <stdexcept>

namespace rsl {

auto rng(std::seed_seq seed_sequence) -> std::mt19937& {
  thread_local auto first = true;
  thread_local auto generator = [&seed_sequence]() {
    first = false;
    if (seed_sequence.size() > 0) {
      return std::mt19937(seed_sequence);
    }
    auto seed_data = std::array<int, std::mt19937::state_size>();
    auto random_device = std::random_device();
    std::generate_n(std::data(seed_data), std::size(seed_data),
                    std::ref(random_device));
    auto sequence = std::seed_seq(std::begin(seed_data), std::end(seed_data));
    return std::mt19937(sequence);
  }();
  if (!first && seed_sequence.size() > 0) {
    throw std::runtime_error("rng cannot be re-seeded on this thread");
  }
  return generator;
}

}  // namespace rsl
