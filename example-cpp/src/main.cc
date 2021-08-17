#include <iostream>

#include "mylib.hpp"

auto main(int argc, char **argv) -> int {
  std::cout << "Hello, world! from Docker" << std::endl;

  std::cout << std::endl;

  double a, b;
  std::cout << "Enter number A: ";
  std::cin >> a;
  std::cout << "Enter number B: ";
  std::cin >> b;

  auto sum = mylib::add_nums(a, b);
  auto prod = mylib::mul_nums(a, b);

  std::cout << "Sum: " << sum << std::endl;
  std::cout << "Product: " << prod << std::endl;

  return 0;
}