#include <iostream>
int Digit(unsigned long long x, int i) {
  unsigned long long c = 255ULL << 8 * (i - 1);
  unsigned long long res = x & c;
  int ans = res >> 8ULL * (i - 1);
  return ans;
}
void FillCount(u_int64_t* array, int* count, int n, int q) {
  int x;
  for (int i = 0; i < n; i++) {
    x = Digit(array[i], q);
    count[x]++;
  }
}
void InitArray(int* count, int n) {
  for (int i = 0; i < n; i++) {
    count[i] = 0;
  }
}
void LSDsort(u_int64_t* array, int n) {
  u_int64_t* res = new u_int64_t[n];
  int* count = new int[256];
  int* pref = new int[256];
  for (int q = 1; q <= 8; q++) {
    InitArray(count, 256);
    InitArray(pref, 256);
    FillCount(array, count, n, q);
    for (int i = 1; i < 256; i++) {
      pref[i] = pref[i - 1] + count[i - 1];
    }
    int x;
    for (int i = 0; i < n; i++) {
      x = Digit(array[i], q);
      res[pref[x]++] = array[i];
    }

    for (int i = 0; i < n; i++) {
      array[i] = res[i];
    }
  }

  delete[] count;
  delete[] pref;
  delete[] res;
}
int main() {
  long long n;
  std::cin >> n;
  u_int64_t* array = new u_int64_t[n];
  for (int i = 0; i < n; i++) {
    std::cin >> array[i];
  }
  LSDsort(array, n);
  for (int i = 0; i < n; i++) {
    std::cout << array[i] << '\n';
  }
  delete[] array;
}

