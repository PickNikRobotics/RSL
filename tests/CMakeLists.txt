list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Catch2 3.3.2 REQUIRED)
find_package(range-v3 REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(test-rsl
    main.cpp
    algorithm.cpp
    monad.cpp
    no_discard.cpp
    observer.cpp
    overload.cpp
    parameter_validators.cpp
    queue.cpp
    random.cpp
    static_string.cpp
    static_vector.cpp
    try.cpp)
target_link_libraries(test-rsl
    rsl::rsl
    Catch2::Catch2
    range-v3::range-v3
)
ament_target_dependencies(test-rsl std_msgs)
catch_discover_tests(test-rsl)
