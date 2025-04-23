// Алгоритм Дейкстры для нескольких тестов на графах с неотрицательными рёбрами

#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::priority_queue;
using std::vector;

const long long cInf = 2009000999;

class DijkstraSolver {
 public:
  DijkstraSolver(int n, int m) {
    n_ = n;
    m_ = m;
    gr_.resize(n_);
    d_.assign(n_, cInf);
  }

  void AddEdge(int u, int v, int c) {
    gr_[u].push_back({v, c});
    gr_[v].push_back({u, c});
  }

  void Run(int s) {
    d_.assign(n_, cInf);
    d_[s] = 0;
    priority_queue<pair<int, int>> q;
    q.push({0, s});
    while (!q.empty()) {
      int now = q.top().second;
      int dist = -q.top().first;
      q.pop();
      if (d_[now] < dist) {
        continue;
      }
      for (auto el : gr_[now]) {
        if (d_[el.first] > d_[now] + el.second) {
          d_[el.first] = d_[now] + el.second;
          q.push({-d_[el.first], el.first});
        }
      }
    }
  }

  void PrintDistances() const {
    for (int i = 0; i < n_; ++i) {
      cout << d_[i] << ' ';
    }
    cout << endl;
  }

 private:
  int n_;
  int m_;
  vector<vector<pair<int, int>>> gr_;
  vector<int> d_;
};

int main() {
  int t;
  cin >> t;
  while ((t--) > 0) {
    int n;
    int m;
    cin >> n;
    cin >> m;
    DijkstraSolver solver(n, m);
    for (int i = 0; i < m; ++i) {
      int u;
      int v;
      int c;
      cin >> u;
      cin >> v;
      cin >> c;
      solver.AddEdge(u, v, c);
    }
    int s;
    cin >> s;
    solver.Run(s);
    solver.PrintDistances();
  }
}
