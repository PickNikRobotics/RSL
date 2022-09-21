#pragma once

#include <tl_expected/expected.hpp>

#include <optional>

namespace rsl {

/**
 * @brief      Monad optional bind
 *
 * @param[in]  opt   The input optional
 * @param[in]  f     The function
 *
 * @tparam     T     The input type
 * @tparam     F     The function
 *
 * @return     Return type of f
 */
template <typename T, typename F>
[[nodiscard]] constexpr auto mbind(std::optional<T> const& opt, F f) -> std::invoke_result_t<F, T> {
    if (opt) return f(opt.value());
    return {};
}

/**
 * @brief      Monad tl::expected<T,E>
 *
 * @param[in]  exp   The tl::expected<T,E> input
 * @param[in]  f     The function to apply
 *
 * @tparam     T     The type for the input expected
 * @tparam     E     The error type
 * @tparam     F     The function
 *
 * @return     The return type of the function
 */
template <typename T, typename E, typename F>
[[nodiscard]] constexpr auto mbind(tl::expected<T, E> const& exp, F f)
    -> std::invoke_result_t<F, T> {
    if (exp) return f(exp.value());
    return tl::make_unexpected(exp.error());
}

/**
 * @brief      Monadic try, used to lift a function that throws an
 * exception one that returns an tl::expected<T, std::exception_ptr>
 *
 * @param[in]  f     The function to call
 *
 * @tparam     F     The function type
 *
 * @return     The return value of the function
 */
template <typename F>
[[nodiscard]] auto mtry(F f) -> tl::expected<std::invoke_result_t<F>, std::exception_ptr> try {
    return f();
} catch (...) {
    return tl::make_unexpected(std::current_exception());
}

/**
 * @brief      Monadic compose two monad functions
 *
 * @param[in]  f     The first function
 * @param[in]  g     The second function
 *
 * @tparam     F     The type of the first function
 * @tparam     G     The type of the second function
 *
 * @return     A functional composition of two monad functions
 */
template <typename F, typename G>
[[nodiscard]] constexpr auto mcompose(F f, G g) {
    return [=](auto value) { return mbind(f(value), g); };
}

/**
 * @brief      Variadic mcompose
 *
 * @param[in]  t      The first function
 * @param[in]  g      The second function
 * @param[in]  vars   The rest of the functions
 *
 * @tparam     T      The type of the first function
 * @tparam     G      The type of the second function
 * @tparam     Types  The types of the rest of the functions
 *
 * @return     A functional composition of variadic monad functions
 */
template <typename T, typename G, typename... Types>
[[nodiscard]] constexpr auto mcompose(T t, G g, Types... vars) {
    auto exp = mcompose(t, g);
    return mcompose(exp, vars...);
}

}  // namespace rsl

/**
 * @brief      Overload of the | operator as bind
 *
 * @param[in]  opt   The input optional
 * @param[in]  f     The function
 *
 * @tparam     T     The input type
 * @tparam     F     The function
 *
 * @return     Return type of f
 */
template <typename T, typename F>
[[nodiscard]] constexpr auto operator|(std::optional<T> const& opt, F f) {
    return rsl::mbind(opt, f);
}

/**
 * @brief      Overload of the | operator as bind
 *
 * @param[in]  exp   The input tl::expected<T,E> value
 * @param[in]  f     The function to apply
 *
 * @tparam     T     The type for the input expected
 * @tparam     E     The error type
 * @tparam     F     The function
 *
 * @return     Return type of f
 */
template <typename T, typename E, typename F>
[[nodiscard]] constexpr auto operator|(tl::expected<T, E> const& exp, F f)
    -> std::invoke_result_t<F, T> {
    return rsl::mbind(exp, f);
}
