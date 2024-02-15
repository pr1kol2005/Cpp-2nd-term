#include "string_view.h"

StringView::StringView() : begin_(nullptr), length_(0) {
}

StringView::StringView(const char* str) : begin_(str), length_(std::strlen(str)) {
}

StringView::StringView(const char* str, size_t size) : begin_(str), length_(size) {
}

const char& StringView::operator[](size_t index) const {
  return begin_[index];
}

const char& StringView::Front() const {
  return begin_[0];
}

const char& StringView::Back() const {
  return begin_[length_ - 1];
}

size_t StringView::Size() const {
  return length_;
}

size_t StringView::Length() const {
  return length_;
}

bool StringView::Empty() const {
  return length_ == 0;
}

const char* StringView::Data() const {
  return begin_;
}

void StringView::Swap(StringView& object) {
  auto temp = new StringView(begin_, length_);
  begin_ = object.Data();
  length_ = object.Length();
  object = *temp;
  delete temp;
}

void StringView::RemovePrefix(size_t prefix_size) {
  begin_ += prefix_size;
  length_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  length_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) const {
  size_t sub_str_length = std::min(count, length_ - pos);
  StringView sub_str(begin_ + pos, sub_str_length);
  return sub_str;
}
