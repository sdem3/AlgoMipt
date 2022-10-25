#include <cmath>
#include <iomanip>
#include <iostream>
const int kMaxValue = 3 * 100000;
long double mandragors[kMaxValue];
long double prefiks[kMaxValue];
void FillPrefiks(int n) {
  prefiks[0] = 1;
  prefiks[1] = pow(mandragors[1], 1.0 / n);
  for (int i = 2; i <= n; i++) {
    prefiks[i] = prefiks[i - 1] * pow(mandragors[i], 1.0 / n);
  }
}
long double Meangeo(int l, int r, int n) {
  long double res = pow(prefiks[r + 1] / prefiks[l], (n * 1.0) / (r - l + 1));
  return res;
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> mandragors[i];
  }
  FillPrefiks(n);
  int q;
  std::cin >> q;
  int l, r;
  std::cout << std::fixed << std::setprecision(16);
  for (int i = 0; i < q; i++) {
    std::cin >> l >> r;
    std::cout << Meangeo(l, r, n) << '\n';
  }
}
