#include "polish_notation.h"

std::unique_ptr<IExpression> ParsePolishNotation(const std::vector<Token>& tokens,
                                                 size_t& pos) {
  if (pos >= tokens.size()) {
    throw WrongExpressionError("Incorrect operads number");
  }
  Token token = tokens[pos];
  ++pos;
  if (std::holds_alternative<VariableToken>(token)) {
    return std::make_unique<Variable>();
  }
  if (std::holds_alternative<NumberToken>(token)) {
    return std::make_unique<Constant>(std::get<NumberToken>(token).value);
  }
  if (std::holds_alternative<SqrToken>(token)) {
    return std::make_unique<Square>(ParsePolishNotation(tokens, pos));
  }
  if (std::holds_alternative<AbsToken>(token)) {
    return std::make_unique<AbsoluteValue>(ParsePolishNotation(tokens, pos));
  }
  if (std::holds_alternative<PlusToken>(token)) {
    return std::make_unique<Sum>(ParsePolishNotation(tokens, pos),
                                 ParsePolishNotation(tokens, pos));
  }
  if (std::holds_alternative<MinusToken>(token)) {
    return std::make_unique<Subtract>(ParsePolishNotation(tokens, pos),
                                      ParsePolishNotation(tokens, pos));
  }
  if (std::holds_alternative<MultiplyToken>(token)) {
    return std::make_unique<Multiply>(ParsePolishNotation(tokens, pos),
                                      ParsePolishNotation(tokens, pos));
  }
  if (std::holds_alternative<DivideToken>(token)) {
    return std::make_unique<Divide>(ParsePolishNotation(tokens, pos),
                                    ParsePolishNotation(tokens, pos));
  }
  if (std::holds_alternative<MinToken>(token)) {
    return std::make_unique<Minimum>(ParsePolishNotation(tokens, pos),
                                     ParsePolishNotation(tokens, pos));
  }
  if (std::holds_alternative<MaxToken>(token)) {
    return std::make_unique<Maximum>(ParsePolishNotation(tokens, pos),
                                     ParsePolishNotation(tokens, pos));
  }
  if (std::holds_alternative<ResidualToken>(token)) {
    return std::make_unique<Residual>(ParsePolishNotation(tokens, pos),
                                      ParsePolishNotation(tokens, pos));
  }
  throw UnknownSymbolError("Unknown symbol");
}

int CalculatePolishNotation(std::string_view input) {
  std::vector<Token> tokens = Tokenize(input);
  size_t pos = 0;
  auto expression = ParsePolishNotation(tokens, pos);

  if (pos != tokens.size()) {
    throw WrongExpressionError("Incorrect operands number");
  }

  return expression->Calculate();
}
