cmake_minimum_required(VERSION 3.22)
project(rsl VERSION 1.1.0 LANGUAGES CXX DESCRIPTION "ROS Support Library")

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 REQUIRED)
find_package(fmt REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tcb_span REQUIRED)
find_package(tl_expected REQUIRED)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)
    if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.24.0")
        option(CMAKE_COMPILE_WARNING_AS_ERROR "Treat compiler warnings as errors." ON)
        mark_as_advanced(CMAKE_COMPILE_WARNING_AS_ERROR)
    else()
        add_compile_options(-Werror)
    endif()
endif()

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

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

option(RSL_BUILD_TESTING "Build tests" OFF)
if(RSL_BUILD_TESTING)
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
install(
    EXPORT rsl-targets
    NAMESPACE rsl::
    DESTINATION share/rsl/cmake
)
write_basic_package_version_file(rsl-config-version.cmake COMPATIBILITY SameMajorVersion)
install(
    FILES cmake/rsl-config.cmake ${PROJECT_BINARY_DIR}/rsl-config-version.cmake
    DESTINATION share/rsl/cmake
)

add_custom_target(tidy COMMAND run-clang-tidy -p ${CMAKE_BINARY_DIR})
