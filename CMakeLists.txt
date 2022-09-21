cmake_minimum_required(VERSION 3.22)
project(rsl VERSION 0.0.0 LANGUAGES CXX)

find_package(ament_cmake REQUIRED)
find_package(tl_expected REQUIRED)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)
endif()

add_library(rsl
    src/rand.cpp
)
add_library(rsl::rsl ALIAS rsl)
target_compile_features(rsl PUBLIC cxx_std_17)
target_include_directories(rsl PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(rsl PUBLIC tl_expected::tl_expected)

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
)

ament_export_include_directories(include)
ament_export_libraries(rsl)
ament_export_targets(export_rsl)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

ament_package()
