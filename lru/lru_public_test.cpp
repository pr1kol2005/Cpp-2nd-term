#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "lru.h"
#include "lru.h"  // check include guard

#include <utility>

TEST_CASE("Example", "[LRUMap]") {
  auto lru = LRUMap<int, int>(3);
  REQUIRE(std::as_const(lru).Empty());
  REQUIRE(std::as_const(lru).Capacity() == 3);
  REQUIRE(std::as_const(lru).Size() == 0);

  lru.Add(1, -1);
  lru.Add(2, -2);
  lru.Add(3, -3);
  REQUIRE(std::as_const(lru).Size() == 3);
  REQUIRE(std::as_const(lru).Capacity() == 3);
  REQUIRE_FALSE(std::as_const(lru).Empty());
  REQUIRE(std::as_const(lru).Get(1) == -1);
  REQUIRE(std::as_const(lru).Get(2) == -2);
  REQUIRE(std::as_const(lru).Get(3) == -3);
  REQUIRE(std::as_const(lru).Contains(1));
  REQUIRE(std::as_const(lru).Contains(2));
  REQUIRE(std::as_const(lru).Contains(3));

  lru.Get(1) = 1;
  REQUIRE(std::as_const(lru).Get(1) == 1);

  lru.Add(4, -4);
  REQUIRE(std::as_const(lru).Size() == 3);
  REQUIRE(std::as_const(lru).Capacity() == 3);
  REQUIRE(std::as_const(lru).Contains(1));
  REQUIRE_FALSE(std::as_const(lru).Contains(2));
  REQUIRE(std::as_const(lru).Contains(3));
  REQUIRE(std::as_const(lru).Contains(4));

  lru.Erase(1);
  REQUIRE(std::as_const(lru).Size() == 2);
  REQUIRE(std::as_const(lru).Capacity() == 3);
  REQUIRE(std::as_const(lru).GetOr(1, 12345) == 12345);

  lru.Clear();
  REQUIRE(std::as_const(lru).Size() == 0);
  REQUIRE(std::as_const(lru).Capacity() == 3);
  REQUIRE_THROWS_AS(std::as_const(lru).Get(4), std::out_of_range);
}