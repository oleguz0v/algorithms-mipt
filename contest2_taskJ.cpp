/*
В этой задаче вам предстоит реализовать очередь с поддержкой минимума.
*/

#include <deque>
#include <iostream>

class QueueWithMin {
  public:
    void Front() const;
    void Size() const;
    void GetMin() const;
    void Clear();
    void Dequeue();
    void Enqueue(int value);
    
  private:
    std::deque<int> queue_;
    std::deque<int> minQueue_;
};

void QueueWithMin::Front() const {
  if (queue_.empty()) {
    std::cout << "error" << '\n';
  } else {
    std::cout << queue_.front() << '\n';
  }
}

void QueueWithMin::Size() const { std::cout << queue_.size() << '\n'; }

void QueueWithMin::GetMin() const {
  if (minQueue_.empty()) {
    std::cout << "error" << '\n';
  } else {
    std::cout << minQueue_.front() << '\n';
  }
}

void QueueWithMin::Clear() {
  queue_.clear();
  minQueue_.clear();
  std::cout << "ok" << '\n';
}

void QueueWithMin::Dequeue() {
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

void QueueWithMin::Enqueue(int value) {
  queue_.push_back(value);
  while (!minQueue_.empty() and minQueue_.back() > value) {
    minQueue_.pop_back();
  }
  minQueue_.push_back(value);
  std::cout << "ok" << '\n';
}

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
