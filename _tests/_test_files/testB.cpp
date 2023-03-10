#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>

using namespace std;

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}


TEST(TEST_STUB, TestStub) {
  bool success = test_stub(false);
  EXPECT_EQ(1, success);
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "\n\n----------running testB.cpp---------\n\n"
            << std::endl;
  return RUN_ALL_TESTS();
}
