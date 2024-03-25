#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <list>
#include <vector>

#include "stack.h"
#include "stack.h"  // check include guards

TEST_CASE("Default", "[Stack]") {
  {
    Stack<std::vector<int>> s;
    REQUIRE(s.Empty());
    s.Push({1, 2, 3});
    s.Top()[1] = -2;
    REQUIRE(s.Top() == (std::vector{1, -2, 3}));
    s.Emplace(10, 1);
    REQUIRE(s.Top() == std::vector(10, 1));
    s.Push(s.Top());
    REQUIRE(s.Top() == std::vector(10, 1));
    REQUIRE(s.Size() == 3);
    s.Pop();
    s.Pop();
    REQUIRE(s.Size() == 1);
    REQUIRE(s.Top() == (std::vector{1, -2, 3}));
    s.Pop();
    REQUIRE(s.Size() == 0);
    REQUIRE(s.Empty());
  }

  {
    std::deque<int> d{1, 2, 3};
    Stack<int> s(d);
    REQUIRE_FALSE(s.Empty());
    REQUIRE(s.Top() == 3);
    s.Top() = 4;
    REQUIRE(s.Top() == 4);
    s.Push(-4);
    REQUIRE(s.Size() == 4);
    REQUIRE(s.Top() == -4);
    Stack<int> ss({-1, -1, -1});
    s.Swap(ss);

    REQUIRE(s.Size() == 3);
    REQUIRE(s.Top() == -1);
    REQUIRE(ss.Size() == 4);
    REQUIRE(ss.Top() == -4);
  }

  {
    std::deque<int> d{1, 2, 3};
    Stack<int> s(std::move(d));
    REQUIRE_FALSE(s.Empty());
    REQUIRE(s.Top() == 3);
    s.Top() = 4;
    REQUIRE(s.Top() == 4);
  }

  {
    std::deque<int> d{1, 2, 3};
    const Stack<int> s(d.begin(), d.end());
    REQUIRE_FALSE(s.Empty());
    REQUIRE(s.Top() == 3);
    REQUIRE(s.Size() == 3);
  }
}

TEST_CASE("List", "[Stack]") {
  {
    Stack<std::vector<int>, std::list<std::vector<int>>> s;
    REQUIRE(s.Empty());
    s.Push({1, 2, 3});
    s.Top()[1] = -2;
    REQUIRE(s.Top() == (std::vector{1, -2, 3}));
    s.Emplace(10, 1);
    REQUIRE(s.Top() == std::vector(10, 1));
    s.Push(s.Top());
    REQUIRE(s.Top() == std::vector(10, 1));
    REQUIRE(s.Size() == 3);
    s.Pop();
    s.Pop();
    REQUIRE(s.Size() == 1);
    REQUIRE(s.Top() == (std::vector{1, -2, 3}));
    s.Pop();
    REQUIRE(s.Size() == 0);
    REQUIRE(s.Empty());
  }

  {
    std::list<int> d{1, 2, 3};
    Stack<int, std::list<int>> s(d);
    REQUIRE_FALSE(s.Empty());
    REQUIRE(s.Top() == 3);
    s.Top() = 4;
    REQUIRE(s.Top() == 4);
    s.Push(-4);
    REQUIRE(s.Size() == 4);
    REQUIRE(s.Top() == -4);
    Stack<int, std::list<int>> ss({-1, -1, -1});
    s.Swap(ss);

    REQUIRE(s.Size() == 3);
    REQUIRE(s.Top() == -1);
    REQUIRE(ss.Size() == 4);
    REQUIRE(ss.Top() == -4);
  }

  {
    std::list<int> d{1, 2, 3};
    Stack<int, std::list<int>> s(std::move(d));
    REQUIRE_FALSE(s.Empty());
    REQUIRE(s.Top() == 3);
    s.Top() = 4;
    REQUIRE(s.Top() == 4);
  }

  {
    std::list<int> d{1, 2, 3};
    const Stack<int, std::list<int>> s(d.begin(), d.end());
    REQUIRE_FALSE(s.Empty());
    REQUIRE(s.Top() == 3);
    REQUIRE(s.Size() == 3);
  }
}

TEST_CASE("Emplace", "[Stack]") {
  struct A {
    std::unique_ptr<int> ptr;
    int& ref;

    A(std::unique_ptr<int> p, int& r) : ptr(std::move(p)), ref(r) {
    }
  };

  Stack<A> s;
  const auto p1 = new int{11};
  s.Emplace(std::unique_ptr<int>(p1), *p1);
  REQUIRE(s.Top().ptr.get() == p1);
  REQUIRE(*s.Top().ptr == s.Top().ref);
  s.Top().ref = 139;
  REQUIRE(*p1 == 139);

  const auto p2 = new int{12};
  s.Push(A(std::unique_ptr<int>(p2), *p2));
  REQUIRE(s.Top().ptr.get() == p2);
  REQUIRE(*s.Top().ptr == s.Top().ref);
  s.Top().ref = 123;
  REQUIRE(*p2 == 123);

  auto moved = std::move(s);
  REQUIRE(moved.Size() == 2);
  REQUIRE(moved.Top().ptr.get() == p2);
  REQUIRE(*moved.Top().ptr == moved.Top().ref);
  REQUIRE(*p2 == 123);

  s = std::move(moved);
  REQUIRE(s.Top().ptr.get() == p2);
  REQUIRE(*s.Top().ptr == s.Top().ref);
  REQUIRE(*p2 == 123);
}