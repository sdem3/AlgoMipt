#include <cmath>
#include <iostream>
#include <string>
#include <vector>
const int64_t kLongTwo = 1 << 30;
class MaxHeap {
 public:
  MaxHeap() : data(1), size(0) {}
  void Insert(long long val) {
    if (size == data.size()) {
      data.resize(2 * size);
    }
    data[size++] = val;
    SiftUp(size - 1);
  }
  bool IsEmpty() { return size == 0; }
  long long GetMax() { return data[0]; }
  void ExtractMax() {
    if (size > 0) {
      std::swap(data[0], data[size - 1]);
      size--;
      SiftDown(0);
    }
  }
  std::vector<long long> data;
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
void Heapify(MaxHeap& hp, int64_t* request) {
  hp.data[0] = (request[2] * request[3] + request[4]) % kLongTwo;
  if (request[1] >= request[0]) {
    request[1] = request[0];
  }
  for (int i = 1; i < request[1]; i++) {
    hp.data.push_back((hp.data[i - 1] * request[3] + request[4]) % kLongTwo);
  }
  hp.size = request[1];
  request[2] = hp.data[request[1] - 1];
  for (int i = hp.size / 2; i >= 0; i--) {
    hp.SiftDown(i);
  }
  int64_t temp;
  for (int i = request[1]; i < request[0]; i++) {
    temp = (request[2] * request[3] + request[4]) % kLongTwo;
    if (temp < hp.GetMax()) {
      hp.ExtractMax();
      hp.Insert(temp);
    }
    request[2] = temp;
  }
}
int main() {
  int64_t* request = new int64_t[5];
  std::cin >> request[0] >> request[1];
  std::cin >> request[2] >> request[3] >> request[4];
  MaxHeap hp;
  std::vector<int64_t> res;
  Heapify(hp, request);
  for (int i = 0; i < request[1]; i++) {
    res.push_back(hp.GetMax());
    hp.ExtractMax();
  }
  for (int i = request[1] - 1; i > -1; i--) {
    std::cout << res[i] << ' ';
  }
}
