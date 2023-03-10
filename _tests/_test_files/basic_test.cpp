#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <list>

using namespace std;
bool stub(bool debug = false)
{
  return true;
}

//----- ----- ----- ----- ----- ----- ----- ----- ----- -----
//Lord help me!
bool debug = false;
//----- ----- ----- ----- ----- ----- ----- ----- ----- -----



int main(int argc, char **argv)
{
  if (argc > 1)
  {
    debug = argv[1][0] == 't';
  }
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "\n\n----------running basic_test.cpp---------\n\n"
            << std::endl;
  return RUN_ALL_TESTS();
}
