#pragma once

namespace rsl {

template <typename... Ts>
struct Overload : Ts... {
    using Ts::operator()...;
};

template <class... Ts>
Overload(Ts...) -> Overload<Ts...>;

}  // namespace rsl
