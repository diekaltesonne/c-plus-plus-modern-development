#include "test_runner.h"
#include "logger.h"

int main(){
  TestRunner tr;
  RUN_TEST(tr, TestLog);
  return 0;
}
