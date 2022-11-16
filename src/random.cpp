#include <rsl/random.hpp>

#include <algorithm>
#include <array>
#include <functional>
#include <stdexcept>

namespace rsl {

auto rng(std::seed_seq seed_sequence) -> std::mt19937& {
    thread_local auto is_seeded = false;
    if (is_seeded && seed_sequence.size() > 0)
        throw std::runtime_error("rng cannot be re-seeded on this thread");

    thread_local auto generator = [&seed_sequence]() {
        is_seeded = true;
        if (seed_sequence.size() > 0) return std::mt19937(seed_sequence);
        auto seed_data = std::array<int, std::mt19937::state_size>();
        auto random_device = std::random_device();
        std::generate_n(std::data(seed_data), std::size(seed_data), std::ref(random_device));
        auto sequence = std::seed_seq(std::begin(seed_data), std::end(seed_data));
        return std::mt19937(sequence);
    }();

    return generator;
}

auto random_unit_quaternion() -> Eigen::Quaterniond {
    // From "Uniform Random Rotations", Ken Shoemake, Graphics Gems III, pg. 124-132
    auto const x0 = uniform_real(0., 1.);
    auto const r1 = std::sqrt(1 - x0);
    auto const r2 = std::sqrt(x0);
    auto const t1 = uniform_real(0., 2 * M_PI);
    auto const t2 = uniform_real(0., 2 * M_PI);
    auto const x = r1 * std::sin(t1);
    auto const y = r1 * std::cos(t1);
    auto const z = r2 * std::sin(t2);
    auto const w = r2 * std::cos(t2);
    return Eigen::Quaterniond(w, x, y, z).normalized();
}

}  // namespace rsl
