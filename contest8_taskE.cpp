// Нахождение отрицательного цикла с помощью алгоритма Форда-Беллмана

#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

const int cNoEdge = 100000;

class Graph {
 public:
  explicit Graph(int vertex_count) {
    vertex_count_ = vertex_count;
    adj_matrix_.resize(vertex_count_ + 1, vector<long long>(vertex_count_ + 1));
  }

  void SetEdgeWeight(int from, int to, long long weight) {
    adj_matrix_[from][to] = weight;
  }

  bool HasNegativeCycle(vector<int>& cycle_out) {
    InitializeDistances();
    int cycle_start = RelaxEdges();
    if (cycle_start == -1) {
      return false;
    }
    cycle_start = FindCycleStart(cycle_start);
    cycle_out = RecoverCycle(cycle_start);
    return true;
  }

 private:
  int vertex_count_;
  vector<vector<long long>> adj_matrix_;
  vector<long long> distances_;
  vector<int> parent_;

  void InitializeDistances() {
    distances_.assign(vertex_count_ + 1, 0);
    parent_.assign(vertex_count_ + 1, -1);
  }

  int RelaxEdges() {
    int last_updated = -1;
    for (int iter = 1; iter <= vertex_count_; ++iter) {
      last_updated = -1;
      for (int u = 1; u <= vertex_count_; ++u) {
        for (int v = 1; v <= vertex_count_; ++v) {
          if (adj_matrix_[u][v] != cNoEdge) {
            if (distances_[v] > distances_[u] + adj_matrix_[u][v]) {
              distances_[v] = distances_[u] + adj_matrix_[u][v];
              parent_[v] = u;
              last_updated = v;
            }
          }
        }
      }
    }
    return last_updated;
  }

  int FindCycleStart(int start) const {
    for (int i = 1; i <= vertex_count_; ++i) {
      start = parent_[start];
    }
    return start;
  }

  vector<int> RecoverCycle(int start) const {
    vector<int> cycle;
    int current = start;
    while (true) {
      cycle.push_back(current);
      current = parent_[current];
      if (current == start && cycle.size() > 1) {
        break;
      }
    }
    cycle.push_back(start);
    std::reverse(cycle.begin(), cycle.end());
    return cycle;
  }
};

void ReadGraph(Graph& graph, int n) {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      long long weight;
      cin >> weight;
      graph.SetEdgeWeight(i, j, weight);
    }
  }
}

void PrintCycleResult(const vector<int>& cycle) {
  if (cycle.empty()) {
    cout << "NO" << endl;
  } else {
    cout << "YES" << endl;
    cout << (int)cycle.size() << endl;
    for (int v : cycle) {
      cout << v << ' ';
    }
    cout << endl;
  }
}

int main() {
  int n;
  cin >> n;
  Graph graph(n);
  ReadGraph(graph, n);
  vector<int> cycle;
  if (graph.HasNegativeCycle(cycle)) {
    PrintCycleResult(cycle);
  } else {
    PrintCycleResult({});
  }
}
