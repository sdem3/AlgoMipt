#include <iostream>
int array[100000];
int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  int left = 0;
  int right = n;
  int median = 0;
  while ((right - left) != 1) {
    median = (left + right) / 2;
    if (array[left] < array[median]) {
      left = median;
    } else {
      right = median;
    }
  }
  if (right == n) {
    right = 0;
  }
  std::cout << right;
}
