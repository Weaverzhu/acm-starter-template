
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long LL;

#define zerol

#define int long long

#define FOR(i, x, y) for (LL i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (LL i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "\033[32;1m" << #args<< " -> "; err(args); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
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


const int N = 4e4+5;

int a[N], k[N], x, y, z, n, p, m, l[N], r[N];
int id[N];

inline int sqr(int x) { return x*x;}

class intervalAddSeg {
protected:
    const static int MAXN = 4e4+5;
    int N, dat[MAXN<<2], add[MAXN<<2];
public:
    
    inline virtual int INF() {
        int *a = NULL;
        printf("%d\n", *a);
        exit(-1);
    }
    void init(int n) {
        N = 1;
        while (N < n) N <<= 1;
        for (int i=N+n; i<=2*N; ++i)
            dat[i] = INF();
        // dbg(N, n);
    }

    inline virtual int cmp(int a, int b) {
        int *aa = NULL;
        printf("%d\n", *aa);
        exit(-1);
    }
    void pd(int rt) {
        if (add[rt]) {
            int ls = rt<<1, rs = rt<<1|1;
            add[ls] += add[rt];
            add[rs] += add[rt];
            dat[ls] += add[rt];
            dat[rs] += add[rt];
            add[rt] = 0;
        }
    }
   
    void pu(int rt) {
        dat[rt] = cmp(dat[rt<<1], dat[rt<<1|1]);
    }
    
    
    int L, R, v;
    int q(int l, int r, int rt) {
        // dbg(L, R, l, r, rt, dat[rt]);
        if (L <= l && r <= R) {
            return dat[rt];
        }
        int m = (l+r) >> 1;
        pd(rt);
        int v1 = INF(), v2 = INF();
        if (L <= m) v1 = q(l, m, rt<<1);
        if (m+1<=R) v2 = q(m+1,r,rt<<1|1);
        pu(rt);
        return cmp(v1, v2);
    }

    void u(int l, int r, int rt, int v) {
        // dbg(L, R, l, r, rt);
        if (L <= l && r <= R) {
            dat[rt] += v;
            add[rt] += v;
            return;
        }
        int m = (l+r) >> 1;
        pd(rt);
        if (L <= m) u(l, m, rt<<1, v);
        if (m+1<=R) u(m+1,r,rt<<1|1, v);
        pu(rt);
        // dbg(L, R, l, r, rt, dat[rt], v, dat[rt<<1], dat[rt<<1|1]);
    }
    inline void u(int l, int r, int v) {
        L = l;
        R = r;
        
        u(1, N, 1, v);
    }
    inline int q(int l, int r) {
        L = l;
        R = r;
        return q(1, N, 1);
    }

};


class segMax: public intervalAddSeg {
public:
    inline int cmp(int a, int b) { return max(a, b); }
    inline int INF() { return -0x3f3f3f3f3f3f3f3fLL;}
    inline void pu(int rt) {
        dat[rt] = max(dat[rt<<1], dat[rt<<1|1]);
    }
} c;

class segMin: public intervalAddSeg {
public:
    inline int cmp(int a, int b) { return min(a, b); }
    inline int INF() { return 0x3f3f3f3f3f3f3f3fLL; }
    inline void pu(int rt) {
        dat[rt] = min(dat[rt<<1], dat[rt<<1|1]);
    }
    
} d;

int sa[N], ans[N];

int cmp(int a, int b) {
    return l[a] == l[b]? r[a]<r[b]:l[a]<l[b];
}

signed main(int argc, char const *argv[])
{
    io >> n >> x >> y >> z >> p;
    for (int i=1; i<=n; ++i) {
        a[i] = (sqr(i-x) + sqr(i-y)+sqr(i-z)) % p + p;
        a[i] %= p;
    }
    io >> m;
    io >> k[1] >> k[2] >> x >> y >> z >> p;
    for (int i=3; i<=m; ++i) {
        k[i] = (x*k[i-1] + y*k[i-2] + z) % p + p;
        k[i] %= p;
    }
    for (int i=1; i<=m; ++i) {
        io >> l[i] >> r[i];
        id[i] = i;
    }
    sort(id+1, id+m+1, cmp);
    for (int i=1; i<=n; ++i)
        sa[i] = sa[i-1] + a[i];

    c.init(m);
    d.init(m);

    for (int i=1; i<=n; ++i)
        dbg(i, a[i]);
    for (int i=1; i<=m; ++i) {
        dbg(i, l[i], r[i], k[i]);
    }

    for (int i=1; i<=m; ++i) {
        dbg(i, id[i], l[id[i]], r[id[i]]);
        c.u(i, i, -sa[r[id[i]]]);
        d.u(i, i, -sa[l[id[i]]-1]);
        
    }
    // dbg("FUCK");
    

    for (int i=1; i<=m; ++i) {
        for (int i=1; i<=m; ++i) {
            dbg(i, c.q(i,i), d.q(i,i));
        }
        // dbg(d.q(1, i), c.q(i, m));
        int A = d.q(1, i), B = c.q(i, m);
        ans[i] = min(k[i], A-B);
        ans[i] = max(ans[i], 0LL);
        c.u(i, m, ans[i]);
        if (i < m) d.u(i+1, m, ans[i]);
    }
    for (int i=1; i<=m; ++i) {
        printf("%d\n", ans[i]); 
    }


    return 0;
}

