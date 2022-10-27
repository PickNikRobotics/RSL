#pragma once

#include <algorithm>

namespace rsl {

/** @file */

/**
 * @brief Determine if a collection contains a value. Example usage:
 *
 * @code
 * auto values = std::vector{1, 2, 3};
 * rsl::contains(values, 3); // true
 * rsl::contains(values, -1); // false
 * @endcode
 */
template <typename Collection>
[[nodiscard]] auto contains(Collection const& collection,
                            typename Collection::const_reference value) {
    return std::find(std::cbegin(collection), std::cend(collection), value) !=
           std::cend(collection);
}

/**
 * @brief Determine if all elements in a collection are unique. Example usage:
 *
 * @code
 * rsl::is_unique(std::vector{2,2}); // false
 * rsl::is_unique(std::vector{1,2,3}); // true
 * @endcode
 *
 * Because of how this function is implemented, the collection parameter is
 * taken by value, creating a copy. The implication of this is that it will not work
 * on collections of non-copy-able objects.
 */
template <typename Collection>
[[nodiscard]] auto is_unique(Collection collection) {
    std::sort(std::begin(collection), std::end(collection));
    return std::adjacent_find(std::cbegin(collection), std::cend(collection)) ==
           std::cend(collection);
}

}  // namespace rsl
