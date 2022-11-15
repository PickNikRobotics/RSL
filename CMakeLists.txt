cmake_minimum_required(VERSION 3.22)
project(rsl VERSION 0.2.0 LANGUAGES CXX DESCRIPTION "ROS Support Library")

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ament_cmake REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(fmt REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tcb_span REQUIRED)
find_package(tl_expected REQUIRED)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)
endif()

# Default to shared libraries to work around the Debian ecosystem's inability to specify -DBUILD_SHARED_LIBS=ON at configuration :(
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_library(rsl
    src/parameter_validators.cpp
    src/random.cpp
)
add_library(rsl::rsl ALIAS rsl)
target_compile_features(rsl PUBLIC cxx_std_17)
target_include_directories(rsl PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
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

install(
    DIRECTORY include/
    DESTINATION include
)
install(
    TARGETS rsl
    EXPORT export_rsl
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

ament_export_targets(export_rsl HAS_LIBRARY_TARGET)
ament_export_dependencies(
    Eigen3
    fmt
    rclcpp
    tcb_span
    tl_expected
)
ament_package()

add_custom_target(tidy COMMAND run-clang-tidy -p ${CMAKE_BINARY_DIR})
