#define REVERSE_REVERSED_IMPLEMENTED
#define TEMPORARY_REVERSED_IMPLEMENTED
#pragma once

#include <iostream>
#include <utility>

template <typename Container>
class ReversedSequence {
 private:
  Container container_;

 public:
  explicit ReversedSequence(Container&& cont) : container_(std::forward<Container>(cont)) {
  }

  auto begin() const -> decltype(container_.rbegin()) const {  // NOLINT
    return container_.rbegin();
  }

  auto begin() -> decltype(container_.rbegin()) {  // NOLINT
    return container_.rbegin();
  }

  auto end() const -> decltype(container_.rend()) const {  // NOLINT
    return container_.rend();
  }

  auto end() -> decltype(container_.rend()) {  // NOLINT
    return container_.rend();
  }

  auto rbegin() const -> decltype(container_.begin()) const {  // NOLINT
    return container_.begin();
  }

  auto rbegin() -> decltype(container_.begin()) {  // NOLINT
    return container_.begin();
  }

  auto rend() const -> decltype(container_.end()) const {  // NOLINT
    return container_.end();
  }

  auto rend() -> decltype(container_.end()) {  // NOLINT
    return container_.end();
  }
};

template <typename Container>
ReversedSequence<Container> Reversed(Container&& container) {
  return ReversedSequence<Container>(std::forward<Container>(container));
}