// Нахождение отрицательного цикла с помощью алгоритма Форда-Беллмана

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;
using std::vector;

const int cNoEdge = 100000;

class NegativeCycleFinder {
 public:
  NegativeCycleFinder(int n) {
    n_ = n;
    a_.resize(n_ + 1, vector<long long>(n_ + 1));
    d_.resize(n_ + 1);
    par_.resize(n_ + 1);
  }

  void ReadGraph() {
    for (int i = 1; i <= n_; ++i) {
      for (int j = 1; j <= n_; ++j) {
        cin >> a_[i][j];
      }
    }
  }

  void FindCycle() {
    for (int i = 1; i <= n_; ++i) {
      d_[i] = 0;
      par_[i] = -1;
    }
    int x = -1;
    for (int it = 1; it <= n_; ++it) {
      x = -1;
      for (int u = 1; u <= n_; ++u) {
        for (int v = 1; v <= n_; ++v) {
          if (a_[u][v] != cNoEdge) {
            if (d_[v] > d_[u] + a_[u][v]) {
              d_[v] = d_[u] + a_[u][v];
              par_[v] = u;
              x = v;
            }
          }
        }
      }
    }
    if (x == -1) {
      cout << "NO" << endl;
      return;
    }
    for (int i = 1; i <= n_; ++i) {
      x = par_[x];
    }
    int now = x;
    while (true) {
      cycle_.push_back(now);
      now = par_[now];
      if (now == x and (int) cycle_.size() > 1) {
        break;
      }
    }
    cycle_.push_back(x);
    std::reverse(cycle_.begin(), cycle_.end());
    cout << "YES" << endl;
    cout << (int)cycle_.size() << endl;
    for (int i = 0; i < (int)cycle_.size(); ++i) {
      cout << cycle_[i] << ' ';
    }
    cout << endl;
  }

 private:
  int n_;
  vector<vector<long long>> a_;
  vector<long long> d_;
  vector<int> par_;
  vector<int> cycle_;
};

int main() {
  int n;
  cin >> n;
  NegativeCycleFinder solver(n);
  solver.ReadGraph();
  solver.FindCycle();
}
