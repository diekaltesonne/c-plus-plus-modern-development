#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl<< (y) << endl

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream out;
    PRINT_VALUES(out, 5, "red belt");
    ASSERT_EQUAL(out.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example");
}
