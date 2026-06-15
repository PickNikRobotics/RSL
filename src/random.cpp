#include <rsl/random.hpp>

#include <algorithm>
#include <array>
#include <functional>
#if __has_include(<numbers>)
#include <numbers>
#endif
#include <optional>
#include <stdexcept>

namespace rsl {

namespace {

constexpr auto kPiFallback = 3.141592653589793238462643383279502884;

#if defined(__cpp_lib_math_constants) && (__cpp_lib_math_constants >= 201907L)
constexpr auto kPi = std::numbers::pi_v<double>;
#else
constexpr auto kPi = kPiFallback;
#endif

}  // namespace

auto rng(std::seed_seq seed_sequence) -> std::mt19937& {
    thread_local auto generator = std::optional<std::mt19937>();

    // Prevent reseeding the generator
    if (generator.has_value() && seed_sequence.size() > 0)
        throw std::runtime_error("rng cannot be re-seeded on this thread");

    // Return existing generator
    if (generator.has_value() && seed_sequence.size() == 0) return generator.value();

    // Seed with specified sequence
    if (seed_sequence.size() > 0) return generator.emplace(seed_sequence);

    // Seed with randomized sequence
    auto seed_data = std::array<std::random_device::result_type, std::mt19937::state_size>();
    auto random_device = std::random_device();
    std::generate_n(seed_data.data(), seed_data.size(), std::ref(random_device));
    auto sequence = std::seed_seq(seed_data.begin(), seed_data.end());
    return generator.emplace(sequence);
}

auto random_unit_quaternion() -> Eigen::Quaterniond {
    // From "Uniform Random Rotations", Ken Shoemake, Graphics Gems III, pg. 124-132
    auto const x0 = uniform_real(0., 1.);
    auto const r1 = std::sqrt(1 - x0);
    auto const r2 = std::sqrt(x0);
    auto const t1 = uniform_real(0., 2 * kPi);
    auto const t2 = uniform_real(0., 2 * kPi);
    auto const x = r1 * std::sin(t1);
    auto const y = r1 * std::cos(t1);
    auto const z = r2 * std::sin(t2);
    auto const w = r2 * std::cos(t2);
    return Eigen::Quaterniond(w, x, y, z).normalized();
}

}  // namespace rsl
