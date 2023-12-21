cmake_minimum_required(VERSION 3.22)
project(rsl-install-test)

if(PROJECT_IS_TOP_LEVEL)
    find_package(rsl 1.1.0 EXACT REQUIRED)
endif()

add_executable(test-rsl-install install.cpp)
target_link_libraries(test-rsl-install PRIVATE rsl::rsl)
