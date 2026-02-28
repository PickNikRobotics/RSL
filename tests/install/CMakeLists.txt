cmake_minimum_required(VERSION 3.22)
project(rsl-install-test CXX)

add_executable(test-rsl-install install.cpp)

if(PROJECT_IS_TOP_LEVEL)
    # Test consumption via find_package interface
    find_package(rsl 1.2.0 EXACT REQUIRED)

    target_link_libraries(test-rsl-install PRIVATE rsl::rsl)
else()
    # Test consumption via in-tree build
    target_link_libraries(test-rsl-install PRIVATE rsl::rsl)
endif()
