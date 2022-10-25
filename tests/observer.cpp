#include <rsl/observer.hpp>

#include <catch2/catch_test_macros.hpp>
#include <rclcpp/executors.hpp>
#include <std_msgs/msg/int32.hpp>

static_assert(!std::is_copy_constructible_v<rsl::Observer<std_msgs::msg::Int32>>);
static_assert(!std::is_copy_assignable_v<rsl::Observer<std_msgs::msg::Int32>>);
static_assert(!std::is_nothrow_move_constructible_v<rsl::Observer<std_msgs::msg::Int32>>);
static_assert(!std::is_nothrow_move_assignable_v<rsl::Observer<std_msgs::msg::Int32>>);

static auto make(const std::int32_t value) {
    auto msg = std_msgs::msg::Int32();
    msg.data = value;
    return msg;
}

TEST_CASE("rsl::Observer") {
    auto node = std::make_shared<rclcpp::Node>("test");

    SECTION("Construction") {
        SECTION("Default QoS") {
            auto const observer = rsl::Observer<std_msgs::msg::Int32>(*node, "topic", make(42));
            CHECK(observer.get().data == 42);
        }

        SECTION("Specific QoS") {
            auto const observer = rsl::Observer<std_msgs::msg::Int32>(*node, "topic", make(42),
                                                                      rclcpp::ParameterEventsQoS());
            CHECK(observer.get().data == 42);
        }
    }

    SECTION("Implicit conversion") {
        auto const observer = rsl::Observer<std_msgs::msg::Int32>(*node, "topic", make(64));
        CHECK([](std_msgs::msg::Int32 const& msg) { return msg.data; }(observer) == 64);
    }

    SECTION("Subscription callback") {
        SECTION("Sequentially") {
            auto const observer = rsl::Observer<std_msgs::msg::Int32>(*node, "topic", make(-1));
            auto const publisher =
                node->create_publisher<std_msgs::msg::Int32>("topic", rclcpp::SystemDefaultsQoS());
            publisher->publish(make(72));
            rclcpp::spin_some(node);
            CHECK(observer.get().data == 72);
        }

        SECTION("Concurrently") {
            auto const observer = rsl::Observer<std_msgs::msg::Int32>(*node, "topic", make(100));

            // Try to read values being published below
            auto thread = std::thread([&node, &observer] {
                // Record previous value to ensure values are monotonically increasing
                static auto prev_value = std::int32_t(0);

                rclcpp::spin_some(node);
                const auto value = observer.get().data;
                CHECK(value >= 100);
                CHECK(value < 200);
                CHECK(value >= prev_value);
                prev_value = value;
            });

            // Publish values increasing in range [100, 200)
            auto const publisher =
                node->create_publisher<std_msgs::msg::Int32>("topic", rclcpp::SystemDefaultsQoS());
            for (std::int32_t i = 100; i < 200; ++i) publisher->publish(make(i));

            thread.join();
        }
    }
}
