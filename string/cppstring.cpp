#include "cppstring.h"

String::String() : buffer_(nullptr), size_(0), capacity_(0) {
}

String::String(size_t size, char symbol) {
  size_ = size;
  capacity_ = size_;
  if (size) {
    buffer_ = new char[size];
    for (size_t i = 0; i < size_; i++) {
      buffer_[i] = symbol;
    }
  } else {
    buffer_ = nullptr;
  }
}

String::String(const char* string) {
  size_ = strlen(string);
  capacity_ = size_;
  if (size_) {
    buffer_ = new char[size_];
    strncpy(buffer_, string, size_);
  } else {
    buffer_ = nullptr;
  }
};

String::String(const char* string, int size) {
  size_ = size;
  capacity_ = size_;
  if (size_) {
    buffer_ = new char[size_];
    strncpy(buffer_, string, size_);
  } else {
    buffer_ = nullptr;
  }
};

String::~String() {
  if (capacity_) {
    delete[] buffer_;
  }
};

String::String(const String& other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  if (capacity_) {
    buffer_ = new char[capacity_];
    strncpy(buffer_, other.buffer_, size_);
  } else {
    buffer_ = nullptr;
  }
};

String& String::operator=(const String& other) {
  if (*this != other) {
    if (other.capacity_) {
      if (other.size_ > capacity_) {
        delete[] buffer_;
        buffer_ = new char[other.size_];
        capacity_ = other.size_;
      }
      strncpy(buffer_, other.buffer_, other.size_);
      size_ = other.size_;
    } else {
      String::~String();
      buffer_ = nullptr;
      size_ = other.size_;
      capacity_ = size_;
    }
  }
  return *this;
};

const char& String::operator[](size_t i) const {
  return buffer_[i];
};

char& String::operator[](size_t i) {
  return buffer_[i];
};

const char& String::At(size_t i) const {
  if (i >= size_) {
    throw StringOutOfRange{};
  }
  return buffer_[i];
};

char& String::At(size_t i) {
  if (i >= size_) {
    throw StringOutOfRange{};
  }
  return buffer_[i];
};

const char& String::Front() const {
  return buffer_[0];
};

char& String::Front() {
  return buffer_[0];
};

const char& String::Back() const {
  return buffer_[size_ - 1];
};

char& String::Back() {
  return buffer_[size_ - 1];
};

const char* String::CStr() const {
  return buffer_;
};

char* String::CStr() {
  return buffer_;
};

const char* String::Data() const {
  return buffer_;
};

char* String::Data() {
  return buffer_;
};

bool String::Empty() const {
  return size_ == 0;
};

size_t String::Size() const {
  return size_;
};

size_t String::Length() const {
  return size_;
};

size_t String::Capacity() const {
  return capacity_;
};

void String::Clear() {
  size_ = 0;
};

void String::Swap(String& other) {
  String temp;
  temp = *this;
  *this = other;
  other = temp;
};

void String::PopBack() {
  if (size_) {
    size_ -= 1;
  }
};

void String::PushBack(char symbol) {
  if (capacity_) {
    if (size_ >= capacity_) {
      char* temp = new char[2 * capacity_];
      strncpy(temp, buffer_, size_);
      delete[] buffer_;
      buffer_ = temp;
      capacity_ = 2 * size_;
    }
    buffer_[size_] = symbol;
    ++size_;
  } else {
    buffer_ = new char[1];
    buffer_[0] = symbol;
    size_ = 1;
    capacity_ = 1;
  }
};

String& operator+=(String& left, String right) {
  for (size_t i = 0; i < right.size_; i++) {
    left.PushBack(right[i]);
  }
  return left;
};

void String::Resize(size_t new_size, char symbol) {
  if (capacity_ == 0) {
    buffer_ = new char[new_size];
    capacity_ = new_size;
  } else if (new_size > capacity_) {
    char* temp = new char[new_size];
    strncpy(temp, buffer_, size_);
    delete[] buffer_;
    buffer_ = temp;
    capacity_ = new_size;
  }
  for (size_t i = size_; i < new_size; ++i) {
    buffer_[i] = symbol;
  }
  size_ = new_size;
};

void String::Reserve(size_t new_capacity) {
  if (capacity_ == 0) {
    buffer_ = new char[new_capacity];
    capacity_ = new_capacity;
  } else if (capacity_ < new_capacity) {
    char* temp = new char[capacity_];
    strncpy(temp, buffer_, size_);
    delete[] buffer_;
    buffer_ = temp;
    capacity_ = new_capacity;
  }
};

void String::ShrinkToFit() {
  if (capacity_) {
    char* temp = new char[size_];
    strncpy(temp, buffer_, size_);
    delete[] buffer_;
    buffer_ = temp;
    capacity_ = size_;
  }
};

String operator+(String left, String right) {
  if (left.size_ + right.size_ == 0) {
    return {};
  }
  String result;
  char* new_string = new char[left.size_ + right.size_];
  if (right.size_ && left.size_) {
    strncpy(new_string, left.buffer_, left.size_);
    for (size_t i = left.size_; i < left.size_ + right.size_; i++) {
      new_string[i] = right.buffer_[i - left.size_];
    }
  } else if (left.size_) {
    strncpy(new_string, left.buffer_, left.size_);
  } else {
    strncpy(new_string, right.buffer_, right.size_);
  }
  result.buffer_ = new_string;
  result.size_ = left.size_ + right.size_;
  result.capacity_ = result.size_;
  return result;
};

bool operator==(String left, String right) {
  if (left.size_ != right.size_) {
    return false;
  }
  for (size_t i = 0; i < left.size_; i++) {
    if (left[i] != right[i]) {
      return false;
    }
  }
  return true;
};

bool operator!=(String left, String right) {
  return !(left == right);
};

bool operator<(String left, String right) {
  for (size_t i = 0; i < std::min(left.size_, right.size_); i++) {
    if (left.buffer_[i] == right.buffer_[i]) {
      continue;
    }
    return left.buffer_[i] < right.buffer_[i];
  }
  return left.size_ < right.size_;
};

bool operator<=(String left, String right) {
  return (left < right) || (left == right);
};

bool operator>(String left, String right) {
  return ! (left < right) && ! (left == right);
};

bool operator>=(String left, String right) {
  return ! (left < right);
};

std::ostream& operator<<(std::ostream& os, const String& string) {
  for (size_t i = 0; i < string.size_; i++) {
    os << string.buffer_[i];
  }
  return os;
};