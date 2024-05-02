#define VECTOR_MEMORY_IMPLEMENTED
#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

template <class T>
class Vector;

template <class T>
bool operator==(const Vector<T>& left, const Vector<T>& right) noexcept;
template <class T>
bool operator!=(const Vector<T>& left, const Vector<T>& right) noexcept;
template <class T>
bool operator<(const Vector<T>& left, const Vector<T>& right) noexcept;
template <class T>
bool operator<=(const Vector<T>& left, const Vector<T>& right) noexcept;
template <class T>
bool operator>(const Vector<T>& left, const Vector<T>& right) noexcept;
template <class T>
bool operator>=(const Vector<T>& left, const Vector<T>& right) noexcept;

template <class T>
class Vector {
  std::byte* buffer_;
  size_t size_;
  size_t capacity_;

 public:
  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<T*>;
  using ConstReverseIterator = std::reverse_iterator<const T*>;
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;

  Vector() noexcept;
  explicit Vector(size_t n);
  Vector(size_t n, ConstReference value);
  Vector(std::initializer_list<T> it_list);

  template <class ForwardIterator,
            class = std::enable_if_t<std::is_base_of_v<
                std::forward_iterator_tag, typename std::iterator_traits<ForwardIterator>::iterator_category>>>
  Vector(ForwardIterator first, ForwardIterator last);

  Vector(const Vector<T>& other);
  Vector(Vector<T>&& other) noexcept;
  Vector& operator=(const Vector<T>& other);
  Vector& operator=(Vector<T>&& other) noexcept;
  ~Vector() noexcept;

  SizeType Size() const noexcept;
  SizeType Capacity() const noexcept;
  bool Empty() const noexcept;

  ConstReference operator[](size_t i) const noexcept;
  Reference operator[](size_t i) noexcept;
  ConstReference At(size_t i) const;
  Reference At(size_t i);

  ConstReference Front() const noexcept;
  Reference Front() noexcept;
  ConstReference Back() const noexcept;
  Reference Back() noexcept;
  ConstPointer Data() const noexcept;
  Pointer Data() noexcept;

  void Swap(Vector<T>& other) noexcept;
  void Resize(const size_t& new_size);
  void Resize(const size_t& new_size, ConstReference value);
  void Reserve(size_t new_cap);
  void ShrinkToFit();
  void Clear() noexcept;
  void PushBack(ConstReference value);
  void PushBack(T&& value);
  void PopBack() noexcept;

  template <class... Args>
  void EmplaceBack(Args&&... args) {
    PushBack(T(std::forward<Args>(args)...));
  }

  friend bool operator== <T>(const Vector<T>& left, const Vector<T>& right) noexcept;
  friend bool operator!= <T>(const Vector<T>& left, const Vector<T>& right) noexcept;
  friend bool operator< <T>(const Vector<T>& left, const Vector<T>& right) noexcept;
  friend bool operator<= <T>(const Vector<T>& left, const Vector<T>& right) noexcept;
  friend bool operator><T>(const Vector<T>& left, const Vector<T>& right) noexcept;
  friend bool operator>= <T>(const Vector<T>& left, const Vector<T>& right) noexcept;

  Iterator begin() noexcept;                      // NOLINT
  ConstIterator begin() const noexcept;           // NOLINT
  ConstIterator cbegin() const noexcept;          // NOLINT
  Iterator end() noexcept;                        // NOLINT
  ConstIterator end() const noexcept;             // NOLINT
  ConstIterator cend() const noexcept;            // NOLINT
  ReverseIterator rbegin() noexcept;              // NOLINT
  ConstReverseIterator rbegin() const noexcept;   // NOLINT
  ConstReverseIterator crbegin() const noexcept;  // NOLINT
  ReverseIterator rend() noexcept;                // NOLINT
  ConstReverseIterator rend() const noexcept;     // NOLINT
  ConstReverseIterator crend() const noexcept;    // NOLINT
};

template <class T>
Vector<T>::Vector() noexcept : buffer_(nullptr), size_(0ul), capacity_(0ul) {
}

template <class T>
Vector<T>::Vector(size_t n) : buffer_(nullptr), size_(n), capacity_(n) {
  try {
    buffer_ = new std::byte[size_ * sizeof(T)];
    std::uninitialized_default_construct(begin(), end());
  } catch (...) {
    delete[] buffer_;
    throw;
  }
}

template <class T>
Vector<T>::Vector(size_t n, ConstReference value) : buffer_(nullptr), size_(n), capacity_(n) {
  if (!n) {
    buffer_ = nullptr;
    return;
  }
  try {
    buffer_ = new std::byte[size_ * sizeof(T)];
    std::uninitialized_fill(begin(), end(), value);
  } catch (...) {
    delete[] buffer_;
    throw;
  }
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> it_list) : buffer_(nullptr), size_(it_list.size()), capacity_(size_) {
  try {
    buffer_ = new std::byte[size_ * sizeof(T)];
    std::uninitialized_copy(it_list.begin(), it_list.end(), begin());
  } catch (...) {
    delete[] buffer_;
    throw;
  }
}

template <class T>
template <class ForwardIterator, class>
Vector<T>::Vector(ForwardIterator first, ForwardIterator last)
    : buffer_(nullptr), size_(static_cast<size_t>(std::distance(first, last))), capacity_(size_) {
  if (!size_) {
    buffer_ = nullptr;
    return;
  }
  try {
    buffer_ = new std::byte[size_ * sizeof(T)];
    std::uninitialized_copy(first, last, begin());
  } catch (...) {
    delete[] buffer_;
    throw;
  }
}

template <class T>
Vector<T>::Vector(const Vector<T>& other) : buffer_(nullptr), size_(other.size_), capacity_(other.capacity_) {
  if (!size_) {
    buffer_ = nullptr;
    return;
  }
  try {
    buffer_ = new std::byte[capacity_ * sizeof(T)];
    std::uninitialized_copy(other.begin(), other.end(), begin());
  } catch (...) {
    delete[] buffer_;
    throw;
  }
}

template <class T>
Vector<T>::Vector(Vector<T>&& other) noexcept {
  if (!other.buffer_) {
    buffer_ = nullptr;
    size_ = other.size_;
    capacity_ = other.capacity_;
    return;
  }
  buffer_ = other.buffer_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.buffer_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
  if (!other.buffer_) {
    std::destroy(begin(), end());
    delete[] buffer_;
    buffer_ = nullptr;
    size_ = other.size_;
    capacity_ = other.capacity_;
    return *this;
  }
  std::byte* memory = nullptr;
  try {
    memory = new std::byte[other.size_ * sizeof(T)];
    auto new_begin = reinterpret_cast<T*>(memory);
    std::uninitialized_copy(other.begin(), other.end(), new_begin);
    std::destroy(begin(), end());
    delete[] buffer_;
    buffer_ = memory;
    size_ = other.size_;
    capacity_ = other.capacity_;
  } catch (...) {
    delete[] memory;
    throw;
  }
  return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept {
  std::destroy(begin(), end());
  delete[] buffer_;
  buffer_ = other.buffer_;
  other.buffer_ = nullptr;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.size_ = 0;
  other.capacity_ = 0;
  return *this;
}

template <class T>
Vector<T>::~Vector() noexcept {
  Clear();
  delete[] buffer_;
  capacity_ = 0;
}

template <class T>
Vector<T>::Iterator Vector<T>::begin() noexcept {
  return reinterpret_cast<T*>(buffer_);
}

template <class T>
Vector<T>::ReverseIterator Vector<T>::rbegin() noexcept {
  return ReverseIterator(reinterpret_cast<T*>(buffer_) + size_);
}

template <class T>
size_t Vector<T>::Size() const noexcept {
  return size_;
}

template <class T>
size_t Vector<T>::Capacity() const noexcept {
  return capacity_;
}

template <class T>
bool Vector<T>::Empty() const noexcept {
  return !size_;
}

template <class T>
T& Vector<T>::operator[](size_t i) noexcept {
  return *(begin() + i);
}

template <class T>
const T& Vector<T>::operator[](size_t i) const noexcept {
  return *(cbegin() + i);
}

template <class T>
T& Vector<T>::At(size_t i) {
  if (i >= size_) {
    throw std::out_of_range("Out of range");
  }
  return *(begin() + i);
}

template <class T>
const T& Vector<T>::At(size_t i) const {
  if (i >= size_) {
    throw std::out_of_range("Out of range");
  }
  return *(cbegin() + i);
}

template <class T>
const T& Vector<T>::Front() const noexcept {
  return *cbegin();
}

template <class T>
T& Vector<T>::Front() noexcept {
  return *begin();
}

template <class T>
const T& Vector<T>::Back() const noexcept {
  return *(cbegin() + size_ - 1);
}

template <class T>
T& Vector<T>::Back() noexcept {
  return *(begin() + size_ - 1);
}

template <class T>
const T* Vector<T>::Data() const noexcept {
  return cbegin();
}

template <class T>
T* Vector<T>::Data() noexcept {
  return begin();
}

template <class T>
void Vector<T>::Swap(Vector<T>& other) noexcept {
  std::swap(other.buffer_, buffer_);
  std::swap(other.capacity_, capacity_);
  std::swap(other.size_, size_);
}

template <class T>
void Vector<T>::Resize(const size_t& new_size) {
  if (new_size > size_) {
    if (new_size <= capacity_) {
      std::uninitialized_default_construct(begin() + size_, begin() + new_size);
      size_ = new_size;
    } else {
      std::byte* memory = nullptr;
      try {
        memory = new std::byte[new_size * sizeof(T)];
        auto new_begin = reinterpret_cast<T*>(memory);
        std::uninitialized_default_construct(new_begin + size_, new_begin + new_size);
        std::uninitialized_move(begin(), end(), new_begin);
        std::destroy(begin(), end());
        delete[] buffer_;
        buffer_ = memory;
        capacity_ = new_size;
        size_ = new_size;
      } catch (...) {
        delete[] memory;
        throw;
      }
    }
  } else {
    std::destroy(begin() + new_size, begin() + size_);
    size_ = new_size;
  }
}

template <class T>
void Vector<T>::Resize(const size_t& new_size, const T& value) {
  if (new_size > size_) {
    if (new_size <= capacity_) {
      std::uninitialized_fill(begin() + size_, begin() + new_size, value);
      size_ = new_size;
    } else {
      std::byte* memory = nullptr;
      try {
        memory = new std::byte[new_size * sizeof(T)];
        auto new_begin = reinterpret_cast<T*>(memory);
        std::uninitialized_fill(new_begin + size_, new_begin + new_size, value);
        std::uninitialized_move(begin(), end(), new_begin);
        std::destroy(begin(), end());
        delete[] buffer_;
        buffer_ = memory;
        capacity_ = new_size;
        size_ = new_size;
      } catch (...) {
        delete[] memory;
        throw;
      }
    }
  } else {
    std::destroy(begin() + new_size, begin() + size_);
    size_ = new_size;
  }
}

template <class T>
void Vector<T>::Reserve(size_t new_cap) {
  std::byte* memory = nullptr;
  try {
    if (new_cap > capacity_) {
      memory = new std::byte[new_cap * sizeof(T)];
      auto new_begin = reinterpret_cast<T*>(memory);
      std::uninitialized_move(begin(), end(), new_begin);
      std::destroy(begin(), end());
      delete[] buffer_;
      buffer_ = memory;
      capacity_ = new_cap;
    }
  } catch (...) {
    delete[] memory;
    throw;
  }
}
template <class T>
void Vector<T>::ShrinkToFit() {
  if (!size_) {
    delete[] buffer_;
    capacity_ = 0;
    buffer_ = nullptr;
    return;
  }
  std::byte* memory = nullptr;
  try {
    memory = new std::byte[size_ * sizeof(T)];
    auto new_begin = reinterpret_cast<T*>(memory);
    std::uninitialized_move(begin(), end(), new_begin);
    std::destroy(begin(), end());
    delete[] buffer_;
    buffer_ = memory;
    capacity_ = size_;
  } catch (...) {
    delete[] memory;
    throw;
  }
}

template <class T>
void Vector<T>::Clear() noexcept {
  if (buffer_) {
    for (auto it = begin(); it != end(); ++it) {
      it->~T();
    }
    size_ = 0;
  }
}

template <class T>
void Vector<T>::PushBack(const T& value) {
  if (!capacity_) {
    try {
      buffer_ = new std::byte[sizeof(T)];
      new (buffer_) T(value);
      ++size_;
      ++capacity_;
    } catch (...) {
      delete[] buffer_;
      buffer_ = nullptr;
      throw;
    }
    return;
  }
  if (size_ == capacity_) {
    auto temp = buffer_;
    try {
      buffer_ = new std::byte[2 * capacity_ * sizeof(T)];
      auto new_begin = reinterpret_cast<T*>(temp);
      new (begin() + Size()) T(value);
      std::uninitialized_move(new_begin, new_begin + size_, begin());
      std::destroy(new_begin, new_begin + size_);
      ++size_;
      capacity_ *= 2;
      delete[] temp;
    } catch (...) {
      delete[] buffer_;
      buffer_ = temp;
      throw;
    }
  } else {
    new (begin() + Size()) T(value);
    ++size_;
  }
}

template <class T>
void Vector<T>::PushBack(T&& value) {
  if (!capacity_) {
    try {
      buffer_ = new std::byte[sizeof(T)];
      new (buffer_) T(std::move(value));
      ++size_;
      ++capacity_;
    } catch (...) {
      delete[] buffer_;
      buffer_ = nullptr;
      throw;
    }
    return;
  }
  if (size_ == capacity_) {
    auto temp = buffer_;
    try {
      buffer_ = new std::byte[2 * capacity_ * sizeof(T)];
      auto new_begin = reinterpret_cast<T*>(temp);
      new (begin() + Size()) T(std::move(value));
      std::uninitialized_move(new_begin, new_begin + size_, begin());
      std::destroy(new_begin, new_begin + size_);
      ++size_;
      capacity_ *= 2;
      delete[] temp;
    } catch (...) {
      delete[] buffer_;
      buffer_ = temp;
      throw;
    }
  } else {
    new (begin() + size_) T(std::move(value));
    ++size_;
  }
}

template <class T>
void Vector<T>::PopBack() noexcept {
  (begin() + size_ - 1)->~T();
  --size_;
}

template <class T>
bool operator==(const Vector<T>& left, const Vector<T>& right) noexcept {
  if (left.size_ != right.size_) {
    return false;
  }
  for (size_t i = 0; i < left.size_; i++) {
    if (*(left.begin() + i) != *(right.begin() + i)) {
      return false;
    }
  }
  return true;
}

template <class T>
bool operator!=(const Vector<T>& left, const Vector<T>& right) noexcept {
  return !(left == right);
}

template <class T>
bool operator<(const Vector<T>& left, const Vector<T>& right) noexcept {
  for (size_t i = 0; i < std::min(left.Size(), right.Size()); i++) {
    if (*(left.begin() + i) == *(right.begin() + i)) {
      continue;
    }
    return (*(left.begin() + i) < *(right.begin() + i));
  }
  return left.Size() < right.Size();
}

template <class T>
bool operator<=(const Vector<T>& left, const Vector<T>& right) noexcept {
  return (left < right) || (left == right);
}

template <class T>
bool operator>(const Vector<T>& left, const Vector<T>& right) noexcept {
  return !(left < right) && left != right;
}

template <class T>
bool operator>=(const Vector<T>& left, const Vector<T>& right) noexcept {
  return !(left < right);
}

template <class T>
Vector<T>::ConstIterator Vector<T>::begin() const noexcept {
  return reinterpret_cast<const T*>(buffer_);
}

template <class T>
Vector<T>::ConstIterator Vector<T>::cbegin() const noexcept {
  return reinterpret_cast<const T*>(buffer_);
}

template <class T>
Vector<T>::ConstIterator Vector<T>::cend() const noexcept {
  return (reinterpret_cast<const T*>(buffer_) + size_);
}

template <class T>
Vector<T>::Iterator Vector<T>::end() noexcept {
  return (reinterpret_cast<T*>(buffer_) + size_);
}

template <class T>
Vector<T>::ConstIterator Vector<T>::end() const noexcept {
  return (reinterpret_cast<const T*>(buffer_) + size_);
}

template <class T>
Vector<T>::ConstReverseIterator Vector<T>::rbegin() const noexcept {
  return ConstReverseIterator(reinterpret_cast<const T*>(buffer_) + size_);
}

template <class T>
Vector<T>::ConstReverseIterator Vector<T>::crbegin() const noexcept {
  return ConstReverseIterator(reinterpret_cast<const T*>(buffer_) + size_);
}

template <class T>
Vector<T>::ReverseIterator Vector<T>::rend() noexcept {
  return ReverseIterator(reinterpret_cast<T*>(buffer_));
}

template <class T>
Vector<T>::ConstReverseIterator Vector<T>::rend() const noexcept {
  return ConstReverseIterator(reinterpret_cast<T*>(buffer_));
}

template <class T>
Vector<T>::ConstReverseIterator Vector<T>::crend() const noexcept {
  return ConstReverseIterator(reinterpret_cast<const T*>(buffer_));
}