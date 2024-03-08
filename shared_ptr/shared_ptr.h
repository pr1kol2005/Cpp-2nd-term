#define WEAK_PTR_IMPLEMENTED

#pragma once

#include <stdexcept>

class BadWeakPtr : public std::runtime_error {
 public:
  BadWeakPtr() : std::runtime_error("BadWeakPtr") {
  }
};

template <class T>
class WeakPtr;

struct Counter {
  size_t strong_count = 0;
  size_t weak_count = 0;
};

template <class T>
class SharedPtr {
  T* ptr_;
  Counter* counter_;

  friend class WeakPtr<T>;

 public:
  SharedPtr() : ptr_(nullptr), counter_(nullptr) {
  }

  SharedPtr(std::nullptr_t) : ptr_(nullptr), counter_(nullptr) {  // NOLINT
  }

  explicit SharedPtr(T* pointer) : ptr_(pointer), counter_(new Counter{1, 0}) {
  }

  SharedPtr(const WeakPtr<T>& other) {  // NOLINT
    if (other.Expired()) {
      throw BadWeakPtr{};
    }
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    if (counter_) {
      counter_->strong_count++;
    }
  }

  SharedPtr(const SharedPtr& other) {
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    if (counter_) {
      counter_->strong_count++;
    }
  }

  SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {
      Reset();
      ptr_ = other.ptr_;
      counter_ = other.counter_;
      if (counter_) {
        counter_->strong_count++;
      }
    }
    return *this;
  }

  SharedPtr(SharedPtr&& other) noexcept : ptr_(nullptr), counter_(nullptr) {
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
    if (counter_) {
      counter_->strong_count--;
      if (counter_->strong_count == 0) {
        if (counter_->weak_count == 0) {
          delete counter_;
        }
        delete ptr_;
      }
    }
    ptr_ = pointer;
    counter_ = pointer ? new Counter{1, 0} : nullptr;
  }

  void Swap(SharedPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(counter_, other.counter_);
  }

  T* Get() const {
    return ptr_;
  }

  size_t UseCount() const {
    return counter_ ? counter_->strong_count : 0;
  }

  size_t WeakCount() const {
    return counter_ ? counter_->weak_count : 0;
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

template <class T>
class WeakPtr {
  T* ptr_;
  Counter* counter_;

  friend class SharedPtr<T>;

 public:
  WeakPtr() : ptr_(nullptr), counter_(nullptr) {
  }

  WeakPtr(std::nullptr_t) : ptr_(nullptr), counter_(nullptr) {  // NOLINT
  }

  WeakPtr(const SharedPtr<T>& other) {  // NOLINT
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    if (counter_) {
      counter_->weak_count++;
    }
  }

  WeakPtr(const WeakPtr& other) {
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    if (counter_) {
      counter_->weak_count++;
    }
  }

  WeakPtr& operator=(const WeakPtr& other) {
    if (this != &other) {
      Reset();
      ptr_ = other.ptr_;
      counter_ = other.counter_;
      if (counter_) {
        counter_->weak_count++;
      }
    }
    return *this;
  }

  WeakPtr(WeakPtr&& other) noexcept : ptr_(nullptr), counter_(nullptr) {
    Swap(other);
  }

  WeakPtr& operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
      Reset();
      Swap(other);
    }
    return *this;
  }

  ~WeakPtr() {
    Reset();
  }

  void Reset() {
    if (counter_) {
      counter_->weak_count--;
      if (counter_->strong_count == 0 && counter_->weak_count == 0) {
        delete counter_;
      }
    }
    ptr_ = nullptr;
    counter_ = nullptr;
  }

  void Swap(WeakPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(counter_, other.counter_);
  }

  size_t UseCount() const {
    return counter_ ? counter_->strong_count : 0;
  }

  size_t WeakCount() const {
    return counter_ ? counter_->weak_count : 0;
  }

  bool Expired() const {
    return UseCount() == 0;
  }

  SharedPtr<T> Lock() const {
    return Expired() ? SharedPtr<T>() : SharedPtr<T>(*this);
  }
};