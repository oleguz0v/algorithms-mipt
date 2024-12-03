#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class QueueWithMin {
 private:
  std::deque<int> queue_;
  std::deque<int> minQueue_;

 public:
  void Front() const {
    if (queue_.empty()) {
      std::cout << "error" << '\n';
    } else {
      std::cout << queue_.front() << '\n';
    }
  }

  void Size() const { std::cout << queue_.size() << '\n'; }

  void GetMin() const {
    if (minQueue_.empty()) {
      std::cout << "error" << '\n';
    } else {
      std::cout << minQueue_.front() << '\n';
    }
  }

  void Clear() {
    queue_.clear();
    minQueue_.clear();
    std::cout << "ok" << '\n';
  }

  void Dequeue() {
    if (queue_.empty()) {
      std::cout << "error" << '\n';
    } else {
      std::cout << queue_.front() << '\n';
      if (!minQueue_.empty() and minQueue_.front() == queue_.front()) {
        minQueue_.pop_front();
      }
      queue_.pop_front();
    }
  }

  void Enqueue(int value) {
    queue_.push_back(value);
    while (!minQueue_.empty() and minQueue_.back() > value) {
      minQueue_.pop_back();
    }
    minQueue_.push_back(value);
    std::cout << "ok" << '\n';
  }
};

int main() {
  int q;
  int value;
  std::cin >> q;
  std::string command;
  QueueWithMin qwm;
  for (int i = 0; i < q; ++i) {
    std::cin >> command;
    if (command == "enqueue") {
      std::cin >> value;
      qwm.Enqueue(value);
    } else if (command == "dequeue") {
      qwm.Dequeue();
    } else if (command == "front") {
      qwm.Front();
    } else if (command == "size") {
      qwm.Size();
    } else if (command == "clear") {
      qwm.Clear();
    } else if (command == "min") {
      qwm.GetMin();
    }
  }
}
