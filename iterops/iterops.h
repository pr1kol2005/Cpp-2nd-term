#pragma once

#include <cstddef>
#include <iterator>
#include <type_traits>

template <class Iterator>
constexpr void Advance(Iterator& it, std::ptrdiff_t n) {
  using Category = typename std::iterator_traits<Iterator>::iterator_category;

  if constexpr (std::is_base_of_v<std::random_access_iterator_tag, Category>) {
    it += n;
  } else {
    while (n > 0) {
      --n;
      ++it;
    }
    if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, Category>) {
      while (n < 0) {
        ++n;
        --it;
      }
    }
  }
}

template <class Iterator>
constexpr Iterator Next(Iterator it, typename std::iterator_traits<Iterator>::difference_type n = 1) {
  Advance(it, n);
  return it;
}

template <class Iterator>
constexpr Iterator Prev(Iterator it, typename std::iterator_traits<Iterator>::difference_type n = 1) {
  std::advance(it, -n);
  return it;
}

template <class Iterator>
constexpr typename std::iterator_traits<Iterator>::difference_type Distance(Iterator begin, Iterator end) {
  using Category = typename std::iterator_traits<Iterator>::iterator_category;

  if constexpr (std::is_base_of_v<std::random_access_iterator_tag, Category>) {
    return end - begin;
  } else {
    typename std::iterator_traits<Iterator>::difference_type result = 0;
    while (begin != end) {
      ++begin;
      ++result;
    }
    return result;
  }
}