#include "array_traits.h"
#include "array_traits.h"  // check include guard

void TestIsArray() {
  static_assert(!kIsArrayV<int>);
  static_assert(kIsArrayV<int[3]>);
  static_assert(kIsArrayV<const int[]>);
  static_assert(kIsArrayV<int[3][4]>);
  static_assert(kIsArrayV<int*[][4][5]>);
  static_assert(!kIsArrayV<int(&)[3]>);
}

void TestRank() {
  static_assert(kRankV<int> == 0);
  static_assert(kRankV<int[3]> == 1);
  static_assert(kRankV<const int[]> == 1);
  static_assert(kRankV<int[3][4]> == 2);
  static_assert(kRankV<int*[][4][5]> == 3);
  static_assert(kRankV<int(&)[3]> == 0);
}

void TestSize() {
  static_assert(kSizeV<int> == 1);
  static_assert(kSizeV<int[3]> == 3);
  static_assert(kSizeV<const int[]> == 0);
  static_assert(kSizeV<int[3][4]> == 3);
  static_assert(kSizeV<int*[][4][5]> == 0);
  static_assert(kSizeV<int(&)[3]> == 1);
}

void TestTotalSize() {
  static_assert(kTotalSizeV<int> == 1);
  static_assert(kTotalSizeV<int[3]> == 3);
  static_assert(kTotalSizeV<const int[]> == 0);
  static_assert(kTotalSizeV<int[3][4]> == 12);
  static_assert(kTotalSizeV<int* const[3][4][5]> == 60);
  static_assert(kTotalSizeV<int*[][4][5]> == 0);
  static_assert(kTotalSizeV<int(&)[3]> == 1);
}

void TestRemoveArray() {
  static_assert(std::is_same_v<RemoveArrayT<int>, int>);
  static_assert(std::is_same_v<RemoveArrayT<int[3]>, int>);
  static_assert(std::is_same_v<RemoveArrayT<const int[]>, const int>);
  static_assert(std::is_same_v<RemoveArrayT<int[3][4]>, int[4]>);
  static_assert(std::is_same_v<RemoveArrayT<int*[][4][5]>, int* [4][5]>);
  static_assert(std::is_same_v<RemoveArrayT<int(&)[3]>, int(&)[3]>);
}

void TestRemoveAllArrays() {
  static_assert(std::is_same_v<RemoveAllArraysT<int>, int>);
  static_assert(std::is_same_v<RemoveAllArraysT<int[3]>, int>);
  static_assert(std::is_same_v<RemoveAllArraysT<const int[]>, const int>);
  static_assert(std::is_same_v<RemoveAllArraysT<int[3][4]>, int>);
  static_assert(std::is_same_v<RemoveAllArraysT<int*[][4][5]>, int*>);
  static_assert(std::is_same_v<RemoveAllArraysT<int(&)[3]>, int(&)[3]>);
}

int main() {
}