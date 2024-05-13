#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <list>

#include "iterops.h"
#include "iterops.h"  // check include guards

TEST_CASE("Advance", "[Iterops]") {
  {
    int array[50];
    auto ptr = array + 10;

    Advance(ptr, 33);
    REQUIRE(ptr == array + 43);

    Advance(ptr, -25);
    REQUIRE(ptr == array + 18);
  }

  {
    std::vector<int> v(50);
    auto iter = v.begin() + 10;

    Advance(iter, 33);
    REQUIRE(iter == v.begin() + 43);

    Advance(iter, -25);
    REQUIRE(iter == v.begin() + 18);
  }

  {
    std::list<int> l(50);
    auto iter = std::next(l.begin(), 10);

    Advance(iter, 33);
    REQUIRE(iter == std::next(l.begin(), 43));

    Advance(iter, -25);
    REQUIRE(iter == std::next(l.begin(), 18));
  }
}

TEST_CASE("Distance", "[Iterops]") {
  {
    int array[50];
    auto begin = array + 10;
    auto end = array + 48;
    REQUIRE(Distance(begin, end) == 38);
  }

  {
    std::vector<int> v(50);
    auto begin = v.begin() + 10;
    auto end = v.begin() + 48;
    REQUIRE(Distance(begin, end) == 38);
  }

  {
    std::list<int> l(50);
    auto begin = std::next(l.begin(), 10);
    auto end = std::next(l.begin(), 48);
    REQUIRE(Distance(begin, end) == 38);
  }
}

TEST_CASE("Next", "[Iterops]") {
  {
    int array[50];
    auto ptr = array + 10;

    REQUIRE(Next(ptr) == array + 11);
    REQUIRE(Next(ptr, 33) == array + 43);
    REQUIRE(Next(ptr, 5) == array + 15);
  }

  {
    std::vector<int> v(50);
    auto iter = v.begin() + 10;

    REQUIRE(Next(iter) == v.begin() + 11);
    REQUIRE(Next(iter, 33) == v.begin() + 43);
    REQUIRE(Next(iter, 5) == v.begin() + 15);
  }

  {
    std::list<int> l(50);
    auto iter = std::next(l.begin(), 10);

    REQUIRE(Next(iter) == std::next(l.begin(), 11));
    REQUIRE(Next(iter, 33) == std::next(l.begin(), 43));
    REQUIRE(Next(iter, 5) == std::next(l.begin(), 15));
  }
}

TEST_CASE("Prev", "[Iterops]") {
  {
    int array[50];
    auto ptr = array + 40;

    REQUIRE(Prev(ptr) == array + 39);
    REQUIRE(Prev(ptr, 17) == array + 23);
    REQUIRE(Prev(ptr, 5) == array + 35);
  }

  {
    std::vector<int> v(50);
    auto iter = v.begin() + 40;

    REQUIRE(Prev(iter) == v.begin() + 39);
    REQUIRE(Prev(iter, 17) == v.begin() + 23);
    REQUIRE(Prev(iter, 5) == v.begin() + 35);
  }

  {
    std::list<int> l(50);
    auto iter = std::next(l.begin(), 40);

    REQUIRE(Prev(iter) == std::next(l.begin(), 39));
    REQUIRE(Prev(iter, 17) == std::next(l.begin(), 23));
    REQUIRE(Prev(iter, 5) == std::next(l.begin(), 35));
  }
}
