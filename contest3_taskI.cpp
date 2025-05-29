/*
 Дан массив a. Требуется для каждого запроса l, r, x, y найти
 количество элементов на отрезке массива с l по r, значения
 которых лежат  в отрезке [x, y].
 */

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class SegmentTree {
 public:
  SegmentTree(vector<int>& array);

  size_t CountInRange(int q_l, int q_r, int x);

 private:
  int n_;
  vector<int> a_;
  vector<vector<int>> tree_;

  void Build(int i, int l, int r);
  void static MergeNodes(vector<int>& left, vector<int>& right,
                         vector<int>& parent);
  size_t Query(int i, int l, int r, int q_l, int q_r, int x);
  size_t static CountLessOrEqual(vector<int>& node, int x);
};

SegmentTree::SegmentTree(vector<int>& array) {
  n_ = (int)array.size();
  a_ = array;
  tree_.resize(4 * n_);
  Build(0, 0, n_);
}

void SegmentTree::Build(int i, int l, int r) {
  tree_[i].push_back(0);
  if (l + 1 == r) {
    tree_[i].push_back(a_[l]);
  } else {
    int m = (l + r) / 2;
    Build(2 * i + 1, l, m);
    Build(2 * i + 2, m, r);
    MergeNodes(tree_[2 * i + 1], tree_[2 * i + 2], tree_[i]);
  }
}

size_t SegmentTree::CountInRange(int q_l, int q_r, int x) {
  return Query(0, 0, n_, q_l, q_r, x);
}

void SegmentTree::MergeNodes(vector<int>& left, vector<int>& right,
                             vector<int>& parent) {
  size_t p1 = 0;
  size_t p2 = 0;
  while (p1 < left.size() and p2 < right.size()) {
    if (left[p1] < right[p2]) {
      parent.push_back(left[p1++]);
    } else {
      parent.push_back(right[p2++]);
    }
  }
  while (p1 < left.size()) {
    parent.push_back(left[p1++]);
  }
  while (p2 < right.size()) {
    parent.push_back(right[p2++]);
  }
}

size_t SegmentTree::Query(int i, int l, int r, int q_l, int q_r, int x) {
  if (q_r <= l or r <= q_l) {
    return 0;
  }
  if (q_l <= l and r <= q_r) {
    return CountLessOrEqual(tree_[i], x);
  }
  int m = (l + r) / 2;
  return Query(2 * i + 1, l, m, q_l, q_r, x) +
         Query(2 * i + 2, m, r, q_l, q_r, x);
}

size_t SegmentTree::CountLessOrEqual(vector<int>& node, int x) {
  size_t l_p = 0;
  size_t r_p = node.size();
  while (r_p - l_p > 1) {
    size_t buf = (l_p + r_p) / 2;
    if (node[buf] <= x) {
      l_p = buf;
    } else {
      r_p = buf;
    }
  }
  return l_p + 1;
}

int main() {
  int n;
  int q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  SegmentTree st(a);
  for (int i = 0; i < q; ++i) {
    int l;
    int r;
    int x;
    int y;
    cin >> l >> r >> x >> y;
    --l;
    cout << st.CountInRange(l, r, y) - st.CountInRange(l, r, x - 1) << endl;
  }
}
