# ROS Support Library (RSL)

![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/PickNikRobotics/RSL/CI/main?label=CI)
[![codecov](https://codecov.io/github/PickNikRobotics/RSL/branch/main/graph/badge.svg?token=t85cTyvsez)](https://codecov.io/github/PickNikRobotics/RSL)
![GitHub](https://img.shields.io/github/license/PickNikRobotics/RSL)

RSL is a collection of C++17 utilities for ROS projects.

Read the docs [here](https://picknikrobotics.github.io/RSL/files.html).

## Killer Features

* [monad.hpp](include/rsl/monad.hpp) - Functions and operators for monadic expressions
* [no_discard.hpp](include/rsl/no_discard.hpp) - `[[nodiscard]]` for lambdas
* [overload.hpp](include/rsl/overload.hpp) - Class template for easily visiting variants
* [queue.hpp](include/rsl/queue.hpp) - Thread-safe queue
* [random.hpp](include/rsl/random.hpp) - Modern C++ randomness made easy
* [try.hpp](include/rsl/try.hpp) - Macro to emulatate absl::CONFIRM or operator? from Rust
