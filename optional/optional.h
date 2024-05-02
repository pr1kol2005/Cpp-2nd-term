#pragma once

#include <stdexcept>

struct BadOptionalAccess : public std::logic_error {
  BadOptionalAccess() : std::logic_error("object is dead") {
  } 
};

template <typename T>
class Optional { 
  char memory_[sizeof(T)];
  bool is_alive_;

 public:
  Optional() : is_alive_(false) {
  }

  Optional(const Optional& other) {
    is_alive_ = false;
    if (other.is_alive_) {
      new (memory_) T(*reinterpret_cast<const T*>(other.memory_));
      is_alive_ = true;
    }
  }

  Optional(Optional&& other) noexcept {
    is_alive_ = false;
    if (other.is_alive_) {
      new (memory_) T(std::move(*reinterpret_cast<T*>(other.memory_)));
      is_alive_ = true;
    }
  }

  explicit Optional(const T& other) {
    new (memory_) T(other);
    is_alive_ = true;
  }

  explicit Optional(T&& other) noexcept {
    new (memory_) T(std::move(other));
    is_alive_ = true;
  }

  ~Optional() {
    if (is_alive_) {
      reinterpret_cast<T*>(memory_)->~T();
      is_alive_ = false;
    }
  }

  Optional& operator=(const Optional& other) {
    if (!other.is_alive_) {
      if (is_alive_) {
        reinterpret_cast<T*>(memory_)->~T();
      }
      is_alive_ = false;
      return *this;
    }
    if (is_alive_) {
      reinterpret_cast<T*>(memory_)->~T();
    } else {
      is_alive_ = true;
    }
    new (memory_) T(*reinterpret_cast<const T*>(other.memory_));
    return *this;
  }

  Optional& operator=(Optional&& other) noexcept {
    if (!other.is_alive_) {
      if (is_alive_) {
        reinterpret_cast<T*>(memory_)->~T();
      }
      is_alive_ = false;
      return *this;
    }
    if (is_alive_) {
      reinterpret_cast<const T*>(memory_)->~T();
    } else {
      is_alive_ = true;
    }
    new (memory_) T(std::move(*reinterpret_cast<T*>(other.memory_)));
    return *this;
  }

  Optional& operator=(const T& other) {
    if (is_alive_) {
      reinterpret_cast<T*>(memory_)->~T();
    } else {
      is_alive_ = true;
    }
    new (memory_) T(other);
    return *this;
  }

  Optional& operator=(T&& other) noexcept {
    if (is_alive_) {
      reinterpret_cast<T*>(memory_)->~T();
    } else {
      is_alive_ = true;
    }
    new (memory_) T(std::move(other));
    return *this;
  }

  bool HasValue() const {
    return is_alive_;
  }

  explicit operator bool() const {
    return is_alive_;
  }

  const T& Value() const {
    if (!is_alive_) {
      throw BadOptionalAccess();
    }
    return *reinterpret_cast<const T*>(memory_);
  }

  T& Value() {
    if (!is_alive_) {
      throw BadOptionalAccess();
    }
    return *reinterpret_cast<T*>(memory_);
  }

  T& operator*() {
    return *reinterpret_cast<T*>(memory_);
  }

  const T& operator*() const {
    return *reinterpret_cast<const T*>(memory_);
  }

  template <typename... Args>
  T& Emplace(Args&&... args) {
    this->~Optional();
    new (memory_) T(std::forward<Args>(args)...);
    is_alive_ = true;
    return *reinterpret_cast<T*>(memory_);
  }

  void Reset() {
    if (is_alive_) {
      reinterpret_cast<T*>(memory_)->~T();
      is_alive_ = false;
    }
  }

  void Swap(Optional& other) {
    if (other.is_alive_ && !is_alive_) {
      new (memory_) T(*reinterpret_cast<T*>(other.memory_));
      is_alive_ = true;
      other.is_alive_ = false;
      reinterpret_cast<T*>(other.memory_)->~T();
      return;
    }
    if (!other.is_alive_ && is_alive_) {
      new (other.memory_) T(*reinterpret_cast<T*>(memory_));
      reinterpret_cast<T*>(memory_)->~T();
      other.is_alive_ = true;
      is_alive_ = false;
      return;
    }
    if (other.is_alive_ && is_alive_) {
      std::swap(*reinterpret_cast<T*>(memory_), *reinterpret_cast<T*>(other.memory_));
    }
  }
};