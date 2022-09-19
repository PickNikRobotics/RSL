list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Catch2 3.1.0 REQUIRED)

add_executable(test-rsl overload.cpp rand.cpp)
target_link_libraries(test-rsl PRIVATE rsl::rsl Catch2::Catch2WithMain)
catch_discover_tests(test-rsl)
