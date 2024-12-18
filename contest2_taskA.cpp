/*
Реализовать бинарную кучу на минимум с дополнением в виде DecreaseKey
(уменьшить число, вставленное на i-м запросе, на целое число x >= 0)
*/

#include <iostream>
#include <string>
#include <vector>

class Heap {
 private:
  std::vector<std::pair<long long, long long>> heap_;
  std::vector<int> indexMap_;

  void SiftUp(int el);
  void SiftDown(int el, int n);

 public:
  explicit Heap(int size);
  void Insert(long long value, int index);
  void ExtractMin();
  const long long GetMin();
  void DecreaseKey(int op_index, long long delta);
};

Heap::Heap(int size) { indexMap_.resize(size, -1); }

void Heap::SiftUp(int el) {
  int pr = (el - 1) / 2;
  while (heap_[el].first < heap_[pr].first) {
    std::swap(heap_[el], heap_[pr]);
    std::swap(indexMap_[heap_[el].second], indexMap_[heap_[pr].second]);
    el = pr;
    pr = (el - 1) / 2;
  }
}

void Heap::SiftDown(int el, int n) {
  int l = 2 * el + 1;
  int r = 2 * el + 2;
  while (l < n) {
    int smallest = l;
    if (r < n and heap_[r].first < heap_[l].first) {
      smallest = r;
    }
    if (heap_[el].first <= heap_[smallest].first) {
      return;
    }
    std::swap(heap_[el], heap_[smallest]);
    std::swap(indexMap_[heap_[el].second], indexMap_[heap_[smallest].second]);
    el = smallest;
    l = 2 * el + 1;
    r = 2 * el + 2;
  }
}

void Heap::Insert(long long value, int index) {
  std::pair<long long, int> element = {value, index};
  heap_.push_back(element);
  indexMap_[index] = (int)heap_.size() - 1;
  SiftUp((int)heap_.size() - 1);
}

void Heap::ExtractMin() {
  heap_[0] = heap_.back();
  heap_.pop_back();
  if (!heap_.empty()) {
    indexMap_[heap_[0].second] = 0;
    SiftDown(0, (int)heap_.size());
  }
}

const long long Heap::GetMin() { return heap_[0].first; }

void Heap::DecreaseKey(int op_index, long long delta) {
  int heap_index = indexMap_[op_index - 1];
  heap_[heap_index].first -= delta;
  SiftUp(heap_index);
}

int main() {
  int q;
  std::cin >> q;
  std::string command;
  Heap heap(q);
  for (int i = 0; i < q; ++i) {
    std::cin >> command;
    if (command == "insert") {
      int value;
      std::cin >> value;
      heap.Insert(value, i);
    } else if (command == "extractMin") {
      heap.ExtractMin();
    } else if (command == "getMin") {
      std::cout << heap.GetMin() << '\n';
    } else {
      int op_index;
      long long delta;
      std::cin >> op_index >> delta;
      heap.DecreaseKey(op_index, delta);
    }
  }
}
