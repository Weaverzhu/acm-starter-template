#include <bits/stdc++.h>
using namespace std;

#define zerol

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



const int N = 1e6+5, MOD = 998244353, K = 505;

LL n;
int k;
LL invd[N], invf[N], f[N];

int id1[N], id2[N];
LL w[N], g[N], B;
int m;

LL j[N];

inline int id(LL x) { return x <= B? id1[x]:id2[n/x];}

void precalc(LL n) {
    B = sqrt(n) + 1;
    // int m = 0;
    m = 0;
    for (LL l=1, r, v; l<=n; l=r+1) {
        v = n / l;
        r = n / v;
        if (v <= B) id1[v] = m;
        else id2[r] = m;
        w[m++] = v;
    }
}

LL bin(LL a, LL b, LL p = MOD) {
    LL res = 1;
    for (; b; b>>=1, a=a*a%p)
        if (b & 1) res = res * a % p;
    return res;
}

LL inv(LL a, LL p) { return bin(a, p-2, p);}

namespace interpolation {
    void go(LL y[], int n, LL xx[], int m, LL ans[]) {
        dbg(n, xx[0]);
        for (int j=0; j<m; ++j) {
            // if (x == -1) return 0;
            LL x = xx[j];
            if (x < n) {
                ans[j] = y[x];
                continue;
            }
            LL res = 0;
            for (int i=0; i<n; ++i) {
                dbg(i, f[x], bin(x-1, MOD-2, MOD), invf[x-n]);
                // , invf[n-1-i], invf[i], y[i], x-n, n-1-i);
                
                LL del = f[x] * invd[x-i] % MOD * invf[x-n] % MOD;
                int sgn = (n-i-1)%2? -1:1;
                del = del * sgn * invf[n-1-i] % MOD * invf[i] % MOD;
                del = (del + MOD) % MOD * y[i] % MOD;
                res = (res + MOD + del) % MOD;
                // dbg(sgn, del, i);
                dbg(i);
            }
            ans[j] = res;
        }
     
    }
}
int prime[N], pcnt, minp[N];
LL jor[N], sjor[N];
void init() {
    for (int i=2; i<N; ++i) {
        if (!minp[i]) {
            prime[pcnt++] = i;
            minp[i] = i;
            jor[i] = bin(i, k) - 1;
        }
        for (int j=0; j<pcnt; ++j) {
            LL nextp = 1LL * i * prime[j];
            if (nextp >= N) break;
            if (!minp[nextp]) minp[nextp] = prime[j];
            if (i % prime[j] == 0) {
                jor[nextp] = jor[i];
                break;
            } else {
                jor[nextp] = jor[i] * jor[prime[j]];
            }
        }
    }
    for (int i=1; i<N; ++i)
        sjor[i] = (sjor[i-1] + jor[i]) % MOD;
}

LL nk(LL n) {
    int idv = id(n);
    return g[idv];
}

unordered_map<LL, LL> mpj;

LL jors(LL n) {
    if (n < N) return sjor[n];
    else {
        if (mpj.find(n) != mpj.end()) return mpj[n];
        LL res = 0;
        for (LL l=2, r, v; l<=n; l=r+1) {
            LL del = (r-l+1);
            res = (res + del * jors(n)) % MOD;
        }
        res = nk(n) + MOD - res;
        res %= MOD;
        return mpj[n] = res;
    }
}

LL y[K];

// const int N = 1e6+5;




int main(int argc, char const *argv[])
{
    invd[1] =1;
    for (int i=2; i<N; ++i)
        invd[i] = (MOD - MOD / i) * invd[MOD % i] % MOD;
    f[0] = f[1] = invf[0] = invf[1] = 1;
    for (int i=2; i<N; ++i)
        f[i] = f[i-1] * i % MOD;
    invf[N-1] = inv(f[N-1], MOD);
    for (int i=N-2; i>=2; --i) {
        invf[i] = (invf[i+1]) * (i+1) % MOD;
    }

    // for (int i=0; i<5; ++i)
    //     dbg(i, invd[i], invf[i], f[i]);

    // return 0;

    cin >> n >> k;
    dbg(n, k);
    init();
    // dbg("fuck");
    precalc(n);
    y[0] = 0;
    for (int i=1; i<=k; ++i) {
        // dbg(i);
        y[i] = (y[i-1] + bin(i, k, MOD)) % MOD;
        // interpolation::go(y, n+1, w, m, g);
    }
    // return 0;
    interpolation::go(y, k+1, w, m, g);
    // return 0;
    printf("%Lld\n", jors(n));

    return 0;
}

