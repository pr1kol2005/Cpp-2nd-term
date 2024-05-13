#include "ct_prime.h"
#include "ct_prime.h"  // check include guard

int main() {
  static_assert(kSqrtV<0> == 0);
  static_assert(kSqrtV<1> == 1);
  static_assert(kSqrtV<2> == 1);
  static_assert(kSqrtV<3> == 1);
  static_assert(kSqrtV<4> == 2);
  static_assert(kSqrtV<8> == 2);
  static_assert(kSqrtV<9> == 3);
  static_assert(kSqrtV<1'000'000> == 1000);
  static_assert(kSqrtV<2'000'000> == 1414);
  static_assert(kSqrtV<3'000'000> == 1732);
  static_assert(kSqrtV<5'000'000> == 2236);
  static_assert(kSqrtV<10'000'000> == 3162);
  static_assert(kSqrtV<1'000'000'000> == 31622);
  static_assert(kSqrtV<100'000'000'000> == 316227);
  static_assert(kSqrtV<999'999'999'999'999'999> == 999999999);

  static_assert(kHasDivisorOnV<0, 1, 1>);
  static_assert(kHasDivisorOnV<0, 3, 1'000>);
  static_assert(kHasDivisorOnV<1, 1, 1'000>);
  static_assert(!kHasDivisorOnV<1, 3, 1'000>);
  static_assert(!kHasDivisorOnV<2, 3, 1'000>);
  static_assert(kHasDivisorOnV<2, 2, 12'345>);
  static_assert(!kHasDivisorOnV<100, 26, 49>);
  static_assert(!kHasDivisorOnV<100, 51, 99>);
  static_assert(kHasDivisorOnV<100, 26, 75>);
  static_assert(!kHasDivisorOnV<19'999, 2, 6>);
  static_assert(!kHasDivisorOnV<19'999, 8, 2'856>);
  static_assert(!kHasDivisorOnV<19'999, 2'858, 19'998>);
  static_assert(kHasDivisorOnV<19'999, 7, 7>);
  static_assert(kHasDivisorOnV<19'999, 2'857, 2'857>);

  static_assert(!kIsPrimeV<1>);
  static_assert(kIsPrimeV<2>);
  static_assert(kIsPrimeV<3>);
  static_assert(!kIsPrimeV<4>);
  static_assert(kIsPrimeV<5>);
  static_assert(!kIsPrimeV<999'997>);
  static_assert(kIsPrimeV<1'000'003>);
  static_assert(!kIsPrimeV<98'473'967>);
  static_assert(kIsPrimeV<493'543'891>);
  static_assert(!kIsPrimeV<593'543'891>);
}