#pragma once

#include <utility>

template <class T>
class UniquePtr {
 private:
  T* ptr_ = nullptr;

 public:
  UniquePtr() = default;
  explicit UniquePtr(T* pointer) : ptr_(pointer){};  // maybe noexcept
  UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }
  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;

  ~UniquePtr() {
    delete ptr_;
  }

  T* Release() noexcept {
    auto out = ptr_;
    ptr_ = nullptr;
    return out;
  }

  void Reset(T* pointer = nullptr) noexcept {
    delete ptr_;
    ptr_ = pointer;
  }

  void Swap(UniquePtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
  }

  T* Get() const noexcept {
    return ptr_;
  }

  T& operator*() const noexcept {
    return *ptr_;
  }

  T* operator->() const noexcept {
    return ptr_;
  }

  explicit operator bool() const noexcept {
    return ptr_;  // static_cast<bool>(ptr_) or ptr != nullptr
  }
};