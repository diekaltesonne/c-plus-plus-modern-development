#include <iostream>
#include <optional>

using T = int64_t;

std::optional<T> add(T x, T y) {
  if (x > 0 && y > 0) {
    T max = std::numeric_limits<T>::max();
    if (x > max - y) {
      return std::nullopt;
    }
  } else if (x < 0 && y < 0) {
    T min = std::numeric_limits<T>::min();
    if (x < min - y) {
      return std::nullopt;
    }
  }
  return x + y;
}

int main() {
  T x, y;
  std::cin >> x >> y;
  if (auto sum = add(x, y))
    std::cout << *sum << std::endl;
  else
    std::cout << "Overflow!" << std::endl;
}
