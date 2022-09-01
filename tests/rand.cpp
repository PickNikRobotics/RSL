#include <rsl/rand.hpp>

#include <catch2/catch_all.hpp>

#include <thread>

TEST_CASE("rsl::rng") {
    auto const rng = &rsl::rng();

    SECTION("Repeated calls in thread yield same object") {
        CHECK(rng == &rsl::rng());
        CHECK(rng == &rsl::rng());
        CHECK(rng == &rsl::rng());
    }

    SECTION("Calls from separate threads yield separate objects") {
        std::thread([rng]() { CHECK(rng != &rsl::rng()); }).join();
    }

    SECTION("Throw if seeded after first call") {
        CHECK_NOTHROW(rsl::rng({}));
        CHECK_THROWS(rsl::rng({1, 2, 3, 4}));
    }
}

TEST_CASE("rsl::uniform_real") {
    constexpr auto lower = -100.;
    constexpr auto upper = 100.;
    for (int i = 0; i < 1'000; ++i) {
        auto const value = rsl::uniform_real(lower, upper);
        CHECK(value >= lower);
        CHECK(value < upper);
    }
}

TEST_CASE("rsl::uniform_int") {
    constexpr auto lower = -100;
    constexpr auto upper = 100;
    for (int i = 0; i < 1'000; ++i) {
        auto const value = rsl::uniform_int(lower, upper);
        CHECK(value >= lower);
        CHECK(value <= upper);
    }
}
