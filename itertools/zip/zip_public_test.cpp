#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <list>

#include "zip.h"
#include "zip.h"  // check include guards

TEST_CASE("Empty", "[Zip]") {
  const auto v = std::vector<int>{1, 2, 3};
  const auto empty_l = std::list<float>{};
  for ([[maybe_unused]] auto&& [x, y] : Zip(v, empty_l)) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto&& [a, b, c, d, e] : Zip(empty_l, v, empty_l, v, v)) {
    REQUIRE(false);
  }

#ifdef TEMPORARY_ZIP_IMPLEMENTED

  for ([[maybe_unused]] auto&& [x, y] : Zip(std::vector<int>{}, std::list<float>{1, 2, 3})) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto&& [x, y] : Zip(v, std::list<float>{})) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto&& [x, y] : Zip(std::vector<int>{}, empty_l)) {
    REQUIRE(false);
  }

#endif  // TEMPORARY_ZIP_IMPLEMENTED
}

TEST_CASE("Elementary", "[Zip]") {
  {
    auto v = std::vector<int>{1, 2, 3, 4};
    auto l = std::list<float>{1, 2, 3, 4, 5};
    auto copy_v = v;
    auto copy_l = l;
    int i_v = 0;
    auto i_l = copy_l.begin();
    for (auto&& [x, y, z] : Zip(v, l, v)) {
      REQUIRE(x == v[i_v]);
      REQUIRE(y == *i_l);
      REQUIRE(z == v[i_v]);
      ++x, ++copy_v[i_v];
      ++y, ++(*i_l);
      ++z, ++copy_v[i_v];
      ++i_v, ++i_l;
    }
    REQUIRE(i_v == 4);
    REQUIRE(v == copy_v);
    REQUIRE(l == copy_l);

    i_v = 0;
    i_l = copy_l.begin();
    const auto zip = Zip(std::as_const(v), l);
    for (auto&& [x, y] : zip) {
      REQUIRE((std::is_same_v<decltype(x), const int&>));
      REQUIRE((std::is_same_v<decltype(y), float&>));
      REQUIRE(x == copy_v[i_v]);
      REQUIRE(y == *i_l);
      ++i_v, ++i_l;
    }
    REQUIRE(i_v == 4);
  }

#ifdef TEMPORARY_ZIP_IMPLEMENTED

  {
    auto arr = std::array{2, 0, 4, -1, 1};
    int i = 0;
    for (auto&& [x, y] : Zip(std::array{2, 0, 4, -1, 1}, arr)) {
      REQUIRE(x == y);
      REQUIRE(x == arr[i]);
      REQUIRE((std::is_same_v<decltype(y), int&>));
      ++y;
      ++i;
    }
    REQUIRE(i == 5);

    i = 0;
    const auto zip = Zip(arr, std::array{2, 0, 4, -1, 1});
    for (auto&& [x, y] : zip) {
      REQUIRE(x == y + 1);
      REQUIRE((std::is_same_v<decltype(x), int&>));
      ++i;
    }
    REQUIRE(i == 5);
  }

#endif  // TEMPORARY_ZIP_IMPLEMENTED
}

#ifdef TEMPORARY_ZIP_IMPLEMENTED

TEST_CASE("Compound", "[Zip]") {
  {
    auto v = std::vector<int>{1, 2, 3, 4};
    auto l = std::list<float>{1, 2, 3, 4, 5};
    auto copy_v = v;
    auto copy_l = l;
    int i_v = 0;
    auto i_l = copy_l.begin();
    for (auto&& [x, item_lv] : Zip(v, Zip(l, v))) {
      auto&& [y, z] = item_lv;
      REQUIRE(x == v[i_v]);
      REQUIRE(y == *i_l);
      REQUIRE(z == v[i_v]);
      ++x, ++copy_v[i_v];
      ++y, ++(*i_l);
      ++z, ++copy_v[i_v];
      ++i_v, ++i_l;
    }
    REQUIRE(i_v == 4);
    REQUIRE(v == copy_v);
    REQUIRE(l == copy_l);

    i_v = 0;
    i_l = copy_l.begin();
    const auto zip = Zip(Zip(v, std::as_const(l)), v);
    for (auto&& [item_vl, z] : zip) {
      auto&& [x, y] = item_vl;
      REQUIRE((std::is_same_v<decltype(y), const float&>));
      REQUIRE((std::is_same_v<decltype(x), int&>));
      REQUIRE((std::is_same_v<decltype(z), int&>));
      REQUIRE(x == v[i_v]);
      REQUIRE(y == *i_l);
      REQUIRE(z == v[i_v]);
      ++i_v, ++i_l;
    }
    REQUIRE(i_v == 4);
  }

  {
    auto arr = std::array{2, 0, 4, -1, 1};
    int i = 0;
    for (auto&& [x, item] : Zip(std::array{2, 0, 4, -1, 1}, Zip(arr, std::array{2, 0, 4, -1, 1}))) {
      auto&& [y, z] = item;
      REQUIRE((std::is_same_v<decltype(y), int&>));
      REQUIRE(x == y);
      REQUIRE(x == arr[i]);
      ++i;
    }
    REQUIRE(i == 5);

    i = 0;
    const auto zip = Zip(Zip(arr, std::array{2, 0, 4, -1, 1}), arr);
    for (auto&& [item, z] : zip) {
      auto&& [x, y] = item;
      REQUIRE((std::is_same_v<decltype(x), int&>));
      REQUIRE((std::is_same_v<decltype(z), int&>));
      REQUIRE(x == y);
      REQUIRE(x == arr[i]);
      ++i;
    }
    REQUIRE(i == 5);
  }
}

#endif  // TEMPORARY_ZIP_IMPLEMENTED
