#pragma once

#include <cmath>

#include "polish_notation.h"

class IExpression {
 public:
  virtual int Calculate() const = 0;

  virtual ~IExpression() = default;
};

class Constant : public IExpression {
 protected:
  int value_;

 public:
  Constant(int value) : value_(value) {}

  int Calculate() const override { return value_; }
};

class Variable : public IExpression {
 protected:
  int value_;
  bool substituted_;

 public:
  Variable() : value_(0), substituted_(false) {}

  void Substitute(int value) {
    value_ = value;
    substituted_ = true;
  }

  int Calculate() const override {
    // if (!substituted_) {
    //   throw UnsubstitutedVariablesError();
    // }
    return value_;
  }
};

class IUnaryOperation : public IExpression {
 protected:
  std::unique_ptr<IExpression> operand_;

 public:
  IUnaryOperation(std::unique_ptr<IExpression> operand)
      : operand_(std::move(operand)) {}

  virtual int Operation(int operand) const = 0;

  int Calculate() const override { return Operation(operand_->Calculate()); }
};

class IBinaryOperation : public IExpression {
 protected:
  std::unique_ptr<IExpression> lhs_;
  std::unique_ptr<IExpression> rhs_;

 public:
  IBinaryOperation(std::unique_ptr<IExpression> lhs,
                   std::unique_ptr<IExpression> rhs)
      : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

  virtual int Operation(int lhs, int rhs) const = 0;

  int Calculate() const override {
    return Operation(lhs_->Calculate(), rhs_->Calculate());
  }
};

class AbsoluteValue : public IUnaryOperation {
 public:
  using IUnaryOperation::IUnaryOperation;

 protected:
  int Operation(int operand) const override { return std::abs(operand); }
};

class Square : public IUnaryOperation {
 public:
  using IUnaryOperation::IUnaryOperation;

 protected:
  int Operation(int operand) const override { return operand * operand; }
};

class Sum : public IBinaryOperation {
 public:
  using IBinaryOperation::IBinaryOperation;

 protected:
  int Operation(int lhs, int rhs) const override { return lhs + rhs; }
};

class Subtract : public IBinaryOperation {
 public:
  using IBinaryOperation::IBinaryOperation;

 protected:
  int Operation(int lhs, int rhs) const override { return lhs - rhs; }
};

class Multiply : public IBinaryOperation {
 public:
  using IBinaryOperation::IBinaryOperation;

 protected:
  int Operation(int lhs, int rhs) const override { return lhs * rhs; }
};

class Divide : public IBinaryOperation {
 public:
  using IBinaryOperation::IBinaryOperation;

 protected:
  int Operation(int lhs, int rhs) const override { return lhs / rhs; }
};

class Residual : public IBinaryOperation {
 public:
  using IBinaryOperation::IBinaryOperation;

 protected:
  int Operation(int lhs, int rhs) const override { return lhs % rhs; }
};

class Minimum : public IBinaryOperation {
 public:
  using IBinaryOperation::IBinaryOperation;

 protected:
  int Operation(int lhs, int rhs) const override { return std::min(lhs, rhs); }
};

class Maximum : public IBinaryOperation {
 public:
  using IBinaryOperation::IBinaryOperation;

 protected:
  int Operation(int lhs, int rhs) const override { return std::max(lhs, rhs); }
};