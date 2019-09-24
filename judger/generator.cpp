#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int MAXN = 10000;
int randint(int l, int r) {
    return rand()%(r-l+1) + l;
}
int a[N];
int main() {
    int n = 100000, q = 100000;
    printf("%d %d\n", n, q);
    for (int i=1; i<=n; ++i)
        a[i] = i;
    random_shuffle(a+1, a+n+1);
    for (int i=1; i<=n; ++i) printf("%d ", a[i]);
    for (int i=1; i<=q; ++i) {
        printf("%d %d\n", randint(1, n), randint(1, n));
    }
    return 0;
}