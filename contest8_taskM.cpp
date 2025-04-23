// Алгоритм Крускала для поиска суммы весов минимального остовного дерева

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::sort;
using std::vector;

class KruskalMST {
 public:
  KruskalMST(int n, int m) {
    n_ = n;
    m_ = m;
    edges_.resize(m_);
    parent_.resize(n_ + 1);
    size_.resize(n_ + 1);
    sum_ = 0;
    for (int i = 1; i <= n_; ++i) {
      parent_[i] = i;
      size_[i] = 1;
    }
  }

  void AddEdge(int i, int u, int v, int w) { edges_[i] = {w, {u, v}}; }

  void BuildMST() {
    sort(edges_.begin(), edges_.end());
    for (int i = 0; i < m_; ++i) {
      int a = edges_[i].second.first;
      int b = edges_[i].second.second;
      int c = edges_[i].first;
      int ra = Find(a);
      int rb = Find(b);
      if (ra != rb) {
        sum_ = sum_ + c;
        if (size_[ra] < size_[rb]) {
          int tmp = ra;
          ra = rb;
          rb = tmp;
        }
        parent_[rb] = ra;
        size_[ra] = size_[ra] + size_[rb];
      }
    }
  }

  void PrintTotalWeight() const { cout << sum_ << endl; }

 private:
  int n_;
  int m_;
  vector<pair<int, pair<int, int>>> edges_;
  vector<int> parent_;
  vector<int> size_;
  long long sum_;
  int Find(int v) {
    if (v == parent_[v]) {
      return v;
    }
    parent_[v] = Find(parent_[v]);
    return parent_[v];
  }
};

int main() {
  int n;
  int m;
  cin >> n;
  cin >> m;
  KruskalMST solver(n, m);
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    int w;
    cin >> u;
    cin >> v;
    cin >> w;
    solver.AddEdge(i, u, v, w);
  }
  solver.BuildMST();
  solver.PrintTotalWeight();
}
