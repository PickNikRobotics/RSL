^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package rsl
^^^^^^^^^^^^^^^^^^^^^^^^^

Forthcoming
-----------
* Remove devcontainer
* Fix new clang-tidy warnings
* Update Catch2
* Ensure FindEigen3.cmake is not used (`#126 <https://github.com/PickNikRobotics/RSL/issues/126>`_)
* Eigen: Add NO_MODULE to find_package (`#125 <https://github.com/PickNikRobotics/RSL/issues/125>`_)
  Work around RHEL 8 failure due to a faulty FindEigen3.cmake module being found
* Hide symbols from shared libraries by default and support DLL creation
* Fix static_string.cpp compilation with MSVC standard library
  std::array's iterator is a pointer in libc++ and libstdc++ so
  `const auto*` works fine. However the array iterator is not a
  pointer on MSVC so compilation fails. Removing the asterisk still
  results in a pointer type being used but causes a clang-tidy check
  to fail so we have to disable that.
* Disable TRY macro tests on MSVC
* Disable compiler warnings by default
  Unconditionally enabling -Werror is a heavy-handed approach and not
  ideal when shipping code to be used by many third parties. In fact
  it's even better to disable warnings by default since compiler
  warnings are not hard requirements. They're merely a development
  tool that developers should opt into.
* Contributors: Chris Thrasher, Christoph Fröhlich, Griswald Brooks, mosfet80

1.1.0 (2023-12-20)
------------------
* Fix `ament_target_dependencies` integration
* Add `rsl::maybe_error`
* Disable tests by default
* Stop using non-standard `M_PI`
* Contributors: Chris Thrasher

1.0.1 (2023-12-06)
------------------
* Add more messages for assertion failures
* Document API changes from v0 to v1
* Contributors: Chris Thrasher

1.0.0 (2023-12-04)
------------------
* Add `rsl::StrongType`
* Quote values in error messages
* Make doxygen a weak dependency
* Mark git as a test dependency
* Contributors: Andrew, Chris Thrasher, Michael Carroll, Tyler Weaver, andrea

0.2.2 (2023-03-23)
------------------
* Deprecate `rsl::lower_bounds` and `rsl::upper_bounds`
* Depend on ament_cmake_ros for SHARED default
* Upgrade with new pkgs to fix issue with ROS
* Update Catch2
* Contributors: Chris Thrasher, Tyler Weaver

0.2.1 (2022-11-29)
------------------
* Use constructors over factory functions when possible
* Implement `rsl::rng` with `std::optional`
* Fix bug when trying to seed rng from first call
* Make `rsl::rng()` tests more strenuous
  Seeding on the first call tests a code path that hadn't yet been
  tested but is a valid use of the API.
* Change version of range-v3 to allow building on Ubuntu Focal (`#73 <https://github.com/PickNikRobotics/RSL/issues/73>`_)
* Add missing header
  Fixes a build issue when using GCC 12
* Make it easy for users to override
* Update Catch2
* Add tests for `rsl::to_parameter_result_msg`
* Contributors: Chris Thrasher, Tony Najjar, Tyler Weaver

0.2.0 (2022-11-15)
------------------
* New features
  * rclcpp::Parameter validator functions
  * Algorithms from parameter_traits
  * `rsl::StaticVector` and `rsl::StaticString`
* Doxygen site: https://picknikrobotics.github.io/RSL/files.html
  * Link to the docs from the README
  * Use doxygen-awesome documentation style
  * Deploy documentation website from CI
  * Add Doxygen comments for `rsl::Overload`
  * Add Doxygen comments for `TRY`
* Cleanups
  * Prevent unnecessary string copy
  * Ensure global constants do not violate the ODR
  * Hide `rsl::NoDiscard` implementation details
  * Use more `[[nodiscard]]`
  * Fix to_vector for vector<bool>
  * Ensure static container iterators are used
  * Default to building a shared library
  * Use generator-agnostic CMake commands
  * Remove C compiler settings
  * Don't require compiler extensions
  * Use more expressive path variable
  * Add clang-tidy integration and fix errors
  * Address clang-tidy findings
  * Update FindCatch2 module
  * Update Catch2
* Contributors: Chris Thrasher, Tyler Weaver

0.1.1 (2022-10-04)
------------------
* Fix CMake configuration warnings
* Contributors: Chris Thrasher

0.1.0 (2022-10-04)
------------------
* monad.hpp - Functions and operators for monadic expressions
* no_discard.hpp - `[[nodiscard]]` for lambdas
* overload.hpp - Class template for easily visiting variants
* queue.hpp - Thread-safe queue
* random.hpp - Modern C++ randomness made easy
* try.hpp - Macro to emulatate absl::CONFIRM or operator? from Rust
* Contributors: Chris Thrasher, Tyler Weaver
