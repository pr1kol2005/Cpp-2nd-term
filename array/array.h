#pragma once
#define ARRAY_TRAITS_IMPLEMENTED

#include <cstddef>

template<typename T, size_t N>
class Array {
 public:
  T buffer_[N];

 public:
  const T& operator[](size_t i) const {
    return buffer_[i];
  }
  T& operator[](size_t i) {
    return buffer_[i];
  }

  T& Front() {
    return buffer_[0];
  }
  const T& Front() const {
    return buffer_[0];
  }

  T& Back() {
    return buffer_[N - 1];
  }
  const T& Back() const {
    return buffer_[N - 1];
  }

  const T* Data() const {
    if (N == 0) {
      return nullptr;
    }
    return  &(buffer_[0]);
  }

  T* Data() {
    if (N == 0) {
      return nullptr;
    }
    return  &(buffer_[0]);
  }

  size_t Size() const {
    return N;
  }

  bool Empty() const {
    return N == 0;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      buffer_[i] = value;
    }
  }

  void Swap(Array<T, N>& other_array) {
    T tmp;
    for (size_t i = 0; i < N; ++i) {
      tmp = buffer_[i];
      buffer_[i] = other_array[i];
      other_array.buffer_[i] = tmp;
    }
  }
};

template <typename T, size_t N>
size_t  GetSize(const T (&)[N]) {
  return N;
}

template <typename T>
size_t  GetSize(T) {
  return 0;
}

template <typename T>
size_t GetRank(T) {
  return 0;
}

template <typename T, size_t N>
size_t GetRank(const T (&array)[N]) {
  size_t rank = 0;
  if (GetSize(array) == 0) {
    return rank;
  }
  rank = 1 + GetRank(array[0]);
  return rank;
}

template <typename T>
size_t GetNumElements(T) {
  return 1;
}

template <typename T, size_t N>
size_t GetNumElements(const T (&array)[N]) {
  size_t num_elem = 1;
  num_elem *= (GetSize(array) * GetNumElements(array[0]));
  return num_elem;
}