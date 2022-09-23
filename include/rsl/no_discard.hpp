#pragma once

#include <utility>

namespace rsl {

/**
 * @brief      Template for creating lambdas with the nodiscard attribute
 *
 * @tparam     Fn The lambda
 *
 * @example    no_discard.cpp
 */
template <typename Fn>
struct NoDiscard {
    static_assert(std::is_invocable_v<Fn()>, "Fn must be invocable");
    Fn fn_;
    NoDiscard(Fn const& fn) : fn_(fn) {}
    template <typename... Ts>
    [[nodiscard]] constexpr auto operator()(Ts&&... args) const
        noexcept(noexcept(fn_(std::forward<Ts>(args)...))) {
        return fn_(std::forward<Ts>(args)...);
    }
};

}  // namespace rsl
