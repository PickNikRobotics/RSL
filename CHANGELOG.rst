^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package rsl
^^^^^^^^^^^^^^^^^^^^^^^^^

Forthcoming
-----------
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
