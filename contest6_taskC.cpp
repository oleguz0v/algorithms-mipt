#include <iostream>
#include <vector>

typedef long long Ll;

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::vector;

/*
Предмет динамики:
dp[i] — максимальное количество этажей, которые можно гарантированно
проверить при наличии i оставшихся пробных шаров.

База динамики:
dp[0] = 0 для всех i, так как без шаров невозможно ничего проверить.

Переход в динамике:
Для каждого количества шаров i от большего к меньшему:
- dp[i] = dp[i] + 1 + dp[i-1]
- (то есть: делаем бросок, если он неудачный — у нас i-1 шаров,
если удачный — i шаров и этажей становится меньше)
*/

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
