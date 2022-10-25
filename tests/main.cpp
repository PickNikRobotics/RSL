#include <catch2/catch_session.hpp>
#include <rclcpp/utilities.hpp>

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    return Catch::Session().run(argc, argv);
}
