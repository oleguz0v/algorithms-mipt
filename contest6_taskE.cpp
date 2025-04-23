#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::reverse;
using std::vector;

// Решает задачу 0/1 рюкзака и выводит номера предметов в решении

void ReadInput(int n, vector<int>& w, vector<int>& c) {
  for (int i = 1; i <= n; ++i) {
    cin >> w[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> c[i];
  }
}

void SolveKnapsack(int n, int m, const vector<int>& w, const vector<int>& c,
                   vector<vector<int>>& dp) {
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j >= w[i]) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i]] + c[i]);
      }
    }
  }
}

vector<int> ReconstructAnswer(int n, int m, const vector<int>& w,
                              const vector<vector<int>>& dp) {
  vector<int> ans;
  int j = m;
  for (int i = n; i > 0; --i) {
    if (dp[i][j] != dp[i - 1][j]) {
      ans.push_back(i);
      j -= w[i];
    }
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

void OutputAnswer(const vector<int>& ans) {
  for (int i = 0; i < (int)ans.size(); ++i) {
    cout << ans[i] << endl;
  }
}

int main() {
  int n;
  int m;
  cin >> n;
  cin >> m;
  vector<int> w(n + 1);
  vector<int> c(n + 1);
  ReadInput(n, w, c);
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  SolveKnapsack(n, m, w, c, dp);
  vector<int> ans = ReconstructAnswer(n, m, w, dp);
  OutputAnswer(ans);
}
