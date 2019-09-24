#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define zerol

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

struct ios {
    inline char read(){
        static const int IN_LEN=1<<18|1;
        static char buf[IN_LEN],*s,*t;
        return (s==t)&&(t=(s=buf)+fread(buf,1,IN_LEN,stdin)),s==t?-1:*s++;
    }

    template <typename _Tp> inline ios & operator >> (_Tp&x){
        static char c11,boo;
        for(c11=read(),boo=0;!isdigit(c11);c11=read()){
            if(c11==-1)return *this;
            boo|=c11=='-';
        }
        for(x=0;isdigit(c11);c11=read())x=x*10+(c11^'0');
        boo&&(x=-x);
        return *this;
    }

    int read(char *s) {
        int len = 0;
        char ch;
        for (ch=read(); ch=='\n' || ch == ' '; ch=read());
        if (ch == -1) {
            s[len] = 0;
            return -1;
        }
        for (; ch!='\n' && ch != ' ' && ch != -1;ch=read())
            s[len++] = ch;
        s[len] = 0;
        return len;
    }
} io;


//--------------------------------------------------------------------------------------------

const int N = 1e5+5;

struct point {
    LL x, y;
    int id;
    point (LL x=0, LL y=0, int id=0):x(x), y(y), id(id){}
    point operator - (const point &other) const {
        return point(x-other.x, y-other.y);
    }
    LL operator * (const point &other) const {
        return x * other.y - y * other.x;
    }
    point K(const point &other) {
        point res = *this-other;
        if (res.x < 0) {
            res.x = -res.x;
            res.y = -res.y;
        }
        return res;
    }

    bool operator <= (const LL k) const {
        return y <= k * x;
    }
} sta[N];

int top;

int c[N], n;
LL s[N], L, p[N], dp[N];
int main(int argc, char const *argv[])
{
    io >> n >> L;
    for (int i=1; i<=n; ++i)
    {
        io >> c[i];
        s[i] = s[i-1] + c[i];
        p[i] = s[i]+i;
    }
    ++L;
    for (int i=1; i<=n; ++i) {
        point now(p[i-1], dp[i-1] + p[i-1]*p[i-1], i);
        while (top >= 2 && (sta[top-1] - sta[top-2]) * (now - sta[top-2]) < 0) --top;
        sta[top++] = now;
        int l = 1, r = top-1;
        LL k = 2LL*(L - p[i]);
        int tar;
        if (top == 1 || (r >= 1 && sta[r].K(sta[r-1]) <= k)) {
            tar = r;
        } else {
            while (l < r-1) {
                int m = (l+r) >> 1;
                if (sta[m].K(sta[m-1]) <= k)
                    l = m;
                else r = m;
            }
            tar = l;
        }
        tar = sta[tar].id;
        dp[i] = dp[tar-1] + (p[i]-p[tar-1]-L)*(p[i]-p[tar-1]-L);
    }

    for (int i=1; i<=n; ++i) {
        dbg(i, dp[i], p[i], c[i], s[i]);
    }

    printf("%lld\n", dp[n]);
    return 0;
}

