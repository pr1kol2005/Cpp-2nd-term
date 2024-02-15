#pragma once

#include <cstddef>
#include <cstring>
#include <iostream>

class StringView {
  const char* begin_;
  size_t length_;

 public:
  StringView();
  StringView(const char* str);  // NOLINT
  StringView(const char* str, size_t size);
  const char& operator[](size_t index) const;
  const char& Front() const;
  const char& Back() const;
  size_t Size() const;
  size_t Length() const;
  bool Empty() const;
  const char* Data() const;
  void Swap(StringView& object);
  void RemovePrefix(size_t prefix_size);
  void RemoveSuffix(size_t suffix_size);
  StringView Substr(size_t pos, size_t count = -1) const;
};
