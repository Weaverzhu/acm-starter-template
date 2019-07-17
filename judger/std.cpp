#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#include <algorithm>
#include <iostream>
#include <vector>
 
using namespace __gnu_pbds;
using namespace std;
 
template <typename T>
using oset =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
const int maxn = 200005;
 
int n, x[maxn], y[maxn], idx[maxn];
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
 
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> x[i] >> y[i];
    idx[i] = i;
  }
  sort(idx, idx + n, [&](int i, int j) {
    if (y[i] != y[j])
      return y[i] < y[j];
    return x[i] < x[j];
  });
  oset<int> s;
  uint64_t ans = 0;
  for (int i = n - 1; i >= 0;) {
    int z = y[idx[i]];
    int i1 = i;
    while (i1 >= 0 && y[idx[i1]] == z) {
      s.insert(x[idx[i1]]);
      i1 -= 1;
    }
    for (int j = i1 + 1; j <= i; ++j) {
      uint64_t zl = s.order_of_key(x[idx[j]]);
      uint64_t zr = 0;
      if (j == i) {
        zr = s.size();
      } else {
        zr = s.order_of_key(x[idx[j + 1]]);
      }
      ans += (zl + 1) * (zr - zl);
    }
    i = i1;
  }
  cout << ans << '\n';
}