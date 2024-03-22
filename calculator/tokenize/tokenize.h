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

  explicit UnknownToken(std::string valuee) : value(valuee) {
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

using Token = std::variant<NumberToken, UnknownToken, PlusToken, MinusToken, MultiplyToken, DivideToken, MinToken,
                           MaxToken, AbsToken, ResidualToken, SqrToken, OpeningBracketToken, ClosingBracketToken>;

inline bool operator==(PlusToken, PlusToken) {
  return true;
}

inline bool operator==(MinusToken, MinusToken) {
  return true;
}

inline bool operator==(MultiplyToken, MultiplyToken) {
  return true;
}

inline bool operator==(DivideToken, DivideToken) {
  return true;
}

inline bool operator==(MinToken, MinToken) {
  return true;
}

inline bool operator==(MaxToken, MaxToken) {
  return true;
}

inline bool operator==(AbsToken, AbsToken) {
  return true;
}

inline bool operator==(ResidualToken, ResidualToken) {
  return true;
}

inline bool operator==(SqrToken, SqrToken) {
  return true;
}

inline bool operator==(OpeningBracketToken, OpeningBracketToken) {
  return true;
}

inline bool operator==(ClosingBracketToken, ClosingBracketToken) {
  return true;
}

inline bool operator==(NumberToken lhs, NumberToken rhs) {
  return lhs.value == rhs.value;
}

inline bool operator==(const UnknownToken& lhs, const UnknownToken& rhs) {
  return lhs.value == rhs.value;
}

std::vector<Token> Tokenize(std::string_view str);
