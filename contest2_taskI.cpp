#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

class MidDeque {
 private:
  std::deque<int> first_;
  std::deque<int> second_;

  void Balance() {
    if (second_.size() > first_.size()) {
      first_.push_back(second_.front());
      second_.pop_front();
    }
  }

 public:
  void PushBack(int value) {
    second_.push_back(value);
    Balance();
  }

  void PushMiddle(int value) {
    second_.push_front(value);
    Balance();
  }

  int PopFront() {
    int res = first_.front();
    first_.pop_front();
    Balance();
    return res;
  }
};

int main() {
  int n;
  std::cin >> n;
  MidDeque deque;
  char command;
  int value;
  for (int i = 0; i < n; ++i) {
    std::cin >> command;
    if (command == '+') {
      std::cin >> value;
      deque.PushBack(value);
    } else if (command == '*') {
      std::cin >> value;
      deque.PushMiddle(value);
    } else {
      std::cout << deque.PopFront() << '\n';
    }
  }
}
