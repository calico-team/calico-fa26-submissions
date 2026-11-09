// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

struct state {
    size_t x;
    size_t y;
    set<pair<int, int>> seen;
    bool red;

    state(size_t x, size_t y, set<pair<int,int>> seen, bool red) : x(x), y(y), seen(seen), red(red) {}
};

bool move(vector<vector<int>>& G, int dir, state& s) {
    state s2(s);
    if (dir == 0) s2.x++;
    if (dir == 1) s2.y++;
    if (dir == 2) s2.x--;
    if (dir == 3) s2.y--;
    if (s.seen.count(make_pair(s2.x, s2.y))) return false;
    s2.seen.insert(make_pair(s2.x, s2.y));
    if (s2.x >= G.size() || s2.y >= G[0].size()) return false;

    if (G[s2.x][s2.y] == 2 - s.red) {s = s2; return true;}
    if (G[s2.x][s2.y] == 1 + s.red){
        if (G[s.x][s.y] != 0) return false;
        s2.red = !s2.red;
    }
    s = s2;
    return true;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        size_t N, M, Q;
        cin >> N >> M >> Q;
        vector<vector<int>> G(N); //0 = norm, 1 = red, 2 = blue
        for (size_t i = 0; i < N; i++) {
            char tmp = ' ';
            for (size_t j = 0; j < M; j++) {
                cin >> tmp;
                if (tmp == '.') G[i].push_back(0);
                if (tmp == 'R') G[i].push_back(1);
                if (tmp == 'B') G[i].push_back(2);
            }
        }
        for (size_t _q = 0; _q < Q; _q++) {
            size_t sx, sy, dx, dy;
            cin >> sx >> sy >> dx >> dy;
            state initial(sx, sy, {}, false);
            queue<state> q;
            q.push(initial);
            bool flag = false;
            while (!q.empty()) {
                state cur = q.front();
                // cout << cur.x << " " << cur.y << endl;
                if (cur.x == dx && cur.y == dy) {
                    flag = true;
                    break;
                }
                q.pop();
                state tmp = cur;
                if (move(G, 0, tmp)) q.push(tmp);
                tmp = cur;
                if (move(G, 1, tmp)) q.push(tmp);
                tmp = cur;
                if (move(G, 2, tmp)) q.push(tmp);
                tmp = cur;
                if (move(G, 3, tmp)) q.push(tmp);
            }
            
            // for (size_t i = 0; i < N; i++) {
            //     for (size_t j = 0; j < M; j++) cout << G[i][j]; cout << endl;
            // }

            cout << ((flag) ? "YES" : "NO") << endl;
        }
    }
}
