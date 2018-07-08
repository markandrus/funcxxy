#include <funcxxy/funcxxy.h>
#include <gtest/gtest.h>

using namespace funcxxy;

static bool toggle(const bool a) {
  return !a;
}

TEST(Maybe, MapOp) {
  auto result = toggle % Just(false);
  ASSERT_TRUE(result.FromMaybe(false));
}

static int add2(const int a, const int b) {
  return a + b;
}

TEST(Maybe, ApplyOp1) {
  auto result = curry(add2) % Just(1) * Just(2);
  ASSERT_EQ(result.FromMaybe(0), 3);
}

TEST(Maybe, OrOp) {
  auto result = Nothing<bool>() | Just(true);
  ASSERT_TRUE(result.FromMaybe(false));
}

static int add3(const int a, const int b, const int c) {
  return a + b + c;
}

TEST(Maybe, ApplyOp2) {
  auto result = curry(add3)
    % Just(1)
    * Just(2)
    * Just(3);
  ASSERT_EQ(result.FromMaybe(0), 6);
}

TEST(Either, OrOp) {
  auto left = Left<int>(std::string("Left"));
  auto right = Right<std::string>(0);
  Either<std::string, int> result = (left | right);
  ASSERT_TRUE(result.FromEither<bool>(
      [](const std::string) { return false; },
      [](const int) { return true; }));
}

TEST(Either, ApplyOp) {
  auto result = curry(add3)
    % Right<bool>(1)
    * Right<bool>(2)
    * Right<bool>(3);
  ASSERT_EQ(result.FromRight(0), 6);
}

TEST(Validation, IsValid) {
  auto valid = Valid(1);
  ASSERT_TRUE(valid.IsValid());
  ASSERT_FALSE(valid.IsInvalid());
}

TEST(Validation, IsInvalid) {
  auto invalid = Invalid<bool>("");
  ASSERT_TRUE(invalid.IsInvalid());
  ASSERT_FALSE(invalid.IsValid());
}

static Validation<int> even(const int value) {
  return value % 2
    ? Invalid<int>("Expected an even number")
    : Valid(value);
}

static Validation<int> odd(const int value) {
  return value % 2
    ? Valid(value)
    : Invalid<int>("Expected an odd number");
}

static int multiply(const int a, const int b) {
  return a * b;
}

TEST(Validation, ApOp1) {
  auto result = curry(multiply)
    % even(2)
    * odd(3);
  ASSERT_EQ(result.FromValidation(0), 6);
}

TEST(Validation, OrOp) {
  auto result = Invalid<bool>("IDK") | Valid(true);
  ASSERT_TRUE(result.FromValidation(false));
}

TEST(Validation, ApOp2) {
  auto result = curry(add3)
    % odd(0)
    * odd(2)
    * odd(4);
  auto errors = result.ToErrors();
  ASSERT_EQ(errors.size(), 3);
  for (const auto &error: errors) {
    ASSERT_EQ(error, "Expected an odd number");
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
