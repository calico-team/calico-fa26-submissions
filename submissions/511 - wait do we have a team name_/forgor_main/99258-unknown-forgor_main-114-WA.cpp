#include <bits/stdc++.h>
using namespace std;
/*
how to store a tree given n integers
you have 5x as many a as you have n
assume you start at root. read the a integers one at a time.
first integer: value of root
all other integers: value, then +n if D else +0
you know there is one root at level 0
at level x, you know how many nodes are in level x-1
read one by one, every time you get D move to the next node of the previous depth, if you run out of nodes move to the next depth

WRITE:
consider an A_i
let x=ai/n
let y=ai%n=what node this is
take the two bits of x
bit 1: "am i a D?"
bit 2: "was the element before me a D?"

READ:
you now want to deduce something about the -1
you know its value because that is the missing value
you know if it is D by the next element
*/

/**
 * Output a list N integers A_1 .. A_N
 *
 * N: the number of vertices
 * E: the N - 1 edges of the tree as (u, v) pairs
 */
vector<int> solve_phase1(int n, vector<pair<int, int>>& E) {
    vector<vector<int>> a(n, vector<int>{});
    for (auto [xx, yy]:E){
        xx--; yy--;
        a[xx].push_back(yy);
        a[yy].push_back(xx);
    }
    queue<int> q; q.push(0);
    vector<array<int, 3>> ret{{0,0,0}};
    vector<bool> vis(n,false);
    while (q.size()){
        auto cur=q.front(); q.pop();
        for (auto xx:a[cur]){
            if (vis[xx]) continue;
            ret.push_back({xx, 0, 0});
            vis[xx]=true;
            q.push(xx);
        }
        ret.back()[1]++;
    }
    for (int i=0;i<n-1;i++) if (ret[i][1]) ret[i+1][2]++;
    vector<int> ans(n,0);
    for (int i=0;i<n;i++) {
        ans[i]=ret[i][0]+n*(ret[i][1]+ret[i][2]*2);
    }
    return ans;
}

/**
 * The N - 1 edges of the original tree as (u, v) pairs
 *
 * N: the number of vertices
 * A: the N integers A_1 .. A_N with one value replaced with -1
 */
vector<pair<int, int>> solve_phase2(int n, vector<int>& a) {
    vector<bool> vis(n, true);
    vector<int> val(n,0);
    vector<int> d(n,0);
    int n1n=0;
    for (int i=0;i<n;i++){
        if (a[i]==-1) {
            val[i]=-1; 
            n1n=i;
            continue;
        }
        int x=a[i]/n;
        int y=a[i]%n;
        int b1=x%2;
        int b2=x/2;
        d[i]=b1;
        if (i) d[i-1]=b2;
        vis[y]=false;
        val[i]=y;
    }
    // for (int i=0;i<n;i++){
    //     cout<<"d: "<<d[i]<<'\n';
    // }
    for (int i=0;i<n;i++) if (vis[i]) val[n1n]=i;
    vector<pair<int, int>> ret{};
    int curptr=0;
    vector<int> curlayer{0};
    vector<int> nextlayer{};
    for (int i=1;i<n;i++){
        ret.push_back({curlayer[curptr]+1, val[i]+1});
        nextlayer.push_back(val[i]);
        if (d[i]) {
            curptr++;
            if (curptr>=curlayer.size()){
                swap(curlayer, nextlayer);
                nextlayer.clear();
                curptr=0;
            }
        }
    }
    return ret;
}

int main() {
    string phase;
    cin >> phase;
    int N;
    cin >> N;

    if (phase == "FIRST") {
        vector<pair<int, int>> E(N - 1);
        for (int i = 0; i < N - 1; i++) {
            cin >> E[i].first >> E[i].second;
        }
        vector<int> A = solve_phase1(N, E);
        for (int i = 0; i < N; i++) {
            if (i > 0) cout << ' ';
            cout << A[i];
        }
        cout << '\n';
    } else {
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        vector<pair<int, int>> edges = solve_phase2(N, A);
        for (auto& e : edges) {
            cout << e.first << ' ' << e.second << '\n';
        }
    }
}
