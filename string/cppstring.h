#pragma once

#include <cstring>
#include <iostream>
#include "stddef.h"
#include <stdexcept>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
  char* buffer_;
  size_t size_;
  size_t capacity_;

 public:
  String();
  String(size_t size, char symbol);
  String(const char* string);  // NOLINT
  String(const char* string, int size);
  ~String();
  String(const String& other);
  String& operator=(const String& other);
  const char& operator[](size_t i) const;
  char& operator[](size_t i);
  const char& At(size_t i) const;
  char& At(size_t i);
  const char& Front() const;
  char& Front();
  const char& Back() const;
  char& Back();
  const char* CStr() const;
  char* CStr();
  const char* Data() const;
  char* Data();
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String& other);
  void PopBack();
  void PushBack(char symbol);
  friend String& operator+=(String& left, String right);
  void Resize(size_t new_size, char symbol);
  void Reserve(size_t new_capacity);
  void ShrinkToFit();
  friend String operator+(String left, String right);
  friend bool operator==(String left, String right);
  friend bool operator!=(String left, String right);
  friend bool operator<(String left, String right);
  friend bool operator<=(String left, String right);
  friend bool operator>(String left, String right);
  friend bool operator>=(String left, String right);
  friend std::ostream& operator<<(std::ostream& os, const String& string);
};
