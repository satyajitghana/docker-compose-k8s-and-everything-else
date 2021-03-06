cmake_minimum_required(VERSION 3.14)
project(helloworld)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(helloworld src/main.cc src/mylib.hpp)

enable_testing()

add_executable(
  test_basics
  src/tests/test_basics.cc
  src/mylib.hpp
)
target_link_libraries(
  test_basics
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_basics)