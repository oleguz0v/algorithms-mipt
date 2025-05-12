// Нахождение мостов в неориентированном графе с помощью поиска в глубину (DFS)

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

class Graph {
 public:
  explicit Graph(int vertex_count) {
    vertex_count_ = vertex_count;
    adjacency_list_.resize(vertex_count_ + 1);
    entry_time_.resize(vertex_count_ + 1);
    low_time_.resize(vertex_count_ + 1);
    visited_.resize(vertex_count_ + 1, false);
    timer_ = 0;
  }

  void AddEdge(int from, int to, int index) {
    adjacency_list_[from].push_back({to, index});
    adjacency_list_[to].push_back({from, index});
  }

  vector<int> GetBridges() {
    bridges_.clear();
    timer_ = 0;
    std::fill(visited_.begin(), visited_.end(), false);
    for (int vertex = 1; vertex <= vertex_count_; ++vertex) {
      if (!visited_[vertex]) {
        SearchBridgesDFS(vertex, -1);
      }
    }
    sort(bridges_.begin(), bridges_.end());
    return bridges_;
  }

 private:
  int vertex_count_;
  int timer_;
  vector<vector<pair<int, int>>> adjacency_list_;
  vector<int> entry_time_;
  vector<int> low_time_;
  vector<bool> visited_;
  vector<int> bridges_;

  void SearchBridgesDFS(int current_vertex, int edge_id_from_parent) {
    visited_[current_vertex] = true;
    entry_time_[current_vertex] = low_time_[current_vertex] = ++timer_;
    for (const auto& [neighbor, edge_id] : adjacency_list_[current_vertex]) {
      if (edge_id == edge_id_from_parent) {
        continue;
      }
      if (visited_[neighbor]) {
        low_time_[current_vertex] =
            min(low_time_[current_vertex], entry_time_[neighbor]);
      } else {
        SearchBridgesDFS(neighbor, edge_id);
        low_time_[current_vertex] =
            min(low_time_[current_vertex], low_time_[neighbor]);
        if (low_time_[neighbor] > entry_time_[current_vertex]) {
          bridges_.push_back(edge_id);
        }
      }
    }
  }
};

void SolveBridgeProblem() {
  int vertex_count;
  int edge_count;
  cin >> vertex_count >> edge_count;

  Graph graph(vertex_count);
  for (int i = 0; i < edge_count; ++i) {
    int from;
    int to;
    cin >> from >> to;
    graph.AddEdge(from, to, i);
  }

  vector<int> bridges = graph.GetBridges();
  cout << bridges.size() << endl;
  for (int index : bridges) {
    cout << index + 1 << ' ';
  }
  cout << endl;
}

int main() { SolveBridgeProblem(); }
