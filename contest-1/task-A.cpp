#include <iostream>
const int kMaxValue = 100000 + 3;
int array[kMaxValue];
bool BinarySearch(int begin, int end, int target) {
  bool result = false;
  int left = begin;
  int right = end;
  int median;
  while ((right - left) != 1) {
    median = (left + right) / 2;

    if (array[median] > target) {
      right = median;
    } else {
      left = median;
    }
  }
  if (array[left] == target) {
    result = true;
  }
  return result;
}
int main() {
  int q, n, i, j, target;
  std::cin >> n;
  for (int k = 0; k < n; k++) {
    std::cin >> array[k];
  }
  std::cin >> q;
  for (int k = 0; k < q; k++) {
    std::cin >> i >> j >> target;
    if (BinarySearch(i, j, target)) {
      std::cout << "YES" << '\n';
    } else {
      std::cout << "NO" << '\n';
    }
  }
}
