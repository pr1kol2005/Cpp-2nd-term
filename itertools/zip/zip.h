#pragma once

#define TEMPORARY_ZIP_IMPLEMENTED

#include <iterator>
#include <tuple>
#include <utility>

template <typename... Iterators>
class ZipIterator {
  std::tuple<Iterators...> iterators_;

 public:
  using iterator_category = std::forward_iterator_tag;                                     // NOLINT
  using value_type = std::tuple<typename std::iterator_traits<Iterators>::value_type...>;  // NOLINT
  using reference = std::tuple<typename std::iterator_traits<Iterators>::reference...>;    // NOLINT
  using pointer = std::tuple<typename std::iterator_traits<Iterators>::pointer...>;        // NOLINT
  using difference_type = size_t;                                                          // NOLINT

  explicit ZipIterator(Iterators... iterators) : iterators_(iterators...) {
  }

  ZipIterator& operator++() {
    Increment(std::index_sequence_for<Iterators...>{});
    return *this;
  }

  reference operator*() const {
    return Dereference(std::index_sequence_for<Iterators...>{});
  }

  bool operator==(const ZipIterator& other) const {
    return iterators_ == other.iterators_;
  }

  bool operator!=(const ZipIterator& other) const {
    return !IsEqual(other, std::index_sequence_for<Iterators...>{});
  }

  template <size_t... I>
  void Increment(std::index_sequence<I...>) {
    ((++std::get<I>(iterators_)), ...);
  }

  template <size_t... I>
  reference Dereference(std::index_sequence<I...>) const {
    return reference(*std::get<I>(iterators_)...);
  }

  template <size_t... I>
  bool IsEqual(const ZipIterator& other, std::index_sequence<I...>) const {
    return ((std::get<I>(iterators_) == std::get<I>(other.iterators_)) || ...);
  }
};

template <typename... Containers>
class ZipObject {
  std::tuple<Containers...> containers_;

 public:
  using iterator = ZipIterator<decltype(std::begin(std::declval<Containers&>()))...>;              // NOLINT
  using const_iterator = ZipIterator<decltype(std::begin(std::declval<const Containers&>()))...>;  // NOLINT

  explicit ZipObject(Containers&&... containers) : containers_(std::forward<Containers>(containers)...) {
  }

  iterator begin() {  // NOLINT
    return MakeIterator(std::index_sequence_for<Containers...>{});
  }

  iterator end() {  // NOLINT
    return MakeEndIterator(std::index_sequence_for<Containers...>{});
  }

  const_iterator begin() const {  // NOLINT
    return MakeIterator(std::index_sequence_for<Containers...>{});
  }

  const_iterator end() const {  // NOLINT
    return MakeEndIterator(std::index_sequence_for<Containers...>{});
  }

  template <size_t... I>
  iterator MakeIterator(std::index_sequence<I...>) {
    return iterator(std::begin(std::get<I>(containers_))...);
  }

  template <size_t... I>
  const_iterator MakeIterator(std::index_sequence<I...>) const {
    return const_iterator(std::begin(std::get<I>(containers_))...);
  }

  template <size_t... I>
  iterator MakeEndIterator(std::index_sequence<I...>) {
    return iterator(std::end(std::get<I>(containers_))...);
  }

  template <size_t... I>
  const_iterator MakeEndIterator(std::index_sequence<I...>) const {
    return const_iterator(std::end(std::get<I>(containers_))...);
  }
};

template <typename... Containers>
auto Zip(Containers&&... containers) {
  return ZipObject<Containers...>(std::forward<Containers>(containers)...);
}
