#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cout << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cout << a << ' '; err(x...); }
#else
#define dbg(...)
#endif


//--------------------------------------------------------------------------------------------

typedef __int128 LLL;

LL n;

namespace lgcd {
    LLL f(LLL a, LLL b, LLL c, LLL n) {
        LLL res = 0;
        if (n <= 5) {
            for (int i=0; i<=n; ++i) {
                res += (a*i+b)/c;
            }
        } else if (a >= c || b >= c) {
            res = (a/c) * (n*(n+1)/2) + (b/c)*(n+1) + f(a%c, b%c, c, n);
        } else {
            LLL m = (a*n+b)/c;
            res = n * m - f(c, c-b-1, a, m-1);
        }
        return res;
    }
}

LLL g(LLL n, LLL p, LLL q) {
    LLL a = p, b = 0, c = q;
    return lgcd::f(a, b, c, n);
}

LLL cnt(LLL n, LLL p1, LLL q1, LLL p2, LLL q2) {
    return g(n, p1, q1) - g(n, p2, q2);
}


void solve() {
    char input[100];
    scanf("%s", input);
    sscanf(input, "0.%lld", &n);
    LLL p1 = n, p2 = n, q1 = 1, q2 = q1, p = n * 10;
    for (int i=0; i<19; ++i) {
        q1 *= 10;
        q2 *= 10;
    }
    p1 = p1 * 10 + 5;
    p2 = p2 * 10 - 5;

    LLL l = 0, r = 1e9+5;
    while (l < r-1) {
        LLL m = (l+r) >> 1;
        // print(m);
        if (cnt(m, p1, q1, p2, q2) < 1)
            l = m;
        else 
            r = m;
    }
    LLL x = p * r / q1, y = r, g = __gcd(x, y);
    x /= g;
    y /= g;
    LL xx = x, yy = y, gg = __gcd(xx, yy);
    xx /= gg;
    yy /= gg;
    // printf("%lld %lld\n", xx, yy);
    cout << xx << ' ' << yy << endl;
}


int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t); getchar();
    for (int kk=0; kk<t; ++kk)
        solve();
    return 0;
}

