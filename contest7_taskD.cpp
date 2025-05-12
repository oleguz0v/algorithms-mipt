// Алгоритм Косарайю для нахождения компонент сильной связности
// Асимптотика: O(n + m), где n — количество вершин, m — количество рёбер

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::reverse;
using std::vector;

class Graph {
 public:
  explicit Graph(int vertex_count) {
    vertex_count_ = vertex_count;
    adjacency_list_.resize(vertex_count_ + 1);
  }
  void AddEdge(int from, int to) { adjacency_list_[from].push_back(to); }
  int VertexCount() const { return vertex_count_; }
  const vector<vector<int>>& GetAdjacencyList() const {
    return adjacency_list_;
  }
  Graph Transpose() const {
    Graph transposed(vertex_count_);
    for (int from = 1; from <= vertex_count_; ++from) {
      for (int to : adjacency_list_[from]) {
        transposed.adjacency_list_[to].push_back(from);
      }
    }
    return transposed;
  }
  friend int CalculateStrongConnectedComponents(const Graph& graph,
                                                vector<int>& component);

 private:
  int vertex_count_;
  vector<vector<int>> adjacency_list_;
  void DFS(int v, vector<bool>& visited, vector<int>& result,
           int current_component, vector<int>* component) const {
    visited[v] = true;
    if (component != nullptr) {
      (*component)[v] = current_component;
    }
    for (int u : adjacency_list_[v]) {
      if (!visited[u]) {
        DFS(u, visited, result, current_component, component);
      }
    }
    result.push_back(v);
  }
};

// Основная функция Косарайю
int CalculateStrongConnectedComponents(const Graph& graph,
                                       vector<int>& component) {
  int n = graph.VertexCount();
  vector<bool> visited(n + 1, false);
  vector<int> order;
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      graph.DFS(i, visited, order, -1, nullptr);
    }
  }
  reverse(order.begin(), order.end());
  Graph transposed = graph.Transpose();
  visited.assign(n + 1, false);
  component.assign(n + 1, 0);
  int comp_id = 1;
  for (int v : order) {
    if (!visited[v]) {
      vector<int> temp;
      transposed.DFS(v, visited, temp, comp_id, &component);
      ++comp_id;
    }
  }
  return comp_id - 1;
}

int main() {
  int n;
  int m;
  cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int from;
    int to;
    cin >> from >> to;
    graph.AddEdge(from, to);
  }
  vector<int> component;
  int total = CalculateStrongConnectedComponents(graph, component);
  cout << total << endl;
  for (int i = 1; i <= n; ++i) {
    cout << component[i] << ' ';
  }
  cout << endl;
}
