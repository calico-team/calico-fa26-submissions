#include <stdio.h>
#include <math.h>
#include <vector>
#include <utility>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <stack>
#include <string>
#include <string.h>

using namespace std;

const int maxn = 210;
const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};

char s[maxn][maxn];
int m, n, Q;
int fa[maxn * maxn];

void init(){
    int i, j;
    scanf("%d%d%d", &m, &n, &Q);
    for (i = 0; i < m; ++i) scanf("%s", s[i]);
    for (i = 0; i < m * n; ++i) fa[i] = -1;
}

int find_fa(int p){
    int j, k;
    j = p;
    while (fa[j] != -1) j = fa[j];
    while (p != j){
        k = fa[p];
        fa[p] = j;
        p = k;
    }
    
    return j;
}

void work(){
    int x, y, i, nx, ny, A, B;
    for (x = 0; x < m; ++x)
        for (y = 0; y < n; ++y){
            for (i = 0; i < 4; ++i){
                nx = x + dx[i];
                ny = y + dy[i];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n){
                    if (s[x][y] == 'R' && s[nx][ny] == 'B') continue;
                    if (s[x][y] == 'B' && s[nx][ny] == 'R') continue;
                    A = find_fa(x * n + y);
                    B = find_fa(nx * n + ny);
                    if (A != B) fa[A] = B;
                }
            }
        }
    
    for (i = 1; i <= Q; ++i){
        scanf("%d%d%d%d", &x, &y, &nx, &ny);
        A = find_fa(x * n + y);
        B = find_fa(nx * n + ny);
        if (A == B) printf("YES\n");
        else printf("NO\n");
    }
}

int main() {
    int t, T;
    // freopen("e.in", "r", stdin);
    scanf("%d", &T);
    for (t = 1; t <= T; ++t){
        init();
        work();
    }
    return 0;
}