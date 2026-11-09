#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define foreach(v, a) for(auto &v : a)

struct customhash{
    size_t operator()(ll x) const {
        static const ll rand = chrono::steady_clock::now().time_since_epoch().count();
        return x^rand;
    }
};

ll modpow(ll b, ll x, ll m){
    ll cur = 1;
    ll exp = b;
    int i = 0;
    while((1 << i) <= x){
        if((x & (1 << i)) >> i){
            cur = (cur*exp)%m;
        }
        exp = (exp*exp)%m;
        i++;
    }
    return cur;
}

vector<pair<int, int>> dirs{{-1, 0},{1,0},{0,1},{0,-1}};
void paint(int i, int j, int n, int m, int cur, char type, vector<string> &grid, vector<unordered_set<int>> &graph, vector<vector<int>> &col){
    if(col[i][j] != 0 && grid[i][j] != type){
        if(type != '.' && ((type == 'R' && grid[i][j] == 'B') || (type == 'B' && grid[i][j] == 'R'))){
            return;
        }
        graph[cur].insert(col[i][j]);
        graph[col[i][j]].insert(cur);
    }
    if(col[i][j] != 0 || grid[i][j] != type){
        return;
    }
    col[i][j] = cur;

    for(auto dir:dirs){
        int x = i+dir.first, y = j+dir.second;
        if(x < 0 || x >= n || y < 0 || y >= m)
            continue;
        paint(x, y, n, m, cur, type, grid, graph, col);
    }
}



void solve(){
    int n, m, q;
    cin >> n >> m >> q;
    vector<string> grid(n);
    foreach(row, grid){
        cin >> row;
    }

    vector<unordered_set<int>> graph(n*m+1);
    vector<vector<int>> col(n, vector<int>(m, 0));
    int color = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(col[i][j] == 0){
                paint(i, j, n, m, color, grid[i][j], grid, graph, col);
                color++;
            }
        }
    }


    vector<bool> valid(n*m+1, false);
    queue<int> stack;
    stack.push(col[n-1][m-1]);
    while(stack.size() > 0){
        int cur = stack.back();
        valid[cur] = true;

        for(auto child : graph[cur]){
            if(valid[child])
                continue;
            stack.push(child);
        }
        stack.pop();
    }

    for(int i = 0; i < q; i++){
        int rs, cs, re, ce;
        cin >> rs >> cs >> re >> ce;
        if(valid[col[rs][cs]]){
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }
}   

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for(int i = 0; i < T; i++) 
        solve();
    return 0;
}