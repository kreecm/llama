#ifndef LLAMA_STATIC_MATH_H
#define LLAMA_STATIC_MATH_H

#include <type_traits>

namespace llama {

template <typename T>
inline constexpr typename std::enable_if<std::is_integral<T>::value, bool>::type
IsPowerOfTwo(T n) {
  return (n < 0)
             ? IsPowerOfTwo(-n)
             : (n < 3 ? true : ((n % 2) == 1 ? false : IsPowerOfTwo(n >> 1)));
}

}  // namespace llama

#endif  // LLAMA_STATIC_MATH_H
