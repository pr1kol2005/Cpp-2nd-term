#define TEMPORARY_ENUMERATE_IMPLEMENTED
#pragma once

#include <iostream>
#include <utility>

template <typename Container>
class Sequence {
 public:
  Container container_;

 public:
  explicit Sequence(Container&& cont) : container_(std::forward<Container>(cont)) {
  }

  template <typename it_type, typename data_type>
  class Iterator {
   protected:
    it_type it_;
    int num_;

   public:
    Iterator(it_type it, int num) : it_(it), num_(num) {
    }

    Iterator& operator++() {
      num_++;
      it_++;
      return *this;
    }

    Iterator operator++(int) {
      Iterator old_value = *this;
      ++(*this);
      return old_value;
    }

    bool operator==(Iterator other) const {
      return it_ == other.it_;
    }

    bool operator!=(Iterator other) const {
      return it_ != other.it_;
    }

    std::pair<int, data_type> operator*() {
      return {num_, *it_};
    }
  };

  using TypeIt = decltype(std::begin(std::declval<Container>()));
  using TypeData = decltype(*std::begin(std::declval<Container>()));

  Iterator<TypeIt, TypeData> begin() const {  // NOLINT
    return Iterator<TypeIt, TypeData>(container_.begin(), 0);
  }

  Iterator<TypeIt, TypeData> end() const {  // NOLINT
    return Iterator<TypeIt, TypeData>(container_.end(), 999);
  }
};

template <typename Container>
Sequence<Container> Enumerate(Container&& container) {
  return Sequence<Container>(std::forward<Container>(container));
};
