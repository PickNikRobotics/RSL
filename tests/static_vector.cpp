#include <rsl/static_vector.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("rsl::StaticVector") {
    SECTION("Construction") {
        SECTION("Default constructor") {
            auto const static_vector = rsl::StaticVector<int, 10>();
            CHECK(static_vector.begin() == static_vector.end());
        }

        SECTION("Collection constructor") {
            auto const vector = std::vector<int>{1, 2, 3, 4, 5};
            auto const static_vector = rsl::StaticVector<int, 5>(vector);
            CHECK(static_vector.begin() != static_vector.end());
            auto i = 1;
            for (auto const& number : static_vector) CHECK(number == i++);
        }

        SECTION("Initializer list constructor") {
            auto const static_vector = rsl::StaticVector<int, 5>{5, 4, 3, 2, 1};
            CHECK(static_vector.begin() != static_vector.end());
            auto i = 5;
            for (auto const& number : static_vector) CHECK(number == i--);
        }
    }

    SECTION("begin()") {
        SECTION("Non-const") {
            auto static_vector = rsl::StaticVector<int, 5>{5, 4, 3, 2, 1};
            CHECK(static_vector.begin() == std::begin(static_vector));
            CHECK(static_vector.begin() == std::cbegin(static_vector));
            CHECK(++*static_vector.begin() == 6);
        }

        SECTION("Const") {
            auto const static_vector = rsl::StaticVector<int, 5>{5, 4, 3, 2, 1};
            CHECK(static_vector.begin() == std::begin(static_vector));
            CHECK(static_vector.begin() == std::cbegin(static_vector));
            CHECK(*static_vector.begin() == 5);
        }
    }

    SECTION("end()") {
        SECTION("Non-const") {
            auto static_vector = rsl::StaticVector<int, 5>{10, 9, 8, 7, 6};
            CHECK(static_vector.end() == std::end(static_vector));
            CHECK(static_vector.end() == std::cend(static_vector));
            CHECK(--*(static_vector.end() - 1) == 5);
        }

        SECTION("Const") {
            auto const static_vector = rsl::StaticVector<int, 5>{5, 4, 3, 2, 1};
            CHECK(static_vector.end() == std::end(static_vector));
            CHECK(static_vector.end() == std::cend(static_vector));
            CHECK(*(static_vector.end() - 1) == 1);
        }
    }

    SECTION("User defined conversions") {
        SECTION("tcb::span<T>()") {
            auto static_vector = rsl::StaticVector<int, 5>{11, 12, 13, 14, 15};
            auto const span = tcb::span<int>(static_vector);
            CHECK(span[0] == 11);
            CHECK(span[1] == 12);
            CHECK(span[2] == 13);
            CHECK(span[3] == 14);
            CHECK(span[4] == 15);
        }

        SECTION("tcb::span<T const>()") {
            auto const static_vector = rsl::StaticVector<int, 5>{20, 19, 18, 17, 16};
            auto const span = tcb::span<int const>(static_vector);
            CHECK(span[0] == 20);
            CHECK(span[1] == 19);
            CHECK(span[2] == 18);
            CHECK(span[3] == 17);
            CHECK(span[4] == 16);
        }
    }
}

TEST_CASE("rsl::to_vector") {
    CHECK(rsl::to_vector(rsl::StaticVector<int, 0>{}).empty());
    CHECK(rsl::to_vector(rsl::StaticVector<int, 5>{1, 2, 3, 4, 5}) ==
          std::vector<int>{1, 2, 3, 4, 5});
}
