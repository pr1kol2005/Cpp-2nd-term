#define REVERSE_RANGE_IMPLEMENTED
#pragma once

#include <iostream>
#include <iterator>

class Range {
  int from_;
  int to_;
  int step_;

 public:
  class Iterator {
   protected:
    int num_;
    int from_;
    int to_;
    int step_;

   public:
    Iterator(int num, Range* seq) : num_(num), from_(seq->from_), to_(seq->to_), step_(seq->step_) {
    }

    Iterator& operator++() {
      num_ += step_;
      return *this;
    }

    Iterator operator++(int) {
      Iterator old_value = *this;
      ++(*this);
      return old_value;
    }

    bool operator==(Iterator other) const {
      return num_ == other.num_;
    }

    bool operator!=(Iterator other) const {
      int64_t sign = (static_cast<int64_t>(to_) - from_) * step_;
      if (sign <= 0) {
        return false;
      }
      if (to_ >= from_) {
        return num_ < other.num_;
      }
      return num_ > other.num_;
    }

    int operator*() {
      return num_;
    }
  };

  class ReverseIterator : public Iterator {
   public:
    ReverseIterator& operator++() {
      num_ -= step_;
      return *this;
    }

    ReverseIterator operator++(int) {
      ReverseIterator old_value = *this;
      ++(*this);
      return old_value;
    }

    bool operator!=(ReverseIterator other) const {
      int64_t sign = (static_cast<int64_t>(to_) - from_) * step_;
      if (sign <= 0) {
        return false;
      }
      if (to_ >= from_) {
        return num_ > other.num_;
      }
      return num_ < other.num_;
    }
  };

  explicit Range(int to) : from_(0), to_(to), step_(1) {
  }

  Range(int from, int to) : from_(from), to_(to), step_(1) {
  }

  Range(int from, int to, int step) : from_(from), to_(to), step_(step) {
  }

  Iterator begin() {  // NOLINT
    return {from_, this};
  }

  Iterator begin() const {  // NOLINT
    return {from_, const_cast<Range*>(this)};
  }

  Iterator end() {  // NOLINT
    return {to_, this};
  }

  Iterator end() const {  // NOLINT
    return {to_, const_cast<Range*>(this)};
  }

  ReverseIterator rbegin() {  // NOLINT
    if (step_) {
      return {
          {(to_ - from_) % step_ == 0 ? to_ - step_ : from_ + (to_ - from_ + step_ - 1) / step_ * step_ - step_, this}};
    }
    return {{0, this}};
  }

  ReverseIterator rbegin() const {  // NOLINT
    if (step_) {
      return {{(to_ - from_) % step_ == 0 ? to_ - step_ : from_ + (to_ - from_ + step_ - 1) / step_ * step_ - step_,
               const_cast<Range*>(this)}};
    }
    return {{0, const_cast<Range*>(this)}};
  }

  ReverseIterator rend() {  // NOLINT
    return {{from_ - step_, this}};
  }

  ReverseIterator rend() const {  // NOLINT
    return {{from_ - step_, const_cast<Range*>(this)}};
  }
};