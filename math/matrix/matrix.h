#ifndef MATH_MATRIX_MATRIX_H_
#define MATH_MATRIX_MATRIX_H_

namespace math {

template<int Rows, int Cols>
class Matrix {
 public:

 private:
  float mem_[Rows * Cols];
};

}  // namespace math

#endif  // MATH_MATRIX_MATRIX_H_