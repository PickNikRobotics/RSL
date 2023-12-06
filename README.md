# ROS Support Library (RSL)

![GitHub CI Workflow Status](https://img.shields.io/github/actions/workflow/status/picknikrobotics/RSL/.github/workflows/ci.yaml?branch=main&label=CI)
[![codecov](https://codecov.io/github/PickNikRobotics/RSL/branch/main/graph/badge.svg?token=t85cTyvsez)](https://codecov.io/github/PickNikRobotics/RSL)
![GitHub](https://img.shields.io/github/license/PickNikRobotics/RSL)

RSL is a collection of C++17 utilities for ROS projects.

Read the docs [here](https://picknikrobotics.github.io/RSL/files.html).

## Killer Features

* [algorithm](include/rsl/algorithm.hpp) - Functions for inspecting collections
* [monad.hpp](include/rsl/monad.hpp) - Functions and operators for monadic expressions
* [no_discard.hpp](include/rsl/no_discard.hpp) - `[[nodiscard]]` for lambdas
* [overload.hpp](include/rsl/overload.hpp) - Class template for easily visiting variants
* [parameter_validators.hpp](include/rsl/parameter_validators.hpp) - Functions for validating rclcpp::Parameter
* [queue.hpp](include/rsl/queue.hpp) - Thread-safe queue
* [random.hpp](include/rsl/random.hpp) - Modern C++ randomness made easy
* [static_string.hpp](include/rsl/static_string.hpp) - Static capacity string class
* [static_vector.hpp](include/rsl/static_vector.hpp) - Static capacity vector class
* [strong_type.hpp](include/rsl/strong_type.hpp) - Strong typedef class
* [try.hpp](include/rsl/try.hpp) - Macro to emulatate absl::CONFIRM or operator? from Rust

## v0 -> v1 API Breaks

No C++ API changes were made between version 0 and version 1, but a change to the build interface was made.
Because we stopped using ament CMake macros, you cannot use `ament_target_dependencies` to link to RSL.
You must instead use `target_link_libraries(... rsl::rsl)` as you would any other non-ament CMake library.
