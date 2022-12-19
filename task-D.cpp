#include <cmath>
#include <iostream>
#include <string>
#include <vector>
const int64_t kLongTwo = 1 << 30;
class MaxHeap {
public:
  MaxHeap() : data(1), size(0) {}
  void Insert(int64_t val) {
    if (size == data.size()) {
      data.resize(2 * size);
    }
    data[size++] = val;
    SiftUp(size - 1);
  }
  bool IsEmpty() { return size == 0; }
  int64_t GetMax() { return data[0]; }
  void ExtractMax() {
    if (size > 0) {
      std::swap(data[0], data[size - 1]);
      size--;
      SiftDown(0);
    }
  }
  std::vector<int64_t> data;
  size_t size;
  void SiftUp(size_t index) {
    if (index > 0) {
      int parent = (index - 1) / 2;
      if (data[index] > data[parent]) {
        std::swap(data[parent], data[index]);
        SiftUp(parent);
      }
    }
  }
  void SiftDown(size_t index) {
    size_t i_left_child = 2 * index + 1;
    size_t i_right_child = 2 * index + 2;
    size_t i_min = index;
    if (i_left_child < size && data[i_left_child] > data[i_min]) {
      i_min = i_left_child;
    }
    if (i_right_child < size && data[i_right_child] > data[i_min]) {
      i_min = i_right_child;
    }
    if (index != i_min) {
      std::swap(data[i_min], data[index]);
      SiftDown(i_min);
    }
  }
};

struct Request {
public:
  size_t n;
  size_t k;
  int64_t a0;
  int64_t x;
  int64_t y;
};

void Heapify(MaxHeap& hp, Request re) {
  hp.data[0] = (re.a0* re.x + re.y) % kLongTwo;
  if (re.k >= re.n) {
    re.k = re.n;
  }
  for (int i = 1; i < re.k; i++) {
    hp.data.push_back((hp.data[i - 1] * re.x + re.y) % kLongTwo);
  }
  hp.size = re.k;
  re.a0 = hp.data[re.k - 1];
  for (size_t i = hp.size / 2; i >= 0; i--) {
    hp.SiftDown(i);
  }
  int64_t temp;
  for (size_t i = re.k; i < re.n; i++) {
    temp = (re.a0 * re.x + re.y) % kLongTwo;
    if (temp < hp.GetMax()) {
      hp.ExtractMax();
      hp.Insert(temp);
    }
    re.a0 = temp;
  }
}

int main() {
  Request re;
  std:: cin>> re.n >> re.k;
  std::cin >> re.a0 >> re.x >> re.y;
  int64_t* request = new int64_t[5];
  std::cin >> request[0] >> request[1];
  std::cin >> request[2] >> request[3] >> request[4];
  MaxHeap hp;
  std::vector<int64_t> res;
  Heapify(hp, re);
  for (int i = 0; i < request[1]; i++) {
    res.push_back(hp.GetMax());
    hp.ExtractMax();
  }
  for (size_t i = re.k - 1; i > -1; i--) {
    std::cout << res[i] << ' ';
  }
}
