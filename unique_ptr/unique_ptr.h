#pragma once

#include <utility>

template <class T>
class UniquePtr {
  T* ptr_;

 public:
  UniquePtr() : ptr_(nullptr){};

  explicit UniquePtr(T* pointer) : ptr_(pointer){};

  UniquePtr(const UniquePtr&) = delete;

  UniquePtr& operator=(const UniquePtr&) = delete;

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

  ~UniquePtr() {
    delete ptr_;
  }

  T* Release() {
    auto out = ptr_;
    ptr_ = nullptr;
    return out;
  }

  void Reset(T* pointer = nullptr) {
    delete ptr_;
    ptr_ = pointer;
  }

  void Swap(UniquePtr& other) {
    std::swap(ptr_, other.ptr_);
  }

  T* Get() const {
    return ptr_;
  }

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  explicit operator bool() const {
    return static_cast<bool>(ptr_);
  }
};
