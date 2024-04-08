#pragma once

#include <memory>
#include <stdexcept>

class BadAnyCast : public std::bad_cast {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "BadAnyCast error";
  }
};

class IHolder {
 public:
  virtual ~IHolder() = default;

  virtual std::unique_ptr<IHolder> Clone() const = 0;
};

template <class T>
class AnyHolder : public IHolder {
 public:
  T value;

  ~AnyHolder() override = default;

  std::unique_ptr<IHolder> Clone() const override {
    return std::make_unique<AnyHolder<T>>(value);
  }

  explicit AnyHolder(const T& valuee) : value(valuee) {
  }

  explicit AnyHolder(T&& valuee) : value(std::move(valuee)) {
  }
};

class Any {
 public:
  std::unique_ptr<IHolder> holder;

  Any() : holder(nullptr) {
  }

  template <typename T>
  Any(const T& value) {                              // NOLINT
    holder = std::make_unique<AnyHolder<T>>(value);  // NOLINT
  }                                                  // NOLINT

  template <typename T>
  Any& operator=(const T& value) {
    holder = std::make_unique<AnyHolder<T>>(value);
    return *this;
  }

  Any(const Any& other) {
    holder = other.holder ? (other.holder)->Clone() : nullptr;
  }

  Any& operator=(const Any& other) {
    if (this != &other) {
      holder = other.holder ? (other.holder)->Clone() : nullptr;
    }
    return *this;
  }

  Any(Any&& other) noexcept {
    holder = std::move(other.holder);
  }

  Any& operator=(Any&& other) noexcept {
    if (this != &other) {
      holder = std::move(other.holder);
    }
    return *this;
  }

  void Swap(Any& other) {
    std::swap(holder, other.holder);
  }

  void Reset() {
    holder.reset();
  }

  bool HasValue() {
    return static_cast<bool>(holder);
  }
};

template <class T>
T AnyCast(const Any& value) {
  auto result = dynamic_cast<AnyHolder<T>*>(value.holder.get());
  if (!result) {
    throw BadAnyCast();
  }
  return result->value;
};