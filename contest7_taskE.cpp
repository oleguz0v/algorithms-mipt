// Нахождение мостов в неориентированном графе с помощью DFS

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::pair;
using std::sort;
using std::vector;

class BridgeFinder {
 public:
  BridgeFinder(int n, int m) {
    size_ = n;
    edges_ = m;
    gr_.resize(size_ + 1);
    tup_.resize(size_ + 1);
    tin_.resize(size_ + 1);
    used_.resize(size_ + 1);
    tim_ = 0;
  }

  void AddEdge(int u, int v, int idx) {
    gr_[u].push_back({v, idx});
    gr_[v].push_back({u, idx});
  }

  void FindBridges() {
    for (int i = 1; i <= size_; ++i) {
      if (!used_[i]) {
        Dfs(i, -1);
      }
    }
  }

  void PrintBridges() {
    sort(ans_.begin(), ans_.end());
    cout << ans_.size() << endl;
    for (int i = 0; i < (int)ans_.size(); ++i) {
      cout << ans_[i] + 1 << ' ';
    }
    cout << endl;
  }

 private:
  int size_;
  int edges_;
  int tim_;
  vector<vector<pair<int, int>>> gr_;
  vector<int> tup_;
  vector<int> tin_;
  vector<bool> used_;
  vector<int> ans_;

  void Dfs(int ind_now, int le) {
    tin_[ind_now] = ++tim_;
    used_[ind_now] = true;
    tup_[ind_now] = tin_[ind_now];
    for (auto el : gr_[ind_now]) {
      if (el.second != le) {
        if (used_[el.first]) {
          tup_[ind_now] = min(tup_[ind_now], tin_[el.first]);
        } else {
          Dfs(el.first, el.second);
          tup_[ind_now] = min(tup_[ind_now], tup_[el.first]);
          if (tup_[el.first] > tin_[ind_now]) {
            ans_.push_back(el.second);
          }
        }
      }
    }
  }
};

int main() {
  int n;
  int m;
  int a;
  int b;
  cin >> n;
  cin >> m;
  BridgeFinder solver(n, m);
  for (int i = 0; i < m; ++i) {
    cin >> a;
    cin >> b;
    solver.AddEdge(a, b, i);
  }
  solver.FindBridges();
  solver.PrintBridges();
}
