#include "type_vector.h"
#include "type_vector.h"  // check include guard

#include <cstdint>
#include <type_traits>

template <class T, class = void>
struct HasType : std::false_type {};

template <class T>
struct HasType<T, std::void_t<typename T::type>> : std::true_type {};

void TestSize() {
  static_assert(kSizeV<TypeVector<>> == 0);
  static_assert(kSizeV<TypeVector<int>> == 1);
  static_assert(kSizeV<TypeVector<void, const double>> == 2);
  static_assert(kSizeV<TypeVector<int&, double* const, TypeVector<int, void>>> == 3);
  static_assert(kSizeV<TypeVector<int, int, int, int>> == 4);

  static_assert(kEmptyV<TypeVector<>>);
  static_assert(!kEmptyV<TypeVector<int>>);
  static_assert(!kEmptyV<TypeVector<void, const double>>);
  static_assert(!kEmptyV<TypeVector<int&, double* const, TypeVector<int, void>>>);
  static_assert(!kEmptyV<TypeVector<int, int, int, int>>);
}

void TestFrontBack() {
  static_assert(!HasType<Front<TypeVector<>>>{});
  static_assert(std::is_same_v<FrontT<TypeVector<int>>, int>);
  static_assert(std::is_same_v<FrontT<TypeVector<void, const double>>, void>);
  static_assert(std::is_same_v<FrontT<TypeVector<int&, double* const, void>>, int&>);

  static_assert(!HasType<Back<TypeVector<>>>{});
  static_assert(std::is_same_v<BackT<TypeVector<int>>, int>);
  static_assert(std::is_same_v<BackT<TypeVector<void, const double>>, const double>);
  static_assert(std::is_same_v<BackT<TypeVector<int&, double* const, void>>, void>);
}

void TestAt() {
  static_assert(!HasType<At<TypeVector<>, 0>>{});
  static_assert(!HasType<At<TypeVector<>, 1>>{});
  static_assert(!HasType<At<TypeVector<int, double>, 2>>{});
  static_assert(std::is_same_v<AtT<TypeVector<int>, 0>, int>);
  static_assert(std::is_same_v<AtT<TypeVector<void, const double>, 0>, void>);
  static_assert(std::is_same_v<AtT<TypeVector<void, const double>, 1>, const double>);
  static_assert(std::is_same_v<AtT<TypeVector<int&, double* const, void>, 0>, int&>);
  static_assert(std::is_same_v<AtT<TypeVector<int&, double* const, void>, 1>, double* const>);
  static_assert(std::is_same_v<AtT<TypeVector<int&, double* const, void>, 2>, void>);
}

void TestContains() {
  static_assert(!kContainsV<TypeVector<>, int>);
  static_assert(!kContainsV<TypeVector<>, void>);
  static_assert(kContainsV<TypeVector<int>, int>);
  static_assert(!kContainsV<TypeVector<int>, void>);
  static_assert(kContainsV<TypeVector<int, void>, int>);
  static_assert(kContainsV<TypeVector<int, void>, void>);
  static_assert(!kContainsV<TypeVector<int, void>, double>);
  static_assert(kContainsV<TypeVector<int&, const int, int*, int[10], const int* const>, const int>);
  static_assert(!kContainsV<TypeVector<int&, const int, int*, int[10], const int* const>, int>);
}

void TestCount() {
  static_assert(kCountV<TypeVector<>, int> == 0);
  static_assert(kCountV<TypeVector<>, void> == 0);
  static_assert(kCountV<TypeVector<int>, int> == 1);
  static_assert(kCountV<TypeVector<int>, void> == 0);
  static_assert(kCountV<TypeVector<int, void>, int> == 1);
  static_assert(kCountV<TypeVector<int, void>, void> == 1);
  static_assert(kCountV<TypeVector<int, void>, double> == 0);
  static_assert(kCountV<TypeVector<int&, const int, int*, int[10], int*>, const int> == 1);
  static_assert(kCountV<TypeVector<int&, const int, int*, int[10], int*, int*, int>, int*> == 3);
}

void TestPush() {
  static_assert(std::is_same_v<PushFrontT<TypeVector<>, int>, TypeVector<int>>);
  static_assert(std::is_same_v<PushFrontT<TypeVector<int>, void>, TypeVector<void, int>>);
  static_assert(std::is_same_v<PushFrontT<TypeVector<int, void>, double>, TypeVector<double, int, void>>);

  static_assert(std::is_same_v<PushBackT<TypeVector<>, int>, TypeVector<int>>);
  static_assert(std::is_same_v<PushBackT<TypeVector<int>, void>, TypeVector<int, void>>);
  static_assert(std::is_same_v<PushBackT<TypeVector<int, void>, double>, TypeVector<int, void, double>>);
}

void TestPop() {
  static_assert(!HasType<PopFront<TypeVector<>>>{});
  static_assert(std::is_same_v<PopFrontT<TypeVector<int>>, TypeVector<>>);
  static_assert(std::is_same_v<PopFrontT<TypeVector<int, void>>, TypeVector<void>>);
  static_assert(std::is_same_v<PopFrontT<TypeVector<int, void, double>>, TypeVector<void, double>>);

  static_assert(!HasType<PopBack<TypeVector<>>>{});
  static_assert(std::is_same_v<PopBackT<TypeVector<int>>, TypeVector<>>);
  static_assert(std::is_same_v<PopBackT<TypeVector<int, void>>, TypeVector<int>>);
  static_assert(std::is_same_v<PopBackT<TypeVector<int, void, double>>, TypeVector<int, void>>);
}

void TestConcatenate() {
  static_assert(std::is_same_v<ConcatenateT<TypeVector<>, TypeVector<>>, TypeVector<>>);
  static_assert(std::is_same_v<ConcatenateT<TypeVector<>, TypeVector<int>>, TypeVector<int>>);
  static_assert(std::is_same_v<ConcatenateT<TypeVector<int>, TypeVector<>>, TypeVector<int>>);
  static_assert(std::is_same_v<ConcatenateT<TypeVector<int>, TypeVector<void>>, TypeVector<int, void>>);
  static_assert(std::is_same_v<ConcatenateT<TypeVector<int, void>, TypeVector<double>>, TypeVector<int, void, double>>);
  static_assert(
      std::is_same_v<ConcatenateT<TypeVector<int, void>, TypeVector<double, int>>, TypeVector<int, void, double, int>>);
}

#ifdef ALGORITHMS_IMPLEMENTED

void TestInsert() {
  static_assert(!HasType<Insert<TypeVector<>, 1, int>>{});
  static_assert(!HasType<Insert<TypeVector<int, void>, 3, double>>{});
  static_assert(std::is_same_v<InsertT<TypeVector<>, 0, int>, TypeVector<int>>);
  static_assert(std::is_same_v<InsertT<TypeVector<int>, 0, void>, TypeVector<void, int>>);
  static_assert(std::is_same_v<InsertT<TypeVector<int>, 1, void>, TypeVector<int, void>>);
  static_assert(std::is_same_v<InsertT<TypeVector<int, void>, 0, double>, TypeVector<double, int, void>>);
  static_assert(std::is_same_v<InsertT<TypeVector<int, void>, 1, double>, TypeVector<int, double, void>>);
  static_assert(std::is_same_v<InsertT<TypeVector<int, void>, 2, double>, TypeVector<int, void, double>>);
  static_assert(
      std::is_same_v<InsertT<TypeVector<int, int, int, int, int>, 3, void>, TypeVector<int, int, int, void, int, int>>);
}

void TestEraseFirst() {
  static_assert(std::is_same_v<EraseFirstT<TypeVector<>, int>, TypeVector<>>);
  static_assert(std::is_same_v<EraseFirstT<TypeVector<int>, int>, TypeVector<>>);
  static_assert(std::is_same_v<EraseFirstT<TypeVector<int, void>, int>, TypeVector<void>>);
  static_assert(std::is_same_v<EraseFirstT<TypeVector<int, void>, void>, TypeVector<int>>);
  static_assert(std::is_same_v<EraseFirstT<TypeVector<int, void, double>, int>, TypeVector<void, double>>);
  static_assert(std::is_same_v<EraseFirstT<TypeVector<int, void, double>, void>, TypeVector<int, double>>);
  static_assert(std::is_same_v<EraseFirstT<TypeVector<int, void, double>, double>, TypeVector<int, void>>);
  static_assert(std::is_same_v<EraseFirstT<TypeVector<int, int, double>, int>, TypeVector<int, double>>);
  static_assert(std::is_same_v<EraseFirstT<TypeVector<int, void, int>, int>, TypeVector<void, int>>);
  static_assert(std::is_same_v<EraseFirstT<TypeVector<double, int, int>, int>, TypeVector<double, int>>);
  static_assert(std::is_same_v<EraseFirstT<TypeVector<int, int, int>, int>, TypeVector<int, int>>);
  static_assert(std::is_same_v<EraseFirstT<TypeVector<int, int*, int&, int, int[], const int, int, int[1], int>, int>,
                               TypeVector<int*, int&, int, int[], const int, int, int[1], int>>);
}

void TestEraseAll() {
  static_assert(std::is_same_v<EraseAllT<TypeVector<>, int>, TypeVector<>>);
  static_assert(std::is_same_v<EraseAllT<TypeVector<int>, int>, TypeVector<>>);
  static_assert(std::is_same_v<EraseAllT<TypeVector<int, void>, int>, TypeVector<void>>);
  static_assert(std::is_same_v<EraseAllT<TypeVector<int, void>, void>, TypeVector<int>>);
  static_assert(std::is_same_v<EraseAllT<TypeVector<int, void, double>, int>, TypeVector<void, double>>);
  static_assert(std::is_same_v<EraseAllT<TypeVector<int, void, double>, void>, TypeVector<int, double>>);
  static_assert(std::is_same_v<EraseAllT<TypeVector<int, void, double>, double>, TypeVector<int, void>>);
  static_assert(std::is_same_v<EraseAllT<TypeVector<int, int, double>, int>, TypeVector<double>>);
  static_assert(std::is_same_v<EraseAllT<TypeVector<int, void, int>, int>, TypeVector<void>>);
  static_assert(std::is_same_v<EraseAllT<TypeVector<double, int, int>, int>, TypeVector<double>>);
  static_assert(std::is_same_v<EraseAllT<TypeVector<int, int, int>, int>, TypeVector<>>);
  static_assert(std::is_same_v<EraseAllT<TypeVector<int, int*, int&, int, int[], const int, int, int[1], int>, int>,
                               TypeVector<int*, int&, int[], const int, int[1]>>);
}

void TestReverse() {
  static_assert(std::is_same_v<ReverseT<TypeVector<>>, TypeVector<>>);
  static_assert(std::is_same_v<ReverseT<TypeVector<int>>, TypeVector<int>>);
  static_assert(std::is_same_v<ReverseT<TypeVector<int, void>>, TypeVector<void, int>>);
  static_assert(std::is_same_v<ReverseT<TypeVector<int, void, double>>, TypeVector<double, void, int>>);
  static_assert(std::is_same_v<ReverseT<TypeVector<int, void, double, char>>, TypeVector<char, double, void, int>>);
}

void TestUnique() {
  static_assert(std::is_same_v<UniqueT<TypeVector<>>, TypeVector<>>);
  static_assert(std::is_same_v<UniqueT<TypeVector<int>>, TypeVector<int>>);
  static_assert(std::is_same_v<UniqueT<TypeVector<int, void>>, TypeVector<int, void>>);
  static_assert(std::is_same_v<UniqueT<TypeVector<int, void, double>>, TypeVector<int, void, double>>);
  static_assert(std::is_same_v<UniqueT<TypeVector<int, void, double, char>>, TypeVector<int, void, double, char>>);
  static_assert(std::is_same_v<UniqueT<TypeVector<int, int, int, int>>, TypeVector<int>>);
  static_assert(std::is_same_v<UniqueT<TypeVector<char, int, void, void, int, char>>, TypeVector<char, int, void>>);
}

void TestTransform() {
  static_assert(std::is_same_v<TransformT<TypeVector<>, std::add_pointer_t>, TypeVector<>>);
  static_assert(std::is_same_v<TransformT<TypeVector<int>, std::add_pointer_t>, TypeVector<int*>>);
  static_assert(std::is_same_v<TransformT<TypeVector<int, void>, std::add_pointer_t>, TypeVector<int*, void*>>);
  static_assert(std::is_same_v<TransformT<TypeVector<int*, void, double>, std::add_pointer_t>,
                               TypeVector<int**, void*, double*>>);
  static_assert(std::is_same_v<TransformT<TypeVector<int**, void*, double*, const char*>, std::remove_pointer_t>,
                               TypeVector<int*, void, double, const char>>);
}

void TestAllOf() {
  static_assert(kAllOfV<TypeVector<>, std::is_pointer>);
  static_assert(kAllOfV<TypeVector<int*>, std::is_pointer>);
  static_assert(!kAllOfV<TypeVector<int, void*>, std::is_pointer>);
  static_assert(kAllOfV<TypeVector<int*, void*, double*>, std::is_pointer>);
  static_assert(!kAllOfV<TypeVector<int, void, double, const char>, std::is_pointer>);
}

void TestAnyOf() {
  static_assert(!kAnyOfV<TypeVector<>, std::is_pointer>);
  static_assert(kAnyOfV<TypeVector<int*>, std::is_pointer>);
  static_assert(kAnyOfV<TypeVector<int, void*>, std::is_pointer>);
  static_assert(kAnyOfV<TypeVector<int*, void*, double*>, std::is_pointer>);
  static_assert(!kAnyOfV<TypeVector<int, void, double, const char>, std::is_pointer>);
}

#endif  // ALGORITHMS_IMPLEMENTED

#ifdef SORT_IMPLEMENTED

struct A {};
struct B : A {};
struct C : B {};
struct D : C {};

template <class T, class U>
struct SizeofLess : std::bool_constant<sizeof(T) < sizeof(U)> {};

void TestMinElement() {
  static_assert(!HasType<MinElement<TypeVector<>, std::is_base_of>>{});
  static_assert(std::is_same_v<MinElementT<TypeVector<A>, std::is_base_of>, A>);
  static_assert(std::is_same_v<MinElementT<TypeVector<B, A>, std::is_base_of>, A>);
  static_assert(std::is_same_v<MinElementT<TypeVector<A, C, B>, std::is_base_of>, A>);
  static_assert(std::is_same_v<MinElementT<TypeVector<A, B, C, D>, std::is_base_of>, A>);
  static_assert(std::is_same_v<MinElementT<TypeVector<D, C, B, A>, std::is_base_of>, A>);
  static_assert(std::is_same_v<MinElementT<TypeVector<D, C, B, A, A, B, C, D>, std::is_base_of>, A>);

  static_assert(std::is_same_v<MinElementT<TypeVector<int32_t, int64_t, int8_t, int16_t>, SizeofLess>, int8_t>);
}

void TestMaxElement() {
  static_assert(!HasType<MaxElement<TypeVector<>, std::is_base_of>>{});
  static_assert(std::is_same_v<MaxElementT<TypeVector<A>, std::is_base_of>, A>);
  static_assert(std::is_same_v<MaxElementT<TypeVector<B, A>, std::is_base_of>, B>);
  static_assert(std::is_same_v<MaxElementT<TypeVector<A, C, B>, std::is_base_of>, C>);
  static_assert(std::is_same_v<MaxElementT<TypeVector<A, B, C, D>, std::is_base_of>, D>);
  static_assert(std::is_same_v<MaxElementT<TypeVector<D, C, B, A>, std::is_base_of>, D>);
  static_assert(std::is_same_v<MaxElementT<TypeVector<D, C, B, A, A, B, C, D>, std::is_base_of>, D>);

  static_assert(std::is_same_v<MaxElementT<TypeVector<int32_t, int64_t, int8_t, int16_t>, SizeofLess>, int64_t>);
}

void TestMerge() {
  static_assert(std::is_same_v<MergeT<TypeVector<>, TypeVector<>, std::is_base_of>, TypeVector<>>);
  static_assert(std::is_same_v<MergeT<TypeVector<>, TypeVector<A>, std::is_base_of>, TypeVector<A>>);
  static_assert(std::is_same_v<MergeT<TypeVector<A>, TypeVector<>, std::is_base_of>, TypeVector<A>>);
  static_assert(std::is_same_v<MergeT<TypeVector<A>, TypeVector<B>, std::is_base_of>, TypeVector<A, B>>);
  static_assert(std::is_same_v<MergeT<TypeVector<A, B>, TypeVector<A, B>, std::is_base_of>, TypeVector<A, A, B, B>>);
  static_assert(std::is_same_v<MergeT<TypeVector<A, C>, TypeVector<B, D>, std::is_base_of>, TypeVector<A, B, C, D>>);
  static_assert(std::is_same_v<MergeT<TypeVector<A, C, D>, TypeVector<B>, std::is_base_of>, TypeVector<A, B, C, D>>);
  static_assert(
      std::is_same_v<MergeT<TypeVector<A, A, C>, TypeVector<B, B>, std::is_base_of>, TypeVector<A, A, B, B, C>>);
  static_assert(
      std::is_same_v<MergeT<TypeVector<A, B, C, D>, TypeVector<A>, std::is_base_of>, TypeVector<A, A, B, C, D>>);
}

void TestSort() {
  static_assert(std::is_same_v<SortT<TypeVector<>, std::is_base_of>, TypeVector<>>);
  static_assert(std::is_same_v<SortT<TypeVector<A>, std::is_base_of>, TypeVector<A>>);
  static_assert(std::is_same_v<SortT<TypeVector<B, A>, std::is_base_of>, TypeVector<A, B>>);
  static_assert(std::is_same_v<SortT<TypeVector<A, C, B>, std::is_base_of>, TypeVector<A, B, C>>);
  static_assert(std::is_same_v<SortT<TypeVector<A, B, C, D>, std::is_base_of>, TypeVector<A, B, C, D>>);
  static_assert(std::is_same_v<SortT<TypeVector<D, C, B, A>, std::is_base_of>, TypeVector<A, B, C, D>>);
  static_assert(
      std::is_same_v<SortT<TypeVector<D, C, B, A, A, B, C, D>, std::is_base_of>, TypeVector<A, A, B, B, C, C, D, D>>);

  static_assert(std::is_same_v<SortT<TypeVector<int32_t, int64_t, int8_t, int16_t>, SizeofLess>,
                               TypeVector<int8_t, int16_t, int32_t, int64_t>>);
}

#endif  // SORT_IMPLEMENTED

int main() {
}
