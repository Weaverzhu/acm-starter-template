#include <bits/stdc++.h>
using namespace std;

default_random_engine dre(time(0));
template<typename T>
T randint(T l, T r) {
    
    uniform_int_distribution<T> u(l, r);
    return u(dre);
}

string randstr(int len) {
    string s = "";
    for (int i=0; i<len; ++i) {
        s = s + (char)(randint(0, 25) + 'a');
    }
    return s;
}

template<typename T>
pair<T, T> randpair(T l, T r) {
    T lx, rx;
    for (lx=randint(l, r), rx = randint(l, r); lx==rx; lx=randint(l,r), rx=randint(l,r));
    return make_pair(lx, rx);
}

vector< pair<int, int> > genRandomConnectedBiGraph(int n, int m) {
    vector<int> f(n + 1, 0);
    for (int i=2; i<=n; ++i) {
        f[i] = randint(1, i-1);
    }
    vector< pair<int, int> > res;
    for (int i=2; i<=n; ++i)
        res.emplace_back(i, f[i]);
    for (int i=n-1; i<m; ++i) {
        int a = randint(1, n), b = randint(1, n);
        res.emplace_back(a, b);
    }
    return res;
}

int main(int argc, char const *argv[])
{
    int n = randint(3, 7), m = randint(n-1, n * (n-1) / 2), a = randint(1, n), b = randint(1, n);
    auto dat = genRandomConnectedBiGraph(n, m);
    for (auto &p : dat) {
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}
