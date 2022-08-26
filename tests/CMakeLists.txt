include(FetchContent)

set(CATCH_INSTALL_DOCS OFF)
set(CATCH_INSTALL_EXTRAS OFF)
FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.1.0)
FetchContent_MakeAvailable(Catch2)
set_target_properties(Catch2 PROPERTIES COMPILE_OPTIONS "")
include(Catch)

add_executable(test-rand rand.cpp)
target_link_libraries(test-rand PRIVATE rsl::rsl Catch2::Catch2WithMain)
catch_discover_tests(test-rand)
