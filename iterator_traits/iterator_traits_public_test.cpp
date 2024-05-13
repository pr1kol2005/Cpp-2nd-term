#include "iterator_traits.h"
#include "iterator_traits.h"

#include <cstddef>
#include <iterator>
#include <forward_list>
#include <list>
#include <vector>

void TestDereferenceable() {
  static_assert(kIsDereferenceableV<int*>);
  static_assert(!kIsDereferenceableV<int&>);
  static_assert(!kIsDereferenceableV<int>);

  struct A {
    void operator*() const;
  };

  struct B {};

  static_assert(kIsDereferenceableV<A>);
  static_assert(!kIsDereferenceableV<B>);
}

void TestIncrementable() {
  static_assert(kIsIncrementableV<int*>);
  static_assert(kIsIncrementableV<int&>);
  static_assert(kIsIncrementableV<int>);
  static_assert(!kIsIncrementableV<int[2]>);

  struct A {
    void operator++();
    void operator++(int);
  };

  struct B {
    void operator++();
  };

  struct C {};

  static_assert(kIsIncrementableV<A>);
  static_assert(!kIsIncrementableV<B>);
  static_assert(!kIsIncrementableV<C>);
}

void TestDecrementable() {
  static_assert(kIsDecrementableV<int*>);
  static_assert(kIsDecrementableV<int&>);
  static_assert(kIsDecrementableV<int>);
  static_assert(!kIsDecrementableV<int[2]>);

  struct A {
    void operator--();
    void operator--(int);
  };

  struct B {
    void operator--();
  };

  struct C {};

  static_assert(kIsDecrementableV<A>);
  static_assert(!kIsDecrementableV<B>);
  static_assert(!kIsDecrementableV<C>);
}

void TestArrowDereferenceable() {
  static_assert(kIsArrowDereferenceableV<int*>);
  static_assert(!kIsArrowDereferenceableV<int&>);
  static_assert(!kIsArrowDereferenceableV<int>);

  struct A {
    void operator->() const;
  };

  struct B {};

  static_assert(kIsArrowDereferenceableV<A>);
  static_assert(!kIsArrowDereferenceableV<B>);
}

void TestEqualityComparable() {
  static_assert(kIsEqualityComparableV<int*>);
  static_assert(kIsEqualityComparableV<int&>);
  static_assert(kIsEqualityComparableV<int>);
  static_assert(!kIsEqualityComparableV<void>);

  struct A {
    bool operator==(const A&) const;
    operator bool() const;  // NOLINT
  };

  struct B {
    A operator==(const B&) const;
  };

  struct C {
    B operator==(const C&) const;
  };

  struct D {};

  static_assert(kIsEqualityComparableV<A>);
  static_assert(kIsEqualityComparableV<B>);
  static_assert(!kIsEqualityComparableV<C>);
  static_assert(!kIsEqualityComparableV<D>);
}

void TestOrdered() {
  static_assert(kIsOrderedV<int*>);
  static_assert(kIsOrderedV<int&>);
  static_assert(kIsOrderedV<int>);
  static_assert(!kIsOrderedV<void>);

  struct A {
    bool operator<(const A&) const;
    operator bool() const;  // NOLINT
  };

  struct B {
    A operator<(const B&) const;
  };

  struct C {
    B operator<(const C&) const;
  };

  struct D {};

  static_assert(kIsOrderedV<A>);
  static_assert(kIsOrderedV<B>);
  static_assert(!kIsOrderedV<C>);
  static_assert(!kIsOrderedV<D>);
}

void TestSubtractable() {
  static_assert(kIsSubtractableV<int*>);
  static_assert(kIsSubtractableV<int&>);
  static_assert(kIsSubtractableV<int>);
  static_assert(!kIsSubtractableV<void>);
  static_assert(std::is_same_v<DifferenceType<int*>, std::ptrdiff_t>);
  static_assert(std::is_same_v<DifferenceType<double>, double>);
  static_assert(std::is_same_v<DifferenceType<char>, int>);

  struct A {
    int operator-(const A&) const;
  };

  struct B {};

  static_assert(kIsSubtractableV<A>);
  static_assert(!kIsSubtractableV<B>);
  static_assert(std::is_same_v<DifferenceType<A>, int>);
}

void TestHasIntegralArithmetic() {
  static_assert(kHasIntegralArithmeticV<int*>);
  static_assert(kHasIntegralArithmeticV<int&>);
  static_assert(kHasIntegralArithmeticV<int>);
  static_assert(!kHasIntegralArithmeticV<void>);

  struct A {
    int operator-(const A&) const;
    A& operator+=(int);
    A& operator-=(int);
  };

  struct B {
    A operator-(const B&) const;
    B& operator+=(A);
    B& operator-=(A);
  };

  struct C {
    int operator-(const C&) const;
    C& operator+=(int);
  };

  struct D {};

  static_assert(kHasIntegralArithmeticV<A>);
  static_assert(!kHasIntegralArithmeticV<B>);
  static_assert(!kHasIntegralArithmeticV<C>);
  static_assert(!kHasIntegralArithmeticV<D>);
}

void TestIsSubscriptable() {
  static_assert(kIsSubscriptableV<int*>);
  static_assert(!kIsSubscriptableV<int&>);
  static_assert(!kIsSubscriptableV<int>);
  static_assert(kIsSubscriptableV<int[2]>);

  struct A {
    int operator-(const A&) const;
    A& operator[](int);
  };

  struct B {
    A operator-(const B&) const;
    B& operator[](A);
  };

  struct C {};

  static_assert(kIsSubscriptableV<A>);
  static_assert(!kIsSubscriptableV<B>);
  static_assert(!kIsSubscriptableV<C>);
}

void TestIsIterator() {
  static_assert(kIsIteratorV<int*>);
  static_assert(!kIsIteratorV<void*>);
  static_assert(!kIsIteratorV<void*>);
  static_assert(kIsIteratorV<std::ostream_iterator<int>>);
  static_assert(kIsIteratorV<std::istream_iterator<int>>);
  static_assert(kIsIteratorV<std::forward_list<int>::iterator>);
  static_assert(kIsIteratorV<std::list<int>::iterator>);
  static_assert(kIsIteratorV<std::vector<int>::iterator>);

  struct Iterator {
    Iterator(const Iterator&);
    Iterator& operator=(const Iterator&);
    ~Iterator();
    void operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
  };

  struct A : Iterator {
    A(const A&) = delete;
  };

  struct B : Iterator {
    B& operator=(const B&) = delete;
  };

  struct C : Iterator {
    ~C() = delete;
  };

  struct D : Iterator {
    void operator*() const = delete;
  };

  struct E : Iterator {
    E& operator++() = delete;
  };

  static_assert(kIsIteratorV<Iterator>);
  static_assert(!kIsIteratorV<A>);
  static_assert(!kIsIteratorV<B>);
  static_assert(!kIsIteratorV<C>);
  static_assert(!kIsIteratorV<D>);
  static_assert(!kIsIteratorV<E>);
}

void TestIsInputIterator() {
  static_assert(kIsInputIteratorV<int*>);
  static_assert(!kIsInputIteratorV<void*>);
  static_assert(!kIsInputIteratorV<void*>);
  static_assert(!kIsInputIteratorV<std::ostream_iterator<int>>);
  static_assert(kIsInputIteratorV<std::istream_iterator<int>>);
  static_assert(kIsInputIteratorV<std::forward_list<int>::iterator>);
  static_assert(kIsInputIteratorV<std::list<int>::iterator>);
  static_assert(kIsInputIteratorV<std::vector<int>::iterator>);

  struct Iterator {
    Iterator(const Iterator&);
    Iterator& operator=(const Iterator&);
    ~Iterator();
    void operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator==(Iterator) const;
    Iterator* operator->() const;
  };

  struct A : Iterator {
    bool operator==(A) const = delete;
  };

  struct B : Iterator {
    B* operator->() const = delete;
  };

  static_assert(kIsInputIteratorV<Iterator>);
  static_assert(!kIsInputIteratorV<A>);
  static_assert(!kIsInputIteratorV<B>);
}

void TestIsForwardIterator() {
  static_assert(kIsForwardIteratorV<int*>);
  static_assert(!kIsForwardIteratorV<void*>);
  static_assert(!kIsForwardIteratorV<void*>);
  static_assert(!kIsForwardIteratorV<std::ostream_iterator<int>>);
  static_assert(kIsForwardIteratorV<std::forward_list<int>::iterator>);
  static_assert(kIsForwardIteratorV<std::list<int>::iterator>);
  static_assert(kIsForwardIteratorV<std::vector<int>::iterator>);

  struct Iterator {
    Iterator();
    Iterator(const Iterator&);
    Iterator& operator=(const Iterator&);
    ~Iterator();
    void operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator==(Iterator) const;
    Iterator* operator->() const;
  };

  struct A : Iterator {
    A() = delete;
  };

  static_assert(kIsForwardIteratorV<Iterator>);
  static_assert(!kIsForwardIteratorV<A>);
}

void TestIsBidirectionalIterator() {
  static_assert(kIsBidirectionalIteratorV<int*>);
  static_assert(!kIsBidirectionalIteratorV<void*>);
  static_assert(!kIsBidirectionalIteratorV<void*>);
  static_assert(!kIsBidirectionalIteratorV<std::ostream_iterator<int>>);
  static_assert(!kIsBidirectionalIteratorV<std::forward_list<int>::iterator>);
  static_assert(kIsBidirectionalIteratorV<std::list<int>::iterator>);
  static_assert(kIsBidirectionalIteratorV<std::vector<int>::iterator>);

  struct Iterator {
    Iterator();
    Iterator(const Iterator&);
    Iterator& operator=(const Iterator&);
    ~Iterator();
    void operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator==(Iterator) const;
    Iterator* operator->() const;
  };

  struct A : Iterator {
    using Iterator::Iterator;
    A& operator--() = delete;
  };

  static_assert(kIsBidirectionalIteratorV<Iterator>);
  static_assert(!kIsBidirectionalIteratorV<A>);
}

void TestIsRandomAccessIterator() {
  static_assert(kIsRandomAccessIteratorV<int*>);
  static_assert(!kIsRandomAccessIteratorV<void*>);
  static_assert(!kIsRandomAccessIteratorV<void*>);
  static_assert(!kIsRandomAccessIteratorV<std::ostream_iterator<int>>);
  static_assert(!kIsRandomAccessIteratorV<std::forward_list<int>::iterator>);
  static_assert(!kIsRandomAccessIteratorV<std::list<int>::iterator>);
  static_assert(kIsRandomAccessIteratorV<std::vector<int>::iterator>);

  struct Iterator {
    Iterator();
    Iterator(const Iterator&);
    Iterator& operator=(const Iterator&);
    ~Iterator();
    void operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator==(Iterator) const;
    Iterator* operator->() const;
    int operator-(Iterator) const;
    Iterator& operator+=(int);
    Iterator& operator-=(int);
    int& operator[](int) const;
    bool operator<(Iterator) const;
  };

  struct A : Iterator {
    using Iterator::Iterator;
    int operator-(A) = delete;
  };

  struct B : Iterator {
    using Iterator::Iterator;
    B& operator+=(int) = delete;
  };

  struct C : Iterator {
    using Iterator::Iterator;
    int& operator[](int) = delete;
  };

  struct D : Iterator {
    using Iterator::Iterator;
    bool operator<(Iterator) const = delete;
  };

  static_assert(kIsRandomAccessIteratorV<Iterator>);
  static_assert(!kIsRandomAccessIteratorV<A>);
  static_assert(!kIsRandomAccessIteratorV<B>);
  static_assert(!kIsRandomAccessIteratorV<C>);
  static_assert(!kIsRandomAccessIteratorV<D>);
}

int main() {
}