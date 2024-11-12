#pragma once

#include <string>
#include <variant>
#include <vector>

struct NumberToken {
  int64_t value;

  explicit NumberToken(int64_t valuee) : value(valuee) {
  }
};

struct UnknownToken {
  std::string value;

  explicit UnknownToken(std::string value_) : value(value_) {
  }
};

struct PlusToken {};
struct MinusToken {};
struct MultiplyToken {};
struct DivideToken {};
struct MinToken {};
struct MaxToken {};
struct AbsToken {};
struct ResidualToken {};
struct SqrToken {};
struct OpeningBracketToken {};
struct ClosingBracketToken {};
struct VariableToken {};

using Token = std::variant<NumberToken, UnknownToken, PlusToken, MinusToken, MultiplyToken, DivideToken, MinToken,
                           MaxToken, AbsToken, ResidualToken, SqrToken, OpeningBracketToken, ClosingBracketToken, VariableToken>;

template <typename T>
inline bool operator==(T, T) {
  if (std::is_same<T, PlusToken>::value) {
    return true;
  }

  if (std::is_same<T, MinusToken>::value) {
    return true;
  }

  if (std::is_same<T, MultiplyToken>::value) {
    return true;
  }

  if (std::is_same<T, DivideToken>::value) {
    return true;
  }

  if (std::is_same<T, MinToken>::value) {
    return true;
  }

  if (std::is_same<T, MaxToken>::value) {
    return true;
  }

  if (std::is_same<T, AbsToken>::value) {
    return true;
  }

  if (std::is_same<T, ResidualToken>::value) {
    return true;
  }

  if (std::is_same<T, SqrToken>::value) {
    return true;
  }

  if (std::is_same<T, OpeningBracketToken>::value) {
    return true;
  }

  if (std::is_same<T, ClosingBracketToken>::value) {
    return true;
  }

  if (std::is_same<T, VariableToken>::value) {
    return true;
  }

  return false;
}

inline bool operator==(const NumberToken& lhs, const NumberToken& rhs) {
  return lhs.value == rhs.value;
}

inline bool operator==(const UnknownToken& lhs, const UnknownToken& rhs) {
  return lhs.value == rhs.value;
}

std::vector<Token> Tokenize(std::string_view str);
