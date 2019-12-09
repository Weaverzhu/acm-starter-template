
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100+5;
char mp[N][N];
bool vis[4][N][N];
int X1,Y1,X2,Y2,x,y,n,m,t,to[4][2] = {0,1,0,-1,1,0,-1,0},cnt = 1;
struct node{
    int x,y;
    int step;
    int Find;
};
void update(node &a){
    if(a.x == X1 && a.Find != 1){   //等于1不改变状态
        int s = min(a.y,Y1) + 1;
        int e = max(a.y,Y1) - 1;
        int flag = 1;
        for(int i = s;i <= e;i++){
            if(mp[X1][i] != '.'){
                flag = 0;
                break;
            }
        }
        if(flag) a.Find = (a.Find == 0? 1 : 3);
    }
    if(a.x == X2 && a.Find != 2){
        int s = min(a.y,Y2) + 1;
        int e = max(a.y,Y2) - 1;
        int flag = 1;
        for(int i = s;i <= e;i++){
            if(mp[X2][i] != '.'){
                flag = 0;
                break;
            }
        }
        if(flag) a.Find = (a.Find == 0? 2 : 3);
    }
    if(a.y == Y1 && a.Find != 1){
        int s = min(a.x,X1) + 1;
        int e = max(a.x,X1) - 1;
        int flag = 1;
        for(int i = s;i <= e;i++){
            if(mp[i][Y1] != '.'){
                flag = 0;
                break;
            }
        }
        if(flag) a.Find = (a.Find == 0? 1 : 3);
    }
    if(a.y == Y2 && a.Find != 2){
        int s = min(a.x,X2) + 1;
        int e = max(a.x,X2) - 1;
        int flag = 1;
        for(int i = s;i <= e;i++){
            if(mp[i][Y2] != '.'){
                flag = 0;
                break;
            }
        }
        if(flag) a.Find = (a.Find == 0? 2 : 3);
    }
}
void BFS(){
    queue<node> q;
    while(!q.empty()) q.pop();
    node a,b;
    a.x = x,a.y = y,a.Find = 0,a.step = 0;
    update(a);
    q.push(a);
    while(!q.empty()){
        a = q.front();q.pop();
        if(a.Find == 3 && a.step <= t){
            printf("Case %d:\n%d\n",cnt++,a.step);
            return;
        }
        for(int i = 0;i < 4;i++){
            b.x = a.x + to[i][0];
            b.y = a.y + to[i][1];
            if(b.x < 1 || b.y < 1 || b.x > n || b.y > m) continue;
            if(mp[b.x][b.y] != '.') continue;
            b.Find = a.Find;
            update(b);
            if(vis[b.Find][b.x][b.y]) continue;
            vis[b.Find][b.x][b.y] = true;
            b.step = a.step + 1;
            q.push(b);
        }
    }
    printf("Case %d:\n-1\n",cnt++);
}
int main(){
    puts("1");
    return 0;
}