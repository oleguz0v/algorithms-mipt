#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::priority_queue;
using std::vector;

const long long cInf = 1e9;
const long long cLInf = 1e18;

struct Edge {
  int to;
  int rev;
  int cap;
  int cost;
};

class FlowNetwork {
 public:
  explicit FlowNetwork(int vertex_count) {
    vertex_count_ = vertex_count;
    adj_list_.resize(vertex_count_ + 1);
    capacity_.resize(vertex_count_ + 1);
    cost_.resize(vertex_count_ + 1);
    flow_.resize(vertex_count_ + 1);
    reverse_edge_.resize(vertex_count_ + 1);
  }

  void AddEdge(int from, int to, int cap, int cost) {
    adj_list_[from].push_back({to, (int)adj_list_[to].size(), cap, cost});
    adj_list_[to].push_back({from, (int)adj_list_[from].size() - 1, 0, -cost});
    capacity_[from].push_back(cap);
    capacity_[to].push_back(0);
    cost_[from].push_back(cost);
    cost_[to].push_back(-cost);
    flow_[from].push_back(0);
    flow_[to].push_back(0);
    reverse_edge_[from].push_back((int)adj_list_[to].size() - 1);
    reverse_edge_[to].push_back((int)adj_list_[from].size() - 1);
  }

  long long FindMinCostMaxFlow(int source, int sink) {
    long long min_cost = 0;
    while (true) {
      std::vector<long long> dist(vertex_count_ + 1, cLInf);
      std::vector<int> parent(vertex_count_ + 1, -1);
      std::vector<int> edge_index(vertex_count_ + 1, -1);
      dist[source] = 0;
      priority_queue<pair<long long, int>> pq;
      pq.push({0, source});
      while (!pq.empty()) {
        int u = pq.top().second;
        long long d = -pq.top().first;
        pq.pop();
        if (d > dist[u]) {
          continue;
        }
        for (int i = 0; i < (int)adj_list_[u].size(); ++i) {
          const auto& e = adj_list_[u][i];
          if (capacity_[u][i] - flow_[u][i] > 0 and
              dist[e.to] > dist[u] + e.cost) {
            dist[e.to] = dist[u] + e.cost;
            parent[e.to] = u;
            edge_index[e.to] = i;
            pq.push({-dist[e.to], e.to});
          }
        }
      }
      if (dist[sink] == cLInf) {
        break;
      }
      long long push = cInf;
      for (int v = sink; v != source; v = parent[v]) {
        int u = parent[v];
        int idx = edge_index[v];
        push = std::min((int)push, (int)(capacity_[u][idx] - flow_[u][idx]));
      }
      for (int v = sink; v != source; v = parent[v]) {
        int u = parent[v];
        int idx = edge_index[v];
        flow_[u][idx] += push;
        flow_[v][reverse_edge_[u][idx]] -= push;
      }
      min_cost += push * dist[sink];
    }
    return min_cost;
  }

 private:
  int vertex_count_;
  vector<vector<Edge>> adj_list_;
  vector<vector<int>> capacity_;
  vector<vector<int>> cost_;
  vector<vector<int>> flow_;
  vector<vector<int>> reverse_edge_;
};

void ReadGraph(FlowNetwork& network, int edge_count) {
  for (int i = 0; i < edge_count; ++i) {
    int u;
    int v;
    int cap;
    int cost;
    cin >> u >> v >> cap >> cost;
    network.AddEdge(u, v, cap, cost);
  }
}

int main() {
  int vertex_count;
  int edge_count;
  cin >> vertex_count >> edge_count;
  FlowNetwork network(vertex_count);
  ReadGraph(network, edge_count);
  long long min_cost = network.FindMinCostMaxFlow(1, vertex_count);
  cout << min_cost << endl;
}
