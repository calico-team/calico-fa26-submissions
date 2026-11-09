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

const int maxn = 10050;

vector<int> g[maxn];
int n, m, K, fa[maxn], dep[maxn];

void init(){
    int i;
    scanf("%d%d%d", &n, &m, &K);
    for (i = 1; i <= n; ++i) g[i].clear();
    for (i = 1; i <= n; ++i){
        scanf("%d", &fa[i]);
        if (fa[i] > 0) g[fa[i]].push_back(i);
    }
}

void dfs(int p){
    for (auto j : g[p]){
        dep[j] = dep[p] + 1;
        dfs(j);
    }
}

void work(){
    int i, j, k, res = 0;
    set<pair<int, int> > S;
    for (i = 1; i <= n; ++i)
        if (fa[i] == 0){
            dep[i] = 1;
            dfs(i);
        }
    for (i = 1; i <= n; ++i)
        if (fa[i] == 0) S.insert({dep[i], i});

    for (i = 1; i <= m; ++i){
        set<pair<int, int> > T;
        for (j = 1; j <= K && S.size() > 0; ++j){
            auto p = prev(S.end());
            k = p->second;
            ++res;
            S.erase(p);
            for (auto h : g[k]) T.insert({dep[h], h});
        }

        for (auto t : T) S.insert(t);
    }

    printf("%d\n", res);
}

int main() {
    int t, T;
    // freopen("f.in", "r", stdin);
    scanf("%d", &T);
    for (t = 1; t <= T; ++t){
        init();
        work();
    }
    return 0;
}