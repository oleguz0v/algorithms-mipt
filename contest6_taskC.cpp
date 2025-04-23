#include <iostream>
#include <vector>

typedef long long Ll;

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::vector;

const int cMaxB = 30;

int f;
int b;

vector<Ll> dp;

bool IsImpossible() { return f > 1 and b == 0; }

void Initialize() {
  b = min(b, cMaxB);
  dp.resize(b + 1);
  for (int i = 0; i <= b; ++i) {
    dp[i] = 0;
  }
}

Ll ComputeMinimumTries() {
  Ll tries = 0;
  while (f - 1 > dp[b]) {
    for (int i = b; i > 0; --i) {
      dp[i] = dp[i] + 1 + dp[i - 1];
    }
    tries = tries + 1;
  }
  return tries;
}

int main() {
  cin >> f;
  cin >> b;
  if (IsImpossible()) {
    cout << -1 << endl;
    return 0;
  }
  Initialize();
  Ll result = ComputeMinimumTries();
  cout << result << endl;
}
