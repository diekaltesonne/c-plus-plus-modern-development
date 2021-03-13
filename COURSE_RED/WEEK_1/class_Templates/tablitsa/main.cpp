#include "test_runner.h"
#include <vector>
using namespace std;

// Реализуйте здесь шаблонный класс Table

template <typename value>
class Table {
public:
    Table(const size_t & num1 ,const size_t & num2){
       Resize(num1,num2);
    }

    const vector<value>& operator [](size_t n) const {
       return spec[n];
     }
    vector<value>& operator [] (size_t n) {
       return spec[n];
    }
    void Resize(size_t rows, size_t columns) {
        spec.resize(rows);
        for (auto& item : spec) {
          item.resize(columns);
        }
    }

    pair<size_t, size_t> Size() const {
       return {spec.size(), (spec.empty() ? 0 : spec[0].size())};
    }
private:
    vector<vector<value>> spec;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
