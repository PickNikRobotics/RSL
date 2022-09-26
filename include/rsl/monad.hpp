#pragma once

#include <tl_expected/expected.hpp>

#include <optional>

namespace rsl {

/**
 * @brief      Monad optional bind
 *
 * @param[in]  opt   The input optional
 * @param[in]  fn    The function
 *
 * @tparam     T     The input type
 * @tparam     Fn    The function
 *
 * @return     Return type of fn
 */
template <typename T, typename Fn>
[[nodiscard]] constexpr auto mbind(std::optional<T> const& opt, Fn fn)
    -> std::invoke_result_t<Fn, T> {
    if (opt) return fn(opt.value());
    return {};
}

/**
 * @brief      Monad tl::expected<T,E>
 *
 * @param[in]  exp   The tl::expected<T,E> input
 * @param[in]  fn    The function to apply
 *
 * @tparam     T     The type for the input expected
 * @tparam     E     The error type
 * @tparam     Fn    The function
 *
 * @return     The return type of the function
 */
template <typename T, typename E, typename Fn>
[[nodiscard]] constexpr auto mbind(tl::expected<T, E> const& exp, Fn fn)
    -> std::invoke_result_t<Fn, T> {
    if (exp) return fn(exp.value());
    return tl::make_unexpected(exp.error());
}

/**
 * @brief      Monadic try, used to lift a function that throws an
 * exception one that returns an tl::expected<T, std::exception_ptr>
 *
 * @param[in]  fn    The function to call
 *
 * @tparam     Fn    The function type
 *
 * @return     The return value of the function
 */
template <typename Fn>
[[nodiscard]] auto mtry(Fn fn) -> tl::expected<std::invoke_result_t<Fn>, std::exception_ptr> try {
    return fn();
} catch (...) {
    return tl::make_unexpected(std::current_exception());
}

/**
 * @brief      Monadic compose two monad functions
 *
 * @param[in]  fn    The first function
 * @param[in]  g     The second function
 *
 * @tparam     Fn    The type of the first function
 * @tparam     G     The type of the second function
 *
 * @return     A functional composition of two monad functions
 */
template <typename Fn, typename G>
[[nodiscard]] constexpr auto mcompose(Fn fn, G g) {
    return [=](auto value) { return mbind(fn(value), g); };
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

/**
 * @brief           Test if expected type is Error
 *
 * @param[in] exp   The input tl::expected<T,E> value
 *
 * @return          True if expected paraemter is Error
 */
template <typename T, typename E>
[[nodiscard]] constexpr auto has_error(tl::expected<T, E> const& exp) {
    return !exp.has_value();
}

/**
 * @brief           Test if expected type is Value
 *
 * @param[in] exp   The input tl::expected<T,E> value
 *
 * @return          True if expected paraemter is Value
 */
template <typename T, typename E>
[[nodiscard]] constexpr auto has_value(tl::expected<T, E> const& exp) {
    return exp.has_value();
}

}  // namespace rsl

/**
 * @brief      Overload of the | operator as bind
 *
 * @param[in]  opt   The input optional
 * @param[in]  f     The function
 *
 * @tparam     T     The input type
 * @tparam     Fn     The function
 *
 * @return     Return type of f
 */
template <typename T, typename Fn>
[[nodiscard]] constexpr auto operator|(std::optional<T> const& opt, Fn fn) {
    return rsl::mbind(opt, fn);
}

/**
 * @brief      Overload of the | operator as bind
 *
 * @param[in]  exp   The input tl::expected<T,E> value
 * @param[in]  fn    The function to apply
 *
 * @tparam     T     The type for the input expected
 * @tparam     E     The error type
 * @tparam     Fn    The function
 *
 * @return     Return type of fn
 */
template <typename T, typename E, typename Fn>
[[nodiscard]] constexpr auto operator|(tl::expected<T, E> const& exp, Fn fn)
    -> std::invoke_result_t<Fn, T> {
    return rsl::mbind(exp, fn);
}
