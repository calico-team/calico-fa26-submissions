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

const int maxn = 200005;
const int maxT = 3000000;

struct Tnode{
    int sons[2], ge;
};

struct Ttree{
    int top;
    Tnode a[maxT];
}tree, l, r;

vector<int> fg[maxn];
int n, H, lt, rt, tot, 
    nxt[maxn], a[maxn], f[maxn], res[maxn], pre[maxn];
bool done[maxn], inhuan[maxn];
vector<int> huan[maxn];

void init(){
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) fg[i].clear();
    for (i = 1; i <= n; ++i){
        scanf("%d", &nxt[i]);
        fg[nxt[i]].push_back(i);
    }
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
}

int add_node(Ttree &T){
    ++T.top;
    T.a[T.top].sons[0] = T.a[T.top].sons[1] = -1;
    T.a[T.top].ge = 0;
    return T.top;
}

void init_tree(Ttree &T){
    T.top = 0;
    add_node(T);
}

void ins_tree(int x, int dt, Ttree &T){
    int i, j, c, p = 1;
    for (i = 29; i >= 0; --i){
        if (x & (1<<i)) c = 1;
        else c = 0;
        T.a[p].ge += dt;
        if (T.a[p].sons[c] == -1)
            T.a[p].sons[c] = add_node(T);
        p = T.a[p].sons[c];
    }

    T.a[p].ge += dt;
}

void calc_huan(){
    int i, j, k;
    for (i = 1; i <= n; ++i) inhuan[i] = done[i]= false;
    H = 0;
    for (i = 1; i <= n; ++i){
        if (done[i]) continue;
        vector<int> xl;
        for (j = i; !done[j]; j = nxt[j]){
            xl.push_back(j);
            done[j] = true;
        }

        for (k = 0; k < xl.size(); ++k)
            if (xl[k] == j) break;
        if (k < xl.size()){
            huan[++H].clear();
            for (; k < xl.size(); ++k){
                huan[H].push_back(xl[k]);
                inhuan[xl[k]] = true;
            }
        }
    }
}

int find_max(int x, Ttree &T){
    int i, p = 1, c, res = 0;
    for (i = 29; i >= 0; --i){
        if (x & (1<<i)) c = 1;
        else c = 0;
        if (T.a[p].sons[1 - c] != -1 && T.a[T.a[p].sons[1 - c]].ge > 0){
            res ^= (1<<i);
            p = T.a[p].sons[1 - c];
        }
        else{
            if (T.a[p].sons[c] != -1 && T.a[T.a[p].sons[c]].ge > 0)
                p = T.a[p].sons[c];
            else 
                return -1;
        }
    }

    return res;
}

void dfs(int p, int now){
    now = (now ^ a[p]);
    f[p] = now;
    res[p] = max(f[p], find_max(f[p], tree));

    ins_tree(f[p], 1, tree);
    for (auto j : fg[p])
        if (!inhuan[j]) dfs(j, now);
    ins_tree(f[p], -1, tree);
}

void dfs2(int p){
    res[p] = max(res[p], f[p] ^ tot);
    if (lt != -1){
        res[p] = max(res[p], find_max(f[p] ^ lt, l));
        res[p] = max(res[p], find_max(f[p] ^ lt ^ tot, l));
    }

    if (rt != -1){
        res[p] = max(res[p], find_max(f[p] ^ rt, r));
        res[p] = max(res[p], find_max(f[p] ^ rt ^ tot, r));
    }

    for (auto j : fg[p])
        if (!inhuan[j]) dfs2(j);
}


void work(){
    int i, j, L, k, w;
    calc_huan();
    for (i = 1; i <= n; ++i) res[i] = 0;
    for (i = 1; i <= H; ++i){
        init_tree(tree);
        init_tree(l);
        init_tree(r);
        L = huan[i].size();
        for (j = 0; j < L; ++j){
            pre[j] = a[huan[i][j]];
            if (j - 1 >= 0) pre[j] ^= pre[j - 1];
            if (j > 0) ins_tree(pre[j], 1, r);
        }

        tot = pre[j - 1];
        for (j = 0; j < L; ++j) dfs(huan[i][j], 0);
        for (j = 0; j < L; ++j){
            lt = rt = -1;
            if (j + 1 < L) rt = pre[j];
            if (j - 1 >= 0) lt = (pre[L - 1] ^ pre[j]);
            dfs2(huan[i][j]);
            if (j + 1 < L) ins_tree(pre[j + 1], -1, r);
            ins_tree(pre[j], 1, l);
        }
    }

    for (i = 1; i <= n; ++i){
        printf("%d", res[i]);
        if (i == n) printf("\n");
        else printf(" ");
    }
}

int main() {
    int t, T;
    // freopen("j.in", "r", stdin);
    scanf("%d", &T);
    for (t = 1; t <= T; ++t){
        init();
        work();
    }
    return 0;
}