#include <bits/stdc++.h>
using namespace std;

/**
  Segment tree implementation using tempates
  @author theseems
  
  WIKI: https://en.wikipedia.org/wiki/Segment_tree
  Habr (Russian): https://habr.com/ru/post/128787/
**/

template <class T>
class seg_tree {
 private:
  vector<T> tree, change;
  int bit_size = 1;

  void __push(int vtx, int l, int r) {
    if (l == r) {
      modify(tree[vtx], change[vtx]);
      change[vtx] = def;
      return;
    }

    modify(tree[vtx], change[vtx]);
    modify(change[2 * vtx], change[vtx]);
    modify(change[2 * vtx + 1], change[vtx]);
    change[vtx] = def;
  }

  T __get(int vtx, int tl, int tr, const int l, const int r) {
    if (l > tr || r < tl) return neutral;
    __push(vtx, tl, tr);
    if (l <= tl && tr <= r) {
      return tree[vtx];
    } else {
      int mid = (tl + tr) / 2;
      auto left = __get(2 * vtx, tl, mid, l, r);
      auto right = __get(2 * vtx + 1, mid + 1, tr, l, r);
      if (compare(left, right)) {
        return left;
      } else {
        return right;
      }
    }
  }

  void __update(int vtx, int tl, int tr, const int l, const int r, T value) {
    if (l > tr || r < tl) {
      __push(vtx, tl, tr);
      return;
    }
    if (l <= tl && tr <= r) {
      modify(change[vtx], value);
      __push(vtx, tl, tr);
      return;
    }

    __push(vtx, tl, tr);
    int mid = (tl + tr) / 2;
    __update(2 * vtx, tl, mid, l, r, value);
    __update(2 * vtx + 1, mid + 1, tr, l, r, value);
    auto left = tree[2 * vtx], right = tree[2 * vtx + 1];
    if (compare(left, right)) {
      tree[vtx] = left;
    } else {
      tree[vtx] = right;
    }
  }

 public:
  function<bool(T, T)> compare;
  function<void(T &, T &)> modify;

  T neutral, def;

  void build(const vector<T> &src) {
    while (bit_size < src.size()) bit_size *= 2;
    tree.resize(2 * bit_size, neutral);
    change.resize(2 * bit_size, def);

    for (int i = 0; i < src.size(); i++) {
      tree[bit_size + i] = src[i];
    }
    for (int i = bit_size - 1; i > 0; i--) {
      if (compare(tree[2 * i], tree[2 * i + 1])) {
        tree[i] = tree[2 * i];
      } else {
        tree[i] = tree[2 * i + 1];
      }
    }
  }

  void update(const int l, const int r, T value) {
    __update(1, 0, bit_size - 1, l, r, value);
  }

  void update_single(const int index, T value) { update(index, index, value); }

  T get(const int l, const int r) { return __get(1, 0, bit_size - 1, l, r); }

  T get_single(const int index) { return get(index, index); }

  seg_tree(function<bool(T, T)> compare, function<void(T &, T &)> modify,
           T neutral, T def)
      : compare(compare), modify(modify), neutral(neutral), def(def) {}
};

int main() {
  // Simple task solve using seg_tree
  // Source:
  // https://informatics.mccme.ru/mod/statements/view3.php?id=12099&chapterid=3328

  int n;
  cin >> n;

  vector<int> input(n);
  for (int i = 0; i < n; i++) {
    cin >> input[i];
  }

  // Building segment tree
  auto tree = seg_tree<int>(
      // Get maximum
      [](int a, int b) -> bool { return a > b ? true : false; },
      // Addition of two arguments
      [](int &a, int &b) { a += b; },
      // Minimum (in this task it can be a zero)
      -1e9,
      // Default integer value (default modify value)
      0);

  tree.build(input);

  int q;
  cin >> q;

  for (int i = 0; i < q; i++) {
    char q;
    int l, r;

    cin >> q >> l >> r;
    l--, r--;

    if (q == 'm') {
      cout << tree.get(l, r) << endl;
    } else {
      int value;
      cin >> value;
      tree.update(l, r, value);
    }
  }

  return 0;
}
