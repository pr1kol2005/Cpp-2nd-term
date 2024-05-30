#pragma once

#include <type_traits>
#include <cstdint>

template <int64_t N, int64_t L, int64_t R, int64_t M = (L + R) / 2>
struct Sqrt : Sqrt<N, (M <= N / M) ? M + 1 : L, (M <= N / M) ? R : M> {};

template <int64_t N, int64_t L>
struct Sqrt<N, L, L, L> : std::integral_constant<int64_t, (L <= N / L) ? L : (L - 1)> {};

template <>
struct Sqrt<1, 0, 1, 0> : std::integral_constant<int64_t, 1> {};

template <>
struct Sqrt<0, 0, 0, 0> : std::integral_constant<int64_t, 0> {};

template <int64_t N>
inline const int64_t kSqrtV = Sqrt<N, 0, N>::value;

template <int64_t N, int64_t L, int64_t R, int64_t M = (L + R) / 2>
struct HasDivisorInRange
    : std::integral_constant<bool, (HasDivisorInRange<N, L, M>::value || HasDivisorInRange<N, M + 1, R>::value)> {};

template <int64_t N, int64_t L>
struct HasDivisorInRange<N, L, L> : std::integral_constant<bool, (N == 0 || N == 1 || L != 1) && (N % L == 0)> {};

template <int64_t N, int64_t L, int64_t R>
inline const bool kHasDivisorOnV = HasDivisorInRange<N, L, R>::value;

template <int64_t N>
struct IsPrime : std::integral_constant<bool, !kHasDivisorOnV<N, 2, kSqrtV<N>>> {};

template <>
struct IsPrime<1> : std::integral_constant<bool, false> {};

template <>
struct IsPrime<2> : std::integral_constant<bool, true> {};

template <>
struct IsPrime<3> : std::integral_constant<bool, true> {};

template <int64_t N>
inline const bool kIsPrimeV = IsPrime<N>::value;
