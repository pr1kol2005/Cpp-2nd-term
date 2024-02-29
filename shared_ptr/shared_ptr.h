#pragma once

#include <stdexcept>

class BadWeakPtr : public std::runtime_error {
 public:
  BadWeakPtr() : std::runtime_error("BadWeakPtr") {
  }
};

template <class T>
class SharedPtr {
  struct StrongCounter {
    size_t counter = 0;
  };

  T* ptr_;
  StrongCounter* strong_counter_;

 public:
  SharedPtr() : ptr_(nullptr), strong_counter_(nullptr) {
  }

  SharedPtr(std::nullptr_t) : ptr_(nullptr), strong_counter_(nullptr) {  // NOLINT
  }

  explicit SharedPtr(T* pointer) : ptr_(pointer), strong_counter_(new StrongCounter{1}) {
  }

  SharedPtr(const SharedPtr& other) {
    ptr_ = other.ptr_;
    strong_counter_ = other.strong_counter_;
    if (strong_counter_) {
      strong_counter_->counter++;
    }
  }

  SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {
      Reset();
      ptr_ = other.ptr_;
      strong_counter_ = other.strong_counter_;
      if (strong_counter_) {
        strong_counter_->counter++;
      }
    }
    return *this;
  }

  SharedPtr(SharedPtr&& other) noexcept : ptr_(nullptr), strong_counter_(nullptr) {
    Swap(other);
  }

  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
      Reset();
      Swap(other);
    }
    return *this;
  }

  ~SharedPtr() {
    Reset();
  }

  void Reset(T* pointer = nullptr) {
    if (strong_counter_) {
      strong_counter_->counter--;
      if (strong_counter_->counter == 0) {
        delete ptr_;
        delete strong_counter_;
      }
    }
    ptr_ = pointer;
    strong_counter_ = pointer ? new StrongCounter{1} : nullptr;
  }

  void Swap(SharedPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(strong_counter_, other.strong_counter_);
  }

  T* Get() const {
    return ptr_;
  }

  size_t UseCount() const {
    return strong_counter_ ? strong_counter_->counter : 0;
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
