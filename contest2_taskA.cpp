#include <iostream>
#include <string>
#include <vector>

class Heap {
 private:
  std::vector<std::pair<long long, long long>> heap_;
  std::vector<int> indexMap_;

  void SiftUp(int el) {
    while (heap_[el].first < heap_[(el - 1) / 2].first) {
      std::swap(heap_[el], heap_[(el - 1) / 2]);
      std::swap(indexMap_[heap_[el].second],
                indexMap_[heap_[(el - 1) / 2].second]);
      el = (el - 1) / 2;
    }
  }

  void SiftDown(int el, int n) {
    while (2 * el + 2 < n and
           heap_[el].first >
               std::min(heap_[2 * el + 1].first, heap_[2 * el + 2].first)) {
      if (heap_[2 * el + 1].first < heap_[2 * el + 2].first) {
        std::swap(heap_[el], heap_[2 * el + 1]);
        std::swap(indexMap_[heap_[el].second],
                  indexMap_[heap_[2 * el + 1].second]);
        el = 2 * el + 1;
      } else {
        std::swap(heap_[el], heap_[2 * el + 2]);
        std::swap(indexMap_[heap_[el].second],
                  indexMap_[heap_[2 * el + 2].second]);
        el = 2 * el + 2;
      }
    }
    if (2 * el + 1 < n and heap_[el].first > heap_[2 * el + 1].first) {
      std::swap(heap_[el], heap_[2 * el + 1]);
      std::swap(indexMap_[heap_[el].second],
                indexMap_[heap_[2 * el + 1].second]);
    }
  }

 public:
  Heap(int size) { indexMap_.resize(size, -1); }

  void Insert(long long value, int index) {
    std::pair<long long, int> element = {value, index};
    heap_.push_back(element);
    indexMap_[index] = (int)heap_.size() - 1;
    SiftUp((int)heap_.size() - 1);
  }

  void ExtractMin() {
    heap_[0] = heap_.back();
    heap_.pop_back();
    if (!heap_.empty()) {
      indexMap_[heap_[0].second] = 0;
      SiftDown(0, (int)heap_.size());
    }
  }

  long long GetMin() { return heap_[0].first; }

  void DecreaseKey(int op_index, long long delta) {
    int heap_index = indexMap_[op_index - 1];
    heap_[heap_index].first -= delta;
    SiftUp(heap_index);
  }
};

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