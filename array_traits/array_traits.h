#pragma once

#include <type_traits>

template <typename T>
struct IsArray : std::false_type {};

template <typename T>
struct IsArray<T[]> : std::true_type {};

template <typename T, std::size_t N>
struct IsArray<T[N]> : std::true_type {};

template <class T>
constexpr bool kIsArrayV = IsArray<T>::value;

//////////////////////////////////////////////

template <typename T>
struct Rank : std::integral_constant<std::size_t, 0> {};

template <typename T>
struct Rank<T[]> : std::integral_constant<std::size_t, Rank<T>::value + 1> {};

template <typename T, std::size_t N>
struct Rank<T[N]> : std::integral_constant<std::size_t, Rank<T>::value + 1> {};

template <class T>
constexpr std::size_t kRankV = Rank<T>::value;

//////////////////////////////////////////////

template <typename T>
struct Size : std::integral_constant<std::size_t, 1> {};

template <typename T>
struct Size<T[]> : std::integral_constant<std::size_t, 0> {};

template <typename T, std::size_t N>
struct Size<T[N]> : std::integral_constant<std::size_t, N> {};

template <class T>
constexpr std::size_t kSizeV = Size<T>::value;

//////////////////////////////////////////////

template <typename T>
struct TotalSize : std::integral_constant<std::size_t, 1> {};

template <typename T>
struct TotalSize<T[]> : std::integral_constant<std::size_t, 0> {};

template <typename T, std::size_t N>
struct TotalSize<T[N]> : std::integral_constant<std::size_t, TotalSize<T>::value * N> {};

template <class T>
constexpr std::size_t kTotalSizeV = TotalSize<T>::value;

//////////////////////////////////////////////

template <typename T>
struct RemoveArray {
  using Type = T;
};

template <typename T>
struct RemoveArray<T[]> {
  using Type = T;
};

template <typename T, std::size_t N>
struct RemoveArray<T[N]> {
  using Type = T;
};

template <typename T>
using RemoveArrayT = typename RemoveArray<T>::Type;

//////////////////////////////////////////////

template <typename T>
struct RemoveAllArrays {
  using Type = T;
};

template <typename T>
struct RemoveAllArrays<T[]> {
  using Type = typename RemoveAllArrays<T>::Type;
};

template <typename T, std::size_t N>
struct RemoveAllArrays<T[N]> {
  using Type = typename RemoveAllArrays<T>::Type;
};

template <typename T>
using RemoveAllArraysT = typename RemoveAllArrays<T>::Type;