#pragma once

#include <stdexcept>
#include <string>

#include "../tokenize/tokenize.h"
#include "expressions.h"

class UnknownSymbolError : public std::runtime_error {
 public:
  explicit UnknownSymbolError(const std::string& symbol = "")
      : std::runtime_error("UnknownSymbolError: " + symbol) {}
};

class WrongExpressionError : public std::runtime_error {
 public:
  explicit WrongExpressionError(const std::string& msg = "")
      : std::runtime_error("WrongExpressionError: " + msg) {}
};

int CalculatePolishNotation(std::string_view input);

std::unique_ptr<IExpression> ParsePolishNotation(const std::vector<Token>& tokens,
                                                 size_t& pos);

