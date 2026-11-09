#include <bits/stdc++.h>
using namespace std;
typedef long long li;
#define fastio ios_base::sync_with_stdio(false);cin.tie(0)
void setIO(string s) {freopen((s + ".in").c_str(), "r", stdin);freopen((s + ".out").c_str(), "w", stdout);}
li mod(li a,li b){li c=a%b;return c<0?c+b:c;}

/**
 * Return an array of Q strings, the i-th of which is "YES"
 * if Big Ben can travel from start[i] to end[i], and "NO"
 * otherwise.
 *
 * N: the number of rows in the grid
 * M: the number of columns in the grid
 * Q: the number of queries
 * G: the grid, where each tile is 'R', 'B', or '.'
 * start: the (row, column) of the starting tile of each query
 * end: the (row, column) of the ending tile of each query
 */
int xN, yN;
int* gi;
int* col;
vector<set<int>> c;
void flood1(int ax, int ay, int g) {
    stack<pair<int, int>> todo;
    todo.push({ax, ay});
    int me = col[ay*xN+ax];
    while (!todo.empty()) {
        int x = todo.top().first, y = todo.top().second;
        todo.pop();
        if (x < 0 || y < 0 || x >= xN || y >= yN) continue;
        if (col[y*xN+x] != me) {
            int other = gi[y*xN+x];
            if (other == 0) continue;
            // check colors (if neither are normal, and they aren't same (r&b or b&r)
            if (col[y*xN+x] != 0 && me != 0 && col[y*xN+x] != me) continue;
            c[g].insert(other);
            c[other].insert(g);
            continue;
        }
        if (gi[y*xN+x]) continue;
        gi[y*xN+x] = g;
        todo.push({x+1, y});
        todo.push({x-1, y});
        todo.push({x, y+1});
        todo.push({x, y-1});
    }
}

int* v;
int e; int q;
bool dfs(int s) {
    if (v[s] == q) return false;
    if (s == e) return true;
    v[s] = q;
    //process
    for (auto u : c[s]) {
        if (dfs(u)) return true;
    }
    return false;
}


vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    // 0 = normal, 1 = blue, 2 = red
    xN = M; yN = N;
    col = new int[xN*yN];
    for (int y = 0; y < yN; y++) {
        for (int x = 0; x < xN; x++) {
            if (G[y][x] == 'R') col[y*xN+x] = 2;
            else if (G[y][x] == 'B') col[y*xN+x] = 1;
            else col[y*xN+x] = 0;
        }
    }
    gi = new int[xN*yN];
    for (int i = 0; i < xN*yN; i++) gi[i] = 0;
    c.clear(); c.push_back({});
    int g = 1;
    for (int x = 0; x < xN; x++) {
        for (int y = 0; y < yN; y++) {
            if (gi[y*xN+x]) continue;
            c.push_back({});
            flood1(x, y, g);
            g++;
        }
    }
    delete col;

    vector<string> ans{};
    v = new int[g];
    for (int i = 0; i < g; i++) {v[i] = -1;}
    for (q = 0; q < Q; q++) {
        e = gi[end[q].first * xN + end[q].second];
        if (dfs(gi[start[q].first * xN + start[q].second])) {
            ans.push_back("YES");
        } else {
            ans.push_back("NO");
        }
    }
    delete gi;
    return ans;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> G(N);
        for (int j = 0; j < N; j++) {
            cin >> G[j];
        }
        vector<pair<int, int>> start, end;
        for (int j = 0; j < Q; j++) {
            int start_row, start_col, end_row, end_col;
            cin >> start_row >> start_col >> end_row >> end_col;
            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
        }

        for (string s : solve(N, M, Q, G, start, end)) {
            cout << s << '\n';
        }
    }
}