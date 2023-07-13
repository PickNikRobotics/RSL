list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Catch2 3.4.0 REQUIRED)
find_package(range-v3 REQUIRED)

add_executable(test-rsl
    algorithm.cpp
    monad.cpp
    no_discard.cpp
    overload.cpp
    parameter_validators.cpp
    queue.cpp
    random.cpp
    static_string.cpp
    static_vector.cpp
    try.cpp)
target_link_libraries(test-rsl PRIVATE
    rsl::rsl
    Catch2::Catch2WithMain
    range-v3::range-v3
)
catch_discover_tests(test-rsl)
