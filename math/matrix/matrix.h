#ifndef MATH_MATRIX_MATRIX_H_
#define MATH_MATRIX_MATRIX_H_

#include <string.h>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>

namespace math {

typedef float MatrixValue;

template <std::size_t Len>
struct MatrixRow {
 public:
  template <typename... Args>
  MatrixRow(Args... args) {
    static_assert(Len != 0, "Row size cannot be 0");

    constexpr std::size_t args_number = sizeof...(args);
    static_assert(
        args_number == Len,
        "Wrong initializer args number for MatrixRow of given length");

    Init(mem_, args...);
  }

  std::string ToString() {
    std::stringstream ss;
    ss << "[ ";
    for (std::size_t i = 0; i < Len; i++) {
      ss << mem_[i] << " ";
    }
    ss << "]";
    return ss.str();
  }

  const MatrixValue* Data() { return mem_; }

 private:
  void Init(MatrixValue* mem) {}

  template <typename... Args>
  void Init(MatrixValue* mem, float val, Args... args) {
    *mem = val;
    Init(mem + 1, args...);
  }

  MatrixValue mem_[Len];
};

template <std::size_t Rows, std::size_t Cols>
class Matrix {
 public:
  template <typename... Args>
  Matrix(Args... rows) {
    static_assert(Rows != 0 && Cols != 0, "Matrix dimension sizes cannot be 0");
    constexpr std::size_t rows_count = sizeof...(rows);
    static_assert(rows_count == Rows,
                  "Wrong number of rows for the given matrix");

    Init(0, rows...);
  }

  Matrix() { memset(mem_, 0, sizeof(MatrixValue) * Rows * Cols); }

  std::string ToString() {
    std::stringstream ss;
    ss << "[\n";
    for (std::size_t row_idx = 0; row_idx < Rows; row_idx++) {
      ss << "  ";
      for (std::size_t col_idx = 0; col_idx < Cols; col_idx++) {
        ss << GetRowPtr(row_idx)[col_idx] << "  ";
      }
      ss << "\n";
    }
    ss << "]";

    return ss.str();
  }

  std::size_t GetRows() const { return Rows; }

  std::size_t GetCols() const { return Cols; }

  MatrixValue& Val(std::size_t row_idx, std::size_t col_idx) {
    assert(row_idx < Rows && col_idx < Cols);
    return GetRowPtr(row_idx)[col_idx];
  }

  const MatrixValue& Val(std::size_t row_idx, std::size_t col_idx) const {
    assert(row_idx < Rows && col_idx < Cols);
    return GetRowPtr(row_idx)[col_idx];
  }

  Matrix<Rows, Cols> operator+(const Matrix<Rows, Cols>& b) const {
    Matrix<Rows, Cols> result;

    for (size_t row_idx = 0; row_idx < Rows; row_idx++) {
      for (size_t col_idx = 0; col_idx < Cols; col_idx++) {
        result.GetRowPtr(row_idx)[col_idx] =
            this->GetRowPtr(row_idx)[col_idx] + b.GetRowPtr(row_idx)[col_idx];
      }
    }

    return result;
  }

  template <std::size_t RowsB, std::size_t ColsB>
  bool operator==(const Matrix<RowsB, ColsB>& b) const {
    if (Rows != RowsB || Cols != ColsB) {
      return false;
    }

    for (std::size_t row = 0; row < Rows; row++) {
      for (std::size_t col = 0; col < Cols; col++) {
        if (GetRowPtr(row)[col] != b.Val(row, col)) {
          return false;
        }
      }
    }

    return true;
  }

  Matrix<Cols, Rows> Transpose() {
    Matrix<Cols, Rows> result;

    for (std::size_t row = 0; row < Rows; row++) {
      for (std::size_t col = 0; col < Cols; col++) {
        result.Val(col, row) = GetRowPtr(row)[col];
      }
    }

    return result;
  }

 private:
  template <std::size_t RowsA,
            std::size_t ColsA,
            std::size_t RowsB,
            std::size_t ColsB>
  friend Matrix<RowsA, ColsB> Mul(const Matrix<RowsA, ColsA>& a,
                                  const Matrix<RowsB, ColsB>& b);

  void Init(std::size_t row_index) { assert(row_index == Rows); }

  template <typename... Args>
  void Init(std::size_t row_index, MatrixRow<Cols>& row, Args... args) {
    assert(row_index < Rows);

    memcpy(GetRowPtr(row_index), row.Data(), sizeof(MatrixValue) * Cols);

    Init(row_index + 1, args...);
  }

  MatrixValue* GetRowPtr(std::size_t row_idx) {
    assert(row_idx < Rows);
    return &mem_[row_idx * Cols];
  }

  const MatrixValue* GetRowPtr(std::size_t row_idx) const {
    assert(row_idx < Rows);
    return &mem_[row_idx * Cols];
  }

  MatrixValue mem_[Rows * Cols];
};

template <std::size_t RowsA,
          std::size_t ColsA,
          std::size_t RowsB,
          std::size_t ColsB>
Matrix<RowsA, ColsB> Mul(const Matrix<RowsA, ColsA>& a,
                         const Matrix<RowsB, ColsB>& b) {
  static_assert(ColsA == RowsB,
                "When multiplying, first matrix columns number "
                "must be equal to second matrix rows number");

  Matrix<RowsA, ColsB> result;

  for (size_t row_a = 0; row_a < RowsA; row_a++) {
    for (size_t col_b = 0; col_b < ColsB; col_b++) {
      result.GetRowPtr(row_a)[col_b] = 0;
      // Multiply row of matrix A by column of matrix B
      for (size_t idx = 0; idx < ColsA; idx++) {
        result.GetRowPtr(row_a)[col_b] +=
            a.GetRowPtr(row_a)[idx] * b.GetRowPtr(idx)[col_b];
      }
    }
  }

  return result;
}

typedef Matrix<3, 3> Matrix3;
typedef Matrix<3, 1> Column3;
typedef Matrix<1, 3> Row3;

}  // namespace math

#endif  // MATH_MATRIX_MATRIX_H_
