/*
 Вам нужно реализовать структуру данных, которая поддерживает очередь элементов и обрабатывает запросы следующих типов:
 + x: добавить число x в конец очереди;
 * x: вставить число x в середину очереди (если в очереди нечётное число элементов, то x встаёт сразу за центральным элементом);
 -: удалить первый элемент очереди и вывести его значение.
 */

#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

class MidDeque {
 private:
  std::deque<int> first_;
  std::deque<int> second_;

  void Balance();

 public:
  void PushBack(int value);
  void PushMiddle(int value);
  int PopFront();
};

void MidDeque::Balance() {
  if (second_.size() > first_.size()) {
    first_.push_back(second_.front());
    second_.pop_front();
  }
}

void MidDeque::PushBack(int value) {
  second_.push_back(value);
  Balance();
}

void MidDeque::PushMiddle(int value) {
  second_.push_front(value);
  Balance();
}

int MidDeque::PopFront() {
  int res = first_.front();
  first_.pop_front();
  Balance();
  return res;
}

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
