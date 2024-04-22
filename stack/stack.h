#pragma once

#include <deque>
#include <utility>
#include <iterator>

template <class T, class Container = std::deque<T>>
class Stack {
 public:
  Container buffer_;

  Stack() : buffer_() {
  }

  explicit Stack(const Container& container) : buffer_(container) {
  }

  Stack(Container::iterator begin, Container::iterator end) {
    buffer_ = Container(begin, end);
  }

  T& Top() {
    return buffer_.back();
  }

  const T& Top() const {
    return buffer_.back();
  }

  bool Empty() const {
    return buffer_.empty();
  }

  size_t Size() const {
    return buffer_.size();
  }

  template <class TT = T>
  void Push(TT&& value) {
    buffer_.push_back(std::forward<TT>(value));
  }

  template <class... Args>
  void Emplace(Args&&... args) {
    buffer_.emplace_back(std::forward<Args>(args)...);
  }

  void Pop() {
    buffer_.pop_back();
  }

  void Swap(Stack& other) {
    std::swap(buffer_, other.buffer_);
  }
};