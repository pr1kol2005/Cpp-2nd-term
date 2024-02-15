#pragma once

#define MATRIX_SQUARE_MATRIX_IMPLEMENTED

#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <typename T, size_t N, size_t M>
class Matrix {
 public:
  T buffer_[N][M];

 public:
  size_t RowsNumber() const {
    return N;
  }

  size_t ColumnsNumber() const {
    return M;
  }

  const T& operator()(size_t i, size_t j) const {
    return buffer_[i][j];
  }

  T& operator()(size_t i, size_t j) {
    return buffer_[i][j];
  }

  const T& At(size_t i, size_t j) const {
    if (i >= N || j >= M) {
      throw MatrixOutOfRange();
    }
    return buffer_[i][j];
  }

  T& At(size_t i, size_t j) {
    if (i >= N || j >= M) {
      throw MatrixOutOfRange();
    }
    return buffer_[i][j];
  }

  Matrix<T, N, M> operator+(Matrix<T, N, M> other) const {
    Matrix<T, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result.buffer_[i][j] = buffer_[i][j] + other.buffer_[i][j];
      }
    }
    return result;
  }

  Matrix<T, N, M> operator-(Matrix<T, N, M> other) const {
    Matrix<T, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result.buffer_[i][j] = buffer_[i][j] - other.buffer_[i][j];
      }
    }
    return result;
  }

  Matrix<T, N, M>& operator+=(Matrix<T, N, M> other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        buffer_[i][j] += other.buffer_[i][j];
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator-=(Matrix<T, N, M> other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        buffer_[i][j] -= other.buffer_[i][j];
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator*=(Matrix<T, M, M> other) {
    Matrix<T, N, M> copy = *this;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        buffer_[i][j] = 0;
        for (size_t k = 0; k < M; ++k) {
          buffer_[i][j] += copy.buffer_[i][k] * other.buffer_[k][j];
        }
      }
    }
    return *this;
  }

  Matrix<T, N, M> operator*(T num) const {
    Matrix<T, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result.buffer_[i][j] = buffer_[i][j] * num;
      }
    }
    return result;
  }

  Matrix<T, N, M> operator/(T num) const {
    Matrix<T, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result.buffer_[i][j] = buffer_[i][j] / num;
      }
    }
    return result;
  }

  Matrix<T, N, M>& operator*=(T num) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        buffer_[i][j] *= num;
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator/=(T num) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        buffer_[i][j] /= num;
      }
    }
    return *this;
  }

  bool operator==(Matrix<T, N, M> other) const {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (buffer_[i][j] != other.buffer_[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(Matrix<T, N, M> other) const {
    return 1 + (*this == other);
  }

  friend std::istream& operator>>(std::istream& is, Matrix<T, N, M>& matrix) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        is >> matrix.buffer_[i][j];
      }
    }
    return is;
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& matrix) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        os << matrix.buffer_[i][j];
        if (j != M - 1) {
          os << ' ';
        }
      }
      os << '\n';
    }
    return os;
  }
};

template <typename T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(Matrix<T, N, M> matrix) {
  Matrix<T, M, N> result;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result.buffer_[j][i] = matrix.buffer_[i][j];
    }
  }
  return result;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> operator*(int num, Matrix<T, N, M> matrix) {
  Matrix<T, N, M> result;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result.buffer_[i][j] = matrix.buffer_[i][j] * num;
    }
  }
  return result;
};

template <typename T, size_t N, size_t M, size_t K>
Matrix<T, N, K> operator*(Matrix<T, N, M> left, Matrix<T, M, K> right) {
  Matrix<T, N, K> result;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < K; ++j) {
      result.buffer_[i][j] = 0;
      for (size_t k = 0; k < M; ++k) {
        result.buffer_[i][j] += left.buffer_[i][k] * right.buffer_[k][j];
      }
    }
  }
  return result;
}

template <typename T, size_t N>
void Transpose(Matrix<T, N, N>& matrix) {
  Matrix<T, N, N> copy = matrix;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix.buffer_[j][i] = copy.buffer_[i][j];
    }
  }
}

template <typename T, size_t N>
T Trace(Matrix<T, N, N> matrix) {
  T result = 0;
  for (size_t i = 0; i < N; ++i) {
    result += matrix.buffer_[i][i];
  }
  return result;
}

template <typename T, size_t N>
Matrix<T, N - 1, N - 1> Minor(Matrix<T, N, N> matrix, size_t row, size_t col) {
  Matrix<T, N - 1, N - 1> minor;
  for (size_t i = 0; i < N - 1; ++i) {
    size_t new_row = (i < row) ? i : i + 1;
    for (size_t j = 0; j < N - 1; ++j) {
      size_t new_col = (j < col) ? j : j + 1;
      minor.buffer_[i][j] = matrix.buffer_[new_row][new_col];
    }
  }
  return minor;
}

template <typename T>
T Determinant(Matrix<T, 1, 1> matrix) {
  return matrix.buffer_[0][0];
}

template <typename T, size_t N>
T Determinant(Matrix<T, N, N> matrix) {
  T result = 0;
  for (size_t i = 0; i < N; ++i) {
    result += std::pow(-1, i % 2) * matrix.buffer_[0][i] * Determinant(Minor(matrix, 0, i));
  }
  return result;
}

template <typename T>
Matrix<T, 1, 1> GetInversed(Matrix<T, 1, 1> matrix) {
  Matrix<T, 1, 1> result;
  result.buffer_[0][0] = 1 / matrix.buffer_[0][0];
  return result;
}

template <typename T, size_t N>
Matrix<T, N, N> GetInversed(Matrix<T, N, N> matrix) {
  if (Determinant(matrix) == 0) {
    throw MatrixIsDegenerateError();
  }
  T det = Determinant(matrix);
  Matrix<T, N, N> adj;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      adj.buffer_[i][j] = std::pow(-1, i % 2) * std::pow(-1, j % 2) * Determinant(Minor(matrix, i, j));
    }
  }
  Transpose(adj);
  adj /= det;
  return adj;
}

template <typename T, size_t N>
void Inverse(Matrix<T, N, N>& matrix) {
  if (Determinant(matrix) == 0) {
    throw MatrixIsDegenerateError();
  }
  Matrix<T, N, N> inv = GetInversed(matrix);
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix.buffer_[i][j] = inv.buffer_[i][j];
    }
  }
}