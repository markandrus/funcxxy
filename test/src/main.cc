#include <funcxxy/funcxxy.h>
#include <gtest/gtest.h>

TEST(funcxxyTest, test) {
  ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
