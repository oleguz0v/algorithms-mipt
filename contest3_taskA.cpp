#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

const int cInf = 1e9;

class SparseTable {
 public:
  SparseTable(const std::vector<int>& array) {
    n_ = (int)array.size();
    a_ = array;
    PrecomputeLog();
    BuildTable();
  }

  int Query(int l, int r) const {
    int d = flog2_[r - l];
    if (m_[d][l][0] < m_[d][r - (1 << d)][0]) {
      return m_[d][l][1];
    }
    return m_[d][r - (1 << d)][1];
  }

 private:
  int n_;
  std::vector<int> a_;
  std::vector<std::vector<std::vector<int>>> m_;
  std::vector<int> flog2_;

  void PrecomputeLog() {
    flog2_.resize(n_ + 1);
    for (int i = 2; i <= n_; ++i) {
      flog2_[i] = flog2_[i / 2] + 1;
    }
  }

  void BuildTable() {
    m_.resize(flog2_[n_] + 1, std::vector<std::vector<int>>(n_));
    for (int i = 0; i < n_; ++i) {
      m_[0][i].push_back(a_[i]);
      m_[0][i].push_back(i);
    }
    for (int d = 1; d <= flog2_[n_]; ++d) {
      for (int i = 0; i + (1 << d) <= n_; ++i) {
        if (m_[d - 1][i][0] < m_[d - 1][i + (1 << (d - 1))][0]) {
          m_[d][i] = m_[d - 1][i];
        } else {
          m_[d][i] = m_[d - 1][i + (1 << (d - 1))];
        }
      }
    }
  }
};

int FindSecondMinimum(const SparseTable& st, const std::vector<int>& a, int l,
                      int r) {
  int min_seg = st.Query(l - 1, r);
  int minl;
  if (l - 1 == min_seg) {
    minl = cInf;
  } else {
    minl = a[st.Query(l - 1, min_seg)];
  }
  int minr;
  if (min_seg + 1 == r) {
    minr = cInf;
  } else {
    minr = a[st.Query(min_seg + 1, r)];
  }
  return std::min(minl, minr);
}

int main() {
  int n;
  int q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  SparseTable st(a);
  for (int i = 0; i < q; ++i) {
    int l;
    int r;
    std::cin >> l >> r;
    std::cout << FindSecondMinimum(st, a, l, r) << '\n';
  }
}
