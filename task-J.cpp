#include <deque>
#include <iostream>
#include <vector>

class MinHeap {
 public:
  MinHeap() : data(20), size(0) {}
  void Insert(std::pair<int, int> val) {
    if (size == data.size()) {
      data.resize(2 * size);
    }
    data[size++] = val;
    SiftUp(size - 1);
  }
  bool IsEmpty() { return size == 0; }
  std::pair<int, int> ExtractMin() {
    if (size > 0) {
      std::swap(data[0], data[size - 1]);
      size--;
      SiftDown(0);
    }
    return data[size];
  }
  std::vector<std::pair<int, int>> data;
  size_t size;
  void SiftUp(int index) {
    if (index > 0) {
      int parent = (index - 1) / 2;
      if (data[index] < data[parent]) {
        std::swap(data[parent], data[index]);
        SiftUp(parent);
      }
    }
  }
  void SiftDown(size_t index) {
    size_t i_left_child = 2 * index + 1;
    size_t i_right_child = 2 * index + 2;
    size_t i_min = index;
    if (i_left_child < size && data[i_left_child] < data[i_min]) {
      i_min = i_left_child;
    }
    if (i_right_child < size && data[i_right_child] < data[i_min]) {
      i_min = i_right_child;
    }
    if (index != i_min) {
      std::swap(data[i_min], data[index]);
      SiftDown(i_min);
    }
  }
};
void Heapify(MinHeap& hp, std::vector<std::pair<int, int>> array) {
  hp.data = array;
  hp.size = array.size();
  for (int i = hp.size / 2; i >= 0; i--) {
    hp.SiftDown(i);
  }
}
std::vector<int> Merge(std::vector<std::deque<int>>& arrays) {
  MinHeap hp;
  std::vector<std::pair<int, int>> first_vec;
  std::vector<size_t> indexes(arrays.size(), 0);
  int index = 0;
  size_t result_size = 0;
  for (std::deque<int>& array : arrays) {
    first_vec.push_back({array.front(), index});
    index++;
    result_size += array.size();
    array.pop_front();
  }
  Heapify(hp, first_vec);
  std::vector<int> result;
  result.reserve(result_size);
  while (!hp.IsEmpty()) {
    auto pair = hp.ExtractMin();
    auto value = pair.first;
    auto index = pair.second;
    result.push_back(value);
    indexes[index]++;
    if (!arrays[index].empty()) {
      hp.Insert({arrays[index].front(), index});
      arrays[index].pop_front();
    }
  }
  return result;
}
void ReadData(int k, std::vector<std::deque<int>>& arrays) {
  for (int i = 0; i < k; i++) {
    int n;
    std::cin >> n;
    std::deque<int> heap_j;
    int x;
    for (int j = 0; j < n; j++) {
      std::cin >> x;
      heap_j.push_back(x);
    }
    arrays.push_back(heap_j);
  }
}
int main() {
  int k;
  std::cin >> k;
  std::vector<std::deque<int>> arrays;
  ReadData(k, arrays);
  std::vector<int> result = Merge(arrays);
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << result[i] << ' ';
  }
}

