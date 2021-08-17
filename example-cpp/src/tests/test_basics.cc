#include <gtest/gtest.h>

// ideally this will be a shared library, but for now it's easier to just
#include "../mylib.hpp"

TEST(AdditionTest, CanAddIntegers) {
  auto sum = mylib::add_nums(3, 4);
  // auto sum = mylib::add_nums(2, 'A');
  EXPECT_EQ(7, sum);
}

TEST(MultiplicationTest, CanMultiplyIntegers) {
  auto product = mylib::mul_nums(3, 4);
  EXPECT_EQ(12, product);
}

TEST(ThrowsExceptionTest, CanThrowException) {
  EXPECT_THROW(mylib::throw_exception(), std::runtime_error);
}
