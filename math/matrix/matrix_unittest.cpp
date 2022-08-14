#include <gtest/gtest.h>

#include "math/matrix/matrix.h"

TEST(MatrixBasicTest, MatrixConstruct) {
  math::Matrix<3, 3> m(math::MatrixRow<3>(9, 8, 7), math::MatrixRow<3>(6, 5, 4),
                       math::MatrixRow<3>(3, 2, 1));

  ASSERT_EQ(m.Val(0, 0), 9);
  ASSERT_EQ(m.Val(0, 1), 8);
  ASSERT_EQ(m.Val(0, 2), 7);

  ASSERT_EQ(m.Val(1, 0), 6);
  ASSERT_EQ(m.Val(1, 1), 5);
  ASSERT_EQ(m.Val(1, 2), 4);

  ASSERT_EQ(m.Val(2, 0), 3);
  ASSERT_EQ(m.Val(2, 1), 2);
  ASSERT_EQ(m.Val(2, 2), 1);
}

TEST(MatrixBasicTest, MatrixConstructEmpty) {
  math::Matrix<3, 3> m;

  ASSERT_EQ(m.Val(0, 0), 0);
  ASSERT_EQ(m.Val(0, 1), 0);
  ASSERT_EQ(m.Val(0, 2), 0);

  ASSERT_EQ(m.Val(1, 0), 0);
  ASSERT_EQ(m.Val(1, 1), 0);
  ASSERT_EQ(m.Val(1, 2), 0);

  ASSERT_EQ(m.Val(2, 0), 0);
  ASSERT_EQ(m.Val(2, 1), 0);
  ASSERT_EQ(m.Val(2, 2), 0);
}

TEST(MatrixBasicTest, MatrixTranspose) {
  math::Matrix<2, 3> original(math::MatrixRow<3>(1, 2, 3),
                              math::MatrixRow<3>(4, 5, 6));
  math::Matrix<3, 2> transposed(math::MatrixRow<2>(1, 4),
                                math::MatrixRow<2>(2, 5),
                                math::MatrixRow<2>(3, 6));

  ASSERT_EQ(original.Transpose(), transposed);
}
