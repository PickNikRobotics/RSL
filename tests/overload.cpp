#include <rsl/overload.hpp>

#include <catch2/catch_test_macros.hpp>

#include <variant>

TEST_CASE("rsl::Overload") {
    enum class Type { INT, FLOAT, STRING } type = Type::INT;
    auto const overload =
        rsl::Overload{[&type](int) { type = Type::INT; }, [&type](float) { type = Type::FLOAT; },
                      [&type](std::string const&) { type = Type::STRING; }};

    auto variant = std::variant<int, float, std::string>();

    variant = 12;
    std::visit(overload, variant);
    CHECK(type == Type::INT);

    variant = 42.f;
    std::visit(overload, variant);
    CHECK(type == Type::FLOAT);

    variant = "PickNik";
    std::visit(overload, variant);
    CHECK(type == Type::STRING);
}
