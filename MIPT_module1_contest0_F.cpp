#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

const int cInf = 1e9;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int n;
  int m;
  int l;
  std::cin >> n >> m >> l;
  std::vector<std::vector<int>> a(n, std::vector<int>(l));
  std::vector<std::vector<int>> b(m, std::vector<int>(l));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < l; ++j) {
      std::cin >> a[i][j];
    }
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < l; ++j) {
      std::cin >> b[i][j];
    }
  }
  int q;
  std::cin >> q;
  int p_a;
  int p_b;
  for (int i = 0; i < q; ++i) {
    std::cin >> p_a >> p_b;
    --p_a;
    --p_b;
    int min_maxi = cInf;
    int indmm = -1;
    for (int k = 0; k < l; ++k) {
      if (min_maxi > std::max(a[p_a][k], b[p_b][k])) {
        min_maxi = std::max(a[p_a][k], b[p_b][k]);
        indmm = k + 1;
      }
    }
    std::cout << indmm << '\n';
  }
}