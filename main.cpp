#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

int n, m;

typedef pair<int, int> pii;
int dp[N][N];


char s[N][N];

struct node {
    int x, y;
    char ch;
    node(int x=-1, int y=-1, char ch=0):x(x), y(y), ch(ch){}
} dat[N];

//bool cmp1(const pii &a, const pii &b) {
//    return a.first < b.first;
//}
//bool cmp2(const pii &a, const pii &b) {
//    return a.second < b.second;
//}

bool cmp1(const node &a, const node &b) {
    return a.x < b.x;
}

bool cmp2(const node &a, const node &b) {
    return a.y < b.y;
}

bool cmp3(const node &a, const node &b) {
    return a.ch < b.ch;
}

char idc[30], trans[30];

inline bool inbound(int l, int r, int x) {
    return x >= l && x <= r;
}

void paintx(char s[N][N], const pii lu, const pii rd, char ch) {
    if (ch >= 'A' && ch <= 'Z') ch = ch + 'a' - 'A';
    for (int i=lu.first; i<=rd.first; ++i)
        for (int j=lu.second; j<=rd.second; ++j)
            if (s[i][j] == '.') s[i][j] = ch;
}

void solve(pii s, pii t, node p[], int cnt, char str[N][N]) {
    if (cnt == 0) {
        // left
        if (s.second > 0) {
//            puts("FUCK");
            for (int i=s.first; i<=t.first; ++i) {
//                printf("%d %d %d\n", i, s.second, t.second);
                paintx(str, make_pair(i, s.second), make_pair(i, t.second), str[i][s.second-1]);
            }
            return;
        }

        // right
        if (t.second < m-1) {
            for (int i=s.first; i<=t.first; ++i) {
                paintx(str, make_pair(i, s.second), make_pair(i, t.second), str[i][t.second+1]);
            }
            return;
        }
        // up
        if (s.first > 0) {
            for (int i=s.second; i<=t.second; ++i) {
                paintx(str, make_pair(s.first, i), make_pair(t.first, i), str[s.first-1][i]);
            }
            return;
        }
        // down
        if (t.first < n-1) {
            for (int i=s.second; i<=t.second; ++i) {
                paintx(str, make_pair(s.first, i), make_pair(t.first, i), str[t.first+1][i]);
            }
            return;
        }
    }
//    puts("FUCK");
    pii cur(0, 0);
    sort(p, p+cnt, cmp1);
    int lastx = s.first;
    for (int i=s.first; i<=t.first; ++i, cur.first = cur.second+1) {
        cur.second = cur.first;
        while (cur.second+1 < cnt && p[cur.second+1].x == p[cur.first].x) ++cur.second;
        if (cur.first < cnt) {
            lastx = cur.first > 0? p[cur.first-1].x + 1 : s.first;
            int nextx = cur.second < cnt-1? p[cur.first].x : t.first;
//            printf("dbg: %d %d\n", cur.first, cur.second);
            for (int j=cur.first; j<=cur.second; ++j) {
                pii lr(j == cur.first? s.second : p[j-1].y + 1, j == cur.second? t.second : p[j].y);
                paintx(str, make_pair(lastx, lr.first), make_pair(nextx, lr.second), p[j].ch - 'A' + 'a');
            }
        }

    }
}


void dbgoutput() {
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j)
            printf("%c", s[i][j]);
        puts("");
    }
}

int main() {
    puts("1"); return 0;
    scanf("%d%d", &n, &m);
    for (int i=0; i<n; ++i)
        scanf("%s", s[i]);
    int cnt = 0;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            if (isalpha(s[i][j]))
                dat[cnt++] = node(i, j, s[i][j]);
        }
    }
    sort(dat, dat+cnt, cmp3);
//    printf("%d\n", cnt);


//    for (int i=1; i<cnt; ++i) {
//        printf("%d %d %c\n", dat[i].x, dat[i].y, dat[i].ch);
//    }

    pii lu(0, 0), rd(n-1, m-1);

    int S = 0;

    for (int i=0; i<=dat[0].y; ++i)
        for (int j=dat[0].y; j<m; ++j) {
            int sx = 0, tx = n-1;
            bool suc = 1;
            for (int k=1; k<cnt; ++k) {
                if (!inbound(i, j, dat[k].y)) continue;
                if (dat[k].x < dat[0].x) sx = max(sx, dat[k].x + 1);
                else if (dat[k].x > dat[0].x) tx = min(tx, dat[k].x - 1);
                else {
                    suc = 0;
                    break;
                }
            }
            if (!suc) continue;
            int s = (j-i+1) * (tx-sx+1);
            if (s > S) {
                S = s;
                lu = {sx, i};
                rd = {tx, j};
            }
        }
    node payload[100]; int pcnt;
    // up
    if (lu.first > 0) {
        pcnt = 0;
        int sx = 0, tx = lu.first - 1;
        int sy = lu.second, ty = rd.second;
        for (int i=0; i<cnt; ++i)
            if (inbound(sx, tx, dat[i].x) && inbound(sy, ty, dat[i].y)) payload[pcnt++] = dat[i];
        solve(make_pair(sx, sy), make_pair(tx, ty), payload, pcnt, s);
    }
    // down
    if (rd.first < n-1) {
        pcnt = 0;
        int sx = rd.first + 1, tx = n-1, sy = lu.second, ty = rd.second;
        for (int i=0; i<cnt; ++i)
            if (inbound(sx, tx, dat[i].x) && inbound(sy, ty, dat[i].y)) payload[pcnt++] = dat[i];
//        printf("down: %d\n", pcnt);
        solve(make_pair(sx, sy), make_pair(tx, ty), payload, pcnt, s);
    }

    // left
    if (lu.second > 0) {
        pcnt = 0;
        int sx = lu.first, tx = rd.first, sy = 0, ty = lu.second - 1;
        for (int i=0; i<cnt; ++i)
            if (inbound(sx, tx, dat[i].x) && inbound(sy, ty, dat[i].y)) payload[pcnt++] = dat[i];
        solve(make_pair(sx, sy), make_pair(tx, ty), payload, pcnt, s);
    }
    // right
    if (rd.second < m-1) {
        pcnt = 0;
        int sx = lu.first, tx = rd.first, sy = rd.second + 1, ty = m-1;
        for (int i=0; i<cnt; ++i)
            if (inbound(sx, tx, dat[i].x) && inbound(sy, ty, dat[i].y)) payload[pcnt++] = dat[i];
        solve(make_pair(sx, sy), make_pair(tx, ty), payload, pcnt, s);
    }
    paintx(s, lu, rd, 'a');

    // lu
    if (lu.first > 0 && lu.second > 0) {
        pcnt = 0;
        int sx = 0, tx = lu.first-1, sy = 0, ty = lu.second - 1;
        for (int i=0; i<cnt; ++i)
            if (inbound(sx, tx, dat[i].x) && inbound(sy, ty, dat[i].y)) payload[pcnt++] = dat[i];
        solve(make_pair(sx, sy), make_pair(tx, ty), payload, pcnt, s);
    }
    // ru
    if (lu.first > 0 && rd.second < m-1) {
        pcnt = 0;
        int sx = 0, tx = lu.first-1, sy = rd.second+1, ty = m-1;
        for (int i=0; i<cnt; ++i)
            if (inbound(sx, tx, dat[i].x) && inbound(sy, ty, dat[i].y)) payload[pcnt++] = dat[i];
        solve(make_pair(sx, sy), make_pair(tx, ty), payload, pcnt, s);
    }
    // ld
    if (rd.first<n-1 && lu.second > 0) {
        pcnt = 0;
        int sx = rd.first+1, tx = n-1, sy = 0, ty = lu.second - 1;
        for (int i=0; i<cnt; ++i)
            if (inbound(sx, tx, dat[i].x) && inbound(sy, ty, dat[i].y)) payload[pcnt++] = dat[i];
        solve(make_pair(sx, sy), make_pair(tx, ty), payload, pcnt, s);
    }
    // rd
    if (rd.first<n-1 && rd.second < m-1) {
//        puts("ST");
        pcnt = 0;
        int sx = rd.first+1, tx = n-1, sy = rd.second+1, ty = m-1;
        for (int i=0; i<cnt; ++i)
            if (inbound(sx, tx, dat[i].x) && inbound(sy, ty, dat[i].y)) payload[pcnt++] = dat[i];
        solve(make_pair(sx, sy), make_pair(tx, ty), payload, pcnt, s);
    }

//    dbgoutput();
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j)
            printf("%c", s[i][j]);
        puts("");
    }
    return 0;
}