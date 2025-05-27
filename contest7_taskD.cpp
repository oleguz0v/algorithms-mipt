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

  const vector<int>& GetNeighbors(int vertex_id) const {
    return adjacency_list_[vertex_id];
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

 private:
  int vertex_count_;
  vector<vector<int>> adjacency_list_;
};

void GetOrderOfTheVertexesForKosaraju(const Graph& graph, int v,
                                      vector<bool>& visited,
                                      vector<int>& result,
                                      int current_component,
                                      vector<int>* component) {
  visited[v] = true;
  if (component != nullptr) {
    (*component)[v] = current_component;
  }
  for (int u : graph.GetNeighbors(v)) {
    if (!visited[u]) {
      GetOrderOfTheVertexesForKosaraju(graph, u, visited, result,
                                       current_component, component);
    }
  }
  result.push_back(v);
}

// Основная функция Косарайю
int CalculateStrongConnectedComponents(const Graph& graph, vector<int>& component) {
  int n = graph.VertexCount();
  vector<bool> visited(n + 1, false);
  vector<int> order;

  // Заполнение order с использованием поиска в глубину (DFS)
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      GetOrderOfTheVertexesForKosaraju(graph, i, visited, order, -1, nullptr);
    }
  }

  // Переворачиваем порядок обхода
  reverse(order.begin(), order.end());

  // Транспонированный граф
  Graph transposed = graph.Transpose();

  visited.assign(n + 1, false);
  component.assign(n + 1, 0);
  int comp_id = 1;

  // Выполняем DFS на транспонированном графе для получения компонент
  for (int v : order) {
    if (!visited[v]) {
      vector<int> temp;
      GetOrderOfTheVertexesForKosaraju(transposed, v, visited, temp, comp_id,
                                       &component);
      ++comp_id;
    }
  }

  return comp_id - 1;
}

int main() {
  int n;
  int m;
  cin >> n >> m;

  // Создание графа
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int from;
    int to;
    cin >> from >> to;
    graph.AddEdge(from, to);
  }

  // Рассчёт компонент сильной связности
  vector<int> component;
  int total = CalculateStrongConnectedComponents(graph, component);

  // Вывод результата
  cout << total << endl;
  for (int i = 1; i <= n; ++i) {
    cout << component[i] << ' ';
  }
  cout << endl;

  return 0;
}
