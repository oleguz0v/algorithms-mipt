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

const int cInf = 2009000999;

class Graph {
 public:
  explicit Graph(int vertex_count) {
    vertex_count_ = vertex_count;
    adjacency_list_.resize(vertex_count_);
    distances_.assign(vertex_count_, cInf);
  }

  void AddEdge(int from, int to, int cost) {
    adjacency_list_[from].push_back({to, cost});
    adjacency_list_[to].push_back({from, cost});
  }

  void RunDijkstra(int start_vertex) {
    distances_.assign(vertex_count_, cInf);
    distances_[start_vertex] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push({0, start_vertex});
    while (!pq.empty()) {
      int current = pq.top().second;
      int dist = -pq.top().first;
      pq.pop();
      if (distances_[current] < dist) {
        continue;
      }
      for (auto [neighbor, weight] : adjacency_list_[current]) {
        if (distances_[neighbor] > distances_[current] + weight) {
          distances_[neighbor] = distances_[current] + weight;
          pq.push({-distances_[neighbor], neighbor});
        }
      }
    }
  }

  void PrintDistances() const {
    for (int i = 0; i < vertex_count_; ++i) {
      cout << distances_[i] << ' ';
    }
    cout << endl;
  }

 private:
  int vertex_count_;
  vector<vector<pair<int, int>>> adjacency_list_;
  vector<int> distances_;
};

void SolveDijkstraTests() {
  int test_count;
  cin >> test_count;
  while (test_count-- > 0) {
    int vertex_count;
    int edge_count;
    cin >> vertex_count >> edge_count;
    Graph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
      int u;
      int v;
      int w;
      cin >> u >> v >> w;
      graph.AddEdge(u, v, w);
    }
    int start_vertex;
    cin >> start_vertex;
    graph.RunDijkstra(start_vertex);
    graph.PrintDistances();
  }
}

int main() { SolveDijkstraTests(); }
