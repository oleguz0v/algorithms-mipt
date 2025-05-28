#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::vector;

class Graph {
 public:
  explicit Graph(int left_size, int right_size) {
    left_size_ = left_size;
    right_size_ = right_size;
    adj_list_.resize(left_size_ + 1);
    matching_.assign(right_size_ + 1, -1);
  }

  void AddEdge(int left_vertex, const vector<int>& right_vertices) {
    for (int right_vertex : right_vertices) {
      adj_list_[left_vertex].push_back(right_vertex);
    }
  }

  int FindMaxMatching() {
    int match_count = 0;
    for (int left_vertex = 1; left_vertex <= left_size_; ++left_vertex) {
      used_.assign(left_size_ + 1, false);
      if (FindMatch(left_vertex)) {
        ++match_count;
      }
    }
    return match_count;
  }

  vector<pair<int, int>> GetMatching() const {
    vector<pair<int, int>> result;
    for (int right_vertex = 1; right_vertex <= right_size_; ++right_vertex) {
      if (matching_[right_vertex] != -1) {
        result.push_back({matching_[right_vertex], right_vertex});
      }
    }
    return result;
  }

 private:
  int left_size_;
  int right_size_;
  vector<vector<int>> adj_list_;
  vector<int> matching_;
  vector<bool> used_;

  bool FindMatch(int left_vertex) {
    if (used_[left_vertex]) {
      return false;
    }
    used_[left_vertex] = true;
    for (int right_vertex : adj_list_[left_vertex]) {
      if (matching_[right_vertex] == -1 || FindMatch(matching_[right_vertex])) {
        matching_[right_vertex] = left_vertex;
        return true;
      }
    }
    return false;
  }
};

void ReadGraph(Graph& graph, int left_size) {
  for (int i = 1; i <= left_size; ++i) {
    vector<int> right_vertices;
    while (true) {
      int right_vertex;
      cin >> right_vertex;
      if (right_vertex == 0) {
        break;
      }
      right_vertices.push_back(right_vertex);
    }
    graph.AddEdge(i, right_vertices);
  }
}

void PrintResult(int matching_size, const vector<pair<int, int>>& matching) {
  cout << matching_size << endl;
  for (const auto& match : matching) {
    cout << match.first << ' ' << match.second << endl;
  }
}

int main() {
  int left_size;
  int right_size;
  cin >> left_size >> right_size;
  Graph graph(left_size, right_size);
  ReadGraph(graph, left_size);
  int matching_size = graph.FindMaxMatching();
  vector<pair<int, int>> matching = graph.GetMatching();
  PrintResult(matching_size, matching);
}
