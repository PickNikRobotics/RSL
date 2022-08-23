cmake_minimum_required(VERSION 3.22)
project(rsl LANGUAGES CXX)

find_package(ament_cmake REQUIRED)

add_library(rsl
  src/rand.cpp
)
target_compile_features(rsl PUBLIC cxx_std_17)
target_include_directories(rsl PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

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

ament_package()
