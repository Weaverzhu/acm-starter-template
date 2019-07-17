#include <bits/stdc++.h>
using namespace std;
int MAXN = 10000;
int randint(int l, int r) {
    return rand()%(r-l+1) + l;
}
int main() {
    srand(time(0));
    int n = 10, m = n;
    printf("%d %d\n", n, m);
    for (int i=0; i<n; ++i) {
        int l = randint(1, 20), r = randint(1, 20);
        if (l > r) swap(l, r);
        printf("%d %d\n", l, r);
    }
    for (int i=0; i<n; ++i) {
        int l = randint(1, 20), r = randint(1, 20);
        if (l > r) swap(l, r);
        printf("%d %d\n", l, r);
    }
    return 0;
}