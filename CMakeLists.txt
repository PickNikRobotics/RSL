cmake_minimum_required(VERSION 3.22)
project(thread_rand LANGUAGES CXX)

find_package(ament_cmake REQUIRED)

add_library(thread_rand
  src/thread_rand.cpp
)
target_compile_features(thread_rand PUBLIC cxx_std_17)
target_include_directories(thread_rand PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(
  DIRECTORY include/
  DESTINATION include
)
install(
  TARGETS thread_rand
  EXPORT export_thread_rand
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

ament_export_include_directories(include)
ament_export_libraries(thread_rand)
ament_export_targets(export_thread_rand)

ament_package()
