// Алгоритм Косарайю для нахождения компонент сильной связности

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::reverse;
using std::vector;

class KosarajuSCC {
 public:
  KosarajuSCC(int n) {
    size_ = n;
    col_ = 1;
    gr_.resize(size_ + 1);
    grt_.resize(size_ + 1);
    used_.assign(size_ + 1, false);
    ans_.resize(size_ + 1);
  }

  void AddEdge(int from, int to) {
    gr_[from].push_back(to);
    grt_[to].push_back(from);
  }

  void ComputeSCC() {
    for (int i = 1; i <= size_; ++i) {
      if (!used_[i]) {
        Dfs(i);
      }
    }
    reverse(order_.begin(), order_.end());
    used_.assign(size_ + 1, false);
    for (auto el : order_) {
      if (!used_[el]) {
        Dfst(el);
        ++col_;
      }
    }
  }

  int GetComponentCount() const { return col_ - 1; }

  void PrintComponents() const {
    for (int i = 1; i <= size_; ++i) {
      cout << ans_[i] << ' ';
    }
    cout << endl;
  }

 private:
  int size_;
  int col_;
  vector<vector<int>> gr_;
  vector<vector<int>> grt_;
  vector<int> ans_;
  vector<int> order_;
  vector<bool> used_;

  void Dfs(int ind_now) {
    used_[ind_now] = true;
    for (auto el : gr_[ind_now]) {
      if (!used_[el]) {
        Dfs(el);
      }
    }
    order_.push_back(ind_now);
  }

  void Dfst(int ind_now) {
    used_[ind_now] = true;
    ans_[ind_now] = col_;
    for (auto el : grt_[ind_now]) {
      if (!used_[el]) {
        Dfst(el);
      }
    }
  }
};

int main() {
  int n;
  int m;
  cin >> n;
  cin >> m;
  KosarajuSCC scc(n);
  for (int i = 0; i < m; ++i) {
    int a;
    int b;
    cin >> a;
    cin >> b;
    scc.AddEdge(a, b);
  }
  scc.ComputeSCC();
  cout << scc.GetComponentCount() << endl;
  scc.PrintComponents();
}
