#include <funcxxy/funcxxy.h>
#include <gtest/gtest.h>

using namespace funcxxy;

static bool toggle(bool a) {
  return !a;
}

TEST(funcxxyTest, Maybe) {
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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
