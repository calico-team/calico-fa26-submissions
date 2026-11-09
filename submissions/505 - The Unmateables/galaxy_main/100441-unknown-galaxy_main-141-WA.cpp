// BY THE NAME OF ALMIGHTY ALLAH
// حَسْبُنَا اللَّهُ وَنِعْمَ الْوَكِيلُ

#include <bits/stdc++.h>

#define ll long long int
#define ld long double
#define ull unsigned long long int
#define vi vector<int>
#define vll vector<ll>
#define all(x) (x).begin(), (x).end()

using namespace std;
using u64 = unsigned long long;

const ll INF = 1e18;
const ll NEGINF = -INF;
const ll MOD = 1e9 + 7;

void solve()
{
    ll n,m,q;
    cin >> n >> m >> q;
    vector<string> grid(n);
    for (int i = 0; i < n; i++){
        string s;
        cin >> s;
        grid[i] = s;
    }

    vector<vector<vector<pair<int, int>>>> adj(n, vector<vector<pair<int, int>>>(m));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (grid[i][j] == '.'){
                if (i < n-1) {adj[i][j].push_back({i+1,j});}
                if (i > 0) {adj[i][j].push_back({i-1,j});}
                if (j < m-1) {adj[i][j].push_back({i,j+1});}
                if (j > 0) {adj[i][j].push_back({i,j-1});}
            }
            if (grid[i][j] == 'R'){
                if (i < n-1 && grid[i+1][j] != 'B') {adj[i][j].push_back({i+1,j});}
                if (i > 0 && grid[i-1][j] != 'B') {adj[i][j].push_back({i-1,j});}
                if (j < m-1 && grid[i][j+1] != 'B') {adj[i][j].push_back({i,j+1});}
                if (j > 0 && grid[i][j-1] != 'B') {adj[i][j].push_back({i,j-1});}
            }
            if (grid[i][j] == 'B'){
                if (i < n-1 && grid[i+1][j] != 'R') {adj[i][j].push_back({i+1,j});}
                if (i > 0 && grid[i-1][j] != 'R') {adj[i][j].push_back({i-1,j});}
                if (j < m-1 && grid[i][j+1] != 'R') {adj[i][j].push_back({i,j+1});}
                if (j > 0 && grid[i][j-1] != 'R') {adj[i][j].push_back({i,j-1});}
            }
        }
    }

    vector<vector<bool>> used(n, vector<bool>(m));

    while (q--){
        ll startR, startC, endR, endC;
        cin >> startR >> startC >>  endR >> endC;

        used[startR][startC] = true;
        queue<pair<ll,ll>> q;
        q.push({startR, startC});

        while (!q.empty()){
            ll curRow = q.front().first;
            ll curCol = q.front().second;
            q.pop();

            for (pair<int,int> v : adj[curRow][curCol]){
                if (!used[v.first][v.second]) {
                    used[v.first][v.second] = true;
                    q.push({v.first, v.second});
                }
            }
        }
        if (used[endR][endC]) {
            cout << "YES" << '\n';
        }
        else cout << "NO" << '\n';
    }

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;

    //------------------------>
    cin >> t;
    //------------------------>

    for (int i = 1; i <= t; i++)
    {
        // cout << "Case " << i << ": ";
        solve();
    }
}