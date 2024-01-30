#pragma once
#include <iostream>
#include <cstdint>
#include <stdexcept>

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, size_t R, size_t C>
class Matrix {
 public:
  T array[R][C];
  T &operator()(size_t r, size_t c) {
    return array[r][c];
  }
  T &At(size_t r, size_t c) {
    if (r >= R || c >= C) {
      throw MatrixOutOfRange{};
    }
    return array[r][c];
  }
  size_t RowsNumber() const {
    return R;
  }
  size_t ColumnsNumber() const {
    return C;
  }
  T operator()(size_t r, size_t c) const {
    return array[r][c];
  }
  T At(size_t r, size_t c) const {
    if (r >= R || c >= C) {
      throw MatrixOutOfRange{};
    }
    return array[r][c];
  }
};

template <class T, size_t R, size_t C>
Matrix<T, C, R> GetTransposed(const Matrix<T, R, C> &a) {
  Matrix<T, C, R> b;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      b(j, i) = a(i, j);
    }
  }
  return b;
}

template <class T, size_t R, size_t C>
Matrix<T, R, C> operator+(const Matrix<T, R, C> &a, const Matrix<T, R, C> &b) {
  Matrix<T, R, C> c;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      c(i, j) = a(i, j) + b(i, j);
    }
  }
  return c;
}

template <class T, size_t R, size_t C>
Matrix<T, R, C> operator-(const Matrix<T, R, C> &a, const Matrix<T, R, C> &b) {
  Matrix<T, R, C> c;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      c(i, j) = a(i, j) - b(i, j);
    }
  }
  return c;
}

template <class T, size_t R, size_t C, size_t O, class U>
Matrix<T, R, O> operator*(const Matrix<T, R, C> &a, const Matrix<U, C, O> &b) {
  Matrix<T, R, O> c;
  T s = 0;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < O; ++j) {
      for (size_t k = 0; k < C; ++k) {
        s += a(i, k) * b(k, j);
      }
      c(i, j) = s;
      s = 0;
    }
  }
  return c;
}

template <class T, size_t R, size_t C, class U>
Matrix<T, R, C> operator*(const Matrix<T, R, C> &a, U b) {
  Matrix<T, R, C> c = a;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      c(i, j) *= b;
    }
  }
  return c;
}

template <class T, size_t R, size_t C, class U>
Matrix<T, R, C> operator*(U b, const Matrix<T, R, C> &a) {
  Matrix<T, R, C> c = a;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      c(i, j) *= b;
    }
  }
  return c;
}

template <class T, size_t R, size_t C, class U>
Matrix<T, R, C> operator/(const Matrix<T, R, C> &a, U b) {
  Matrix<T, R, C> c;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      c(i, j) = a(i, j) / b;
    }
  }
  return c;
}

template <class T, size_t R, size_t C, class U>
Matrix<T, R, C> &operator*=(Matrix<T, R, C> &a, U b) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      a(i, j) *= b;
    }
  }
  return a;
}

template <class T, size_t R, size_t C>
Matrix<T, R, C> &operator+=(Matrix<T, R, C> &a, Matrix<T, R, C> b) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      a(i, j) += b(i, j);
    }
  }
  return a;
}

template <class T, size_t R, size_t C>
Matrix<T, R, C> &operator-=(Matrix<T, R, C> &a, Matrix<T, R, C> b) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      a(i, j) -= b(i, j);
    }
  }
  return a;
}

template <class T, size_t R, size_t C, class U>
Matrix<T, R, C> &operator*=(Matrix<T, R, C> &a, Matrix<U, C, C> b) {
  a = a * b;
  return a;
}

template <class T, size_t R, size_t C, class U>
Matrix<T, R, C> &operator/=(Matrix<T, R, C> &a, U b) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      a(i, j) = a(i, j) / b;
    }
  }
  return a;
}

template <class T, size_t R, size_t C>
bool operator==(const Matrix<T, R, C> &a, const Matrix<T, R, C> &b) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      if (a(i, j) != b(i, j)) {
        return false;
      }
    }
  }
  return true;
}

template <class T, size_t R, size_t C>
bool operator!=(const Matrix<T, R, C> &a, const Matrix<T, R, C> &b) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      if (a(i, j) != b(i, j)) {
        return true;
      }
    }
  }
  return false;
}

template <class T, size_t R, size_t C>
std::ostream &operator<<(std::ostream &os, Matrix<T, R, C> a) {
  for (size_t i = 0; i < R; ++i) {
    size_t j = 0;
    for (; j < C - 1; ++j) {
      os << a(i, j) << ' ';
    }
    os << a(i, j);
    os << '\n';
  }
  return os;
}

template <class T, size_t R, size_t C>
std::istream &operator>>(std::istream &is, Matrix<T, R, C> &a) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      is >> a(i, j);
    }
  }
  return is;
}