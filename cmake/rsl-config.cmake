include(CMakeFindDependencyMacro)

find_dependency(Eigen3 CONFIG)
find_dependency(fmt)
find_dependency(rclcpp)
find_dependency(rcpputils)
find_dependency(tcb_span)

include(${CMAKE_CURRENT_LIST_DIR}/rsl-targets.cmake)

# Support ament_target_dependencies
set(rsl_TARGETS rsl::rsl)
