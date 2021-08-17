#pragma once

namespace mylib {
template <typename T> T add_nums(T a, T b) { return a + b; }

template <typename T> T mul_nums(T a, T b) { return a * b; }

void throw_exception() { throw std::runtime_error("I will throw!"); }
} // namespace mylib
