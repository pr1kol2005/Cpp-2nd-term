// #define TEMPORARY_ZIP_IMPLEMENTED

#include <tuple>
#include <iterator>
#include <type_traits>
#include <utility>

template <typename... Containers>
class ZipContainer {
  std::tuple<Containers...> result_;

 public:
  class Iterator {
    std::tuple<typename Containers::iterator...> iterators_;

    template <std::size_t... Is>
    auto dereference(std::index_sequence<Is...>) const {
      return std::tie(*std::get<Is>(iterators_)...);
    }

   public:
    explicit Iterator(typename Containers::iterator... its) : iterators_(its...) {}

    Iterator& operator++() {
      std::apply([](auto&... its) { (..., ++its); }, iterators_);
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      return iterators_ != other.iterators_;
    }

    auto operator*() const {
      return dereference(std::index_sequence_for<Containers...>{});
    }
  };

  explicit ZipContainer(Containers&&... conts) : result_(std::forward<Containers>(conts)...) {
  }

  auto begin() const {
    return Iterator(std::begin(std::get<Containers>(result_))...);
  }

  auto end() const {
    return Iterator(std::end(std::get<Containers>(result_))...);
  }
};

template <typename... Containers>
ZipContainer<Containers...> Zip(Containers&&... inputs) {
  return ZipContainer<Containers...>(std::forward<Containers>(inputs)...);
}
