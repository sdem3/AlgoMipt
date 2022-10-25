#include <iostream>
#include <string>
const int kMaxValue = 200000;
int stack1[kMaxValue];
int min_stack1[kMaxValue];
int stack2[kMaxValue];
int min_stack2[kMaxValue];
int indexx1 = -1;
int indexx2 = -1;
void PushInStack1(int n) {
  ++indexx1;
  stack1[indexx1] = n;
  if (indexx1 != 0) {
    min_stack1[indexx1] = std::min(n, min_stack1[indexx1 - 1]);
  } else {
    min_stack1[indexx1] = n;
  }
}
void PushInStack2(int n) {
  ++indexx2;
  stack2[indexx2] = n;
  if (indexx2 != 0) {
    min_stack2[indexx2] = std::min(n, min_stack2[indexx2 - 1]);
  } else {
    min_stack2[indexx2] = n;
  }
}
void PopInStack1() { --indexx1; }
void PopInStack2() { --indexx2; }
int BackInStack1() { return stack1[indexx1]; }
int BackInStack2() { return stack2[indexx2]; }
int MinInStack1() { return min_stack1[indexx1]; }
int MinInStack2() { return min_stack2[indexx2]; }
int Size1() { return indexx1 + 1; }
int Size2() { return indexx2 + 1; }
void Clear() {
  indexx1 = indexx2 = -1;
  std::cout << "ok";
}
void Shift() {
  if (Size2() == 0) {
    while (Size1() > 0) {
      PushInStack2(BackInStack1());
      PopInStack1();
    }
  }
}
void Enqueue(int n) {
  PushInStack1(n);
  std::cout << "ok";
}
void Dequeue() {
  Shift();
  if (Size2() > 0) {
    std::cout << BackInStack2();
    PopInStack2();
  } else {
    std::cout << "error";
  }
}
void Front() {
  Shift();
  if (Size2() > 0) {
    std::cout << BackInStack2();
  } else {
    std::cout << "error";
  }
}
void Size() {
  Shift();
  std::cout << Size2() + Size1();
}
void Min() {
  if (Size1() > 0 && Size2() > 0) {
    std::cout << std::min(MinInStack2(), MinInStack1());
  }
  if (Size1() > 0 && Size2() == 0) {
    std::cout << MinInStack1();
  }
  if (Size2() > 0 && Size1() == 0) {
    std::cout << MinInStack2();
  }
  if (Size2() == 0 && Size1() == 0) {
    std::cout << "error";
  }
}
void Request() {
  std::string command;
  std::cin >> command;
  if (command == "enqueue") {
    int n;
    std::cin >> n;
    Enqueue(n);
  }
  if (command == "clear") {
    Clear();
  }
  if (command == "dequeue") {
    Dequeue();
  }
  if (command == "front") {
    Front();
  }
  if (command == "size") {
    Size();
  }
  if (command == "min") {
    Min();
  }
  std::cout << '\n';
}
int main() {
  int m;
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    Request();
  }
}
