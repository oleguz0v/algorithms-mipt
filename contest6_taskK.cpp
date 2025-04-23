// Поиск самой длинной убывающей подпоследовательности и ее восстановление.

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

vector<int> ReadArray(int n) {
  vector<int> a;
  a.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  return a;
}

vector<int> ComputeSequence(const vector<int>& a) {
  int n;
  n = (int)a.size();
  vector<int> dp;
  vector<int> pos;
  vector<int> pr;
  vector<int> ind;
  dp.clear();
  pos.clear();
  pr.assign(n, -1);
  ind.resize(n);
  for (int i = 0; i < n; ++i) {
    int x;
    x = (int)(upper_bound(dp.begin(), dp.end(), a[i], std::greater<int>()) -
              dp.begin());
    if (x < (int)dp.size()) {
      dp[x] = a[i];
      pos[x] = i;
    } else {
      dp.push_back(a[i]);
      pos.push_back(i);
    }
    if (x > 0) {
      pr[i] = pos[x - 1];
    }
  }
  vector<int> ans;
  int cur;
  cur = pos.back();
  while (cur != -1) {
    ans.push_back(cur + 1);
    cur = pr[cur];
  }
  std::reverse(ans.begin(), ans.end());
  return ans;
}

void PrintAnswer(const vector<int>& ans) {
  cout << (int)ans.size() << endl;
  for (int i = 0; i < (int)ans.size(); ++i) {
    cout << ans[i] << ' ';
  }
  cout << endl;
}

int main() {
  int n;
  cin >> n;
  vector<int> a;
  a = ReadArray(n);
  vector<int> ans;
  ans = ComputeSequence(a);
  PrintAnswer(ans);
}
