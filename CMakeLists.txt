cmake_minimum_required(VERSION 3.22)
project(rsl VERSION 1.0.0 LANGUAGES CXX DESCRIPTION "ROS Support Library")

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ament_cmake_ros REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(fmt REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tcb_span REQUIRED)
find_package(tl_expected REQUIRED)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)
endif()

add_library(rsl
    src/parameter_validators.cpp
    src/random.cpp
)
add_library(rsl::rsl ALIAS rsl)
target_compile_features(rsl PUBLIC cxx_std_17)
target_include_directories(rsl PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_link_libraries(rsl PUBLIC
    Eigen3::Eigen
    fmt::fmt
    rclcpp::rclcpp
    tcb_span::tcb_span
    tl_expected::tl_expected
)

add_subdirectory(docs)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

include(CMakePackageConfigHelpers)

install(
    DIRECTORY include/
    DESTINATION include/rsl
)
install(
    TARGETS rsl EXPORT rsl-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include/rsl
)

ament_export_targets(rsl-targets HAS_LIBRARY_TARGET)
ament_export_dependencies(
    Eigen3
    fmt
    rclcpp
    tcb_span
    tl_expected
)
ament_package()

add_custom_target(tidy COMMAND run-clang-tidy -p ${CMAKE_BINARY_DIR})
