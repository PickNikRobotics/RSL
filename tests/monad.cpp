#include <rsl/monad.hpp>

#include <catch2/catch_test_macros.hpp>

#include <cmath>

static constexpr auto maybe_non_zero(int in) {
    return (in != 0) ? std::make_optional(in) : std::nullopt;
}

static auto maybe_lt_3_round(double in) {
    return (in < 3) ? std::optional<int>(std::round(in)) : std::nullopt;
}

static auto unsafe_divide_4_by(double val) {
    if (val == 0) throw std::runtime_error("divide by zero");
    return 4.0 / val;
}

TEST_CASE("rsl::mbind") {
    SECTION("Optional value") {
        // GIVEN optional value 4
        constexpr auto opt = std::make_optional(4);

        // WHEN we rsl::mbind it with the function maybe_non_zero
        // THEN we expect it true
        STATIC_REQUIRE(rsl::mbind(opt, maybe_non_zero));
    }

    SECTION("Overloaded optional value") {
        // GIVEN optional value -4.0
        constexpr auto opt = std::make_optional(-4.0);

        // WHEN we rsl::mbind it with two functions chained with operator| overload
        // THEN we expect it true
        CHECK((opt | maybe_lt_3_round | maybe_non_zero));
    }

    SECTION("Optional no value") {
        // GIVEN optional non value
        constexpr auto opt = std::optional<int>();

        // WHEN we rsl::mbind it with the function maybe_non_zero
        // THEN we expect it false
        CHECK_FALSE(rsl::mbind(opt, maybe_non_zero));
    }

    SECTION("Optional no value output") {
        // GIVEN optional value with 0.0
        constexpr auto opt = std::make_optional(0);

        // WHEN we rsl::mbind it with the function maybe_non_zero
        // THEN we expect it false
        CHECK_FALSE(rsl::mbind(opt, maybe_non_zero));
    }

    SECTION("Try") {
        // GIVEN input value of 0.0
        constexpr auto input = 0.0;

        // WHEN we pass unsafe_divide_4_by to rsl::mtry with out input
        // THEN we expect it to not throw
        CHECK_NOTHROW(rsl::mtry(std::bind(&unsafe_divide_4_by, input)));
    }

    SECTION("Try ok") {
        // GIVEN input value of 4.3
        constexpr auto input = 4.3;

        // WHEN we pass unsafe_divide_4_by to rsl::mtry with out input
        // THEN we expect it to not throw
        CHECK_NOTHROW(rsl::mtry(std::bind(&unsafe_divide_4_by, input)));
    }

    SECTION("Compose two") {
        // GIVEN the functions maybe_non_zero and maybe_lt_3_round and an input opt
        constexpr auto opt = std::make_optional(-4.0);

        // WHEN we compose them together and then bind them with an input
        auto const compose_result = opt | rsl::mcompose(maybe_lt_3_round, maybe_non_zero);

        // THEN we expect the result to be the same as if we chained the calls together
        auto const chain_result = opt | maybe_lt_3_round | maybe_non_zero;

        CHECK(compose_result == chain_result);
    }

    SECTION("Compose three") {
        // GIVEN the functions maybe_non_zero and maybe_lt_3_round and an input opt
        auto const opt = std::make_optional(-4.0);

        // WHEN we compose them together multiple times and then bind them with an input
        auto const compose_result =
            opt | rsl::mcompose(maybe_lt_3_round, maybe_non_zero, maybe_non_zero);

        // THEN we expect the result to be the same as if we chained the calls together
        auto const chain_result = opt | maybe_lt_3_round | maybe_non_zero | maybe_non_zero;

        CHECK(compose_result == chain_result);
    }
}

TEST_CASE("rsl::has_error") {
    SECTION("Error") {
        // GIVEN expected type containing error
        auto const exp = tl::expected<int, double>(tl::make_unexpected(0.1));

        // WHEN calling rsl::has_value and tl::expected::has_value
        // THEN we expect rsl::has_value is true, and tl::expected::has_value is false
        CHECK(rsl::has_error(exp));
        CHECK_FALSE(exp.has_value());
    }

    SECTION("Value") {
        // GIVEN expected type containing value
        auto const exp = tl::expected<int, double>(1);

        // WHEN calling rsl::has_value and tl::expected::has_value
        // THEN we expect rsl::has_value is false, and tl::expected::has_value is true
        CHECK_FALSE(rsl::has_error(exp));
        CHECK(exp.has_value());
    }
}

TEST_CASE("rsl::has_value") {
    SECTION("Error") {
        // GIVEN expected type containing error
        auto const exp = tl::expected<int, double>(tl::make_unexpected(0.1));

        // WHEN calling rsl::has_value and tl::expected::has_value
        // THEN we expect has_error is false, and has_value is false
        CHECK_FALSE(rsl::has_value(exp));
        CHECK_FALSE(exp.has_value());
    }

    SECTION("Value") {
        // GIVEN expected type containing value
        auto const exp = tl::expected<int, double>(1);

        // WHEN calling rsl::has_value and tl::expected::has_value
        // THEN we expect has_error is true, and has_value is true
        CHECK(rsl::has_value(exp));
        CHECK(exp.has_value());
    }
}
