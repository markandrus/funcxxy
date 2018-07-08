#include <funcxxy/funcxxy.h>
#include <gtest/gtest.h>

using namespace funcxxy;

static bool toggle(bool a) {
  return !a;
}

TEST(funcxxyTest, Maybe1) {
  auto result = toggle % Just(false);
  ASSERT_TRUE(result.FromMaybe(false));
}

static int add2(int a, int b) {
  return a + b;
}

TEST(funcxxyTest, Maybe2) {
  auto result = curry(add2) % Just(1) * Just(2);
  ASSERT_EQ(result.FromMaybe(0), 3);
}

TEST(funcxxyTest, Maybe3) {
  auto result = Nothing<bool>() | Just(true);
  ASSERT_TRUE(result.FromMaybe(false));
}

static int add3(int a, int b, int c) {
  return a + b + c;
}

TEST(funcxxyTest, Maybe4) {
  auto result = curry(add3)
    % Just(1)
    * Just(2)
    * Just(3);
  ASSERT_EQ(result.FromMaybe(0), 6);
}

TEST(funcxxyTest, Either1) {
  auto left = Left<int>(std::string("Left"));
  auto right = Right<std::string>(0);
  Either<std::string, int> result = (left | right);
  ASSERT_TRUE(result.FromEither<bool>(
      [](const std::string) { return false; },
      [](const int) { return true; }));
}

TEST(funcxxy, Either2) {
  auto result = curry(add3)
    % Right<bool>(1)
    * Right<bool>(2)
    * Right<bool>(3);
  ASSERT_EQ(result.FromRight(0), 6);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
