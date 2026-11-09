#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int next() {
    int temp; cin >> temp; return temp;
}

vector<vector<int>> ffa {{0,1}, {0,-1}, {1,0}, {-1,0}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int ttttt = next();
    while (ttttt--) {
        int n = next(), m = next(), q = next();
        vector<vector<int>> a {};
        for (int i=0; i<n; i++) {
            string s; cin >> s;
            vector<int> temp {};
            for (char c : s) {
                if (c == 'R')
                    temp.push_back(1);
                else if (c == 'B')
                    temp.push_back(-1);
                else
                    temp.push_back(2);
            }
            a.push_back(temp);
        }
        vector<vector<int>> aa {};
        for (int i=0; i<n; i++) {
            vector<int> temp(m,0);
            aa.push_back(temp);
        }
        // flood
        int counter = 0, floodc = 0;
        while (counter < n * m) {
            int c1 = counter / m, c2 = counter % m;
            counter++; 
            if (aa[c1][c2] != 0) { continue; }
            floodc++;
            queue<vector<int>> dq {};
            dq.push({c1,c2});
            while (!dq.empty()) {
                auto temp = dq.front(); dq.pop();
                aa[temp[0]][temp[1]] = floodc;
                for (auto i : ffa) {
                    int cc1 = temp[0] + i[0], cc2 = temp[1] + i[1];
                    if (cc1 >= 0 && cc2 >= 0 && cc1 < n && cc2 < m) {
                        if (a[cc1][cc2] != -a[temp[0]][temp[1]] && aa[cc1][cc2] == 0) {
                            dq.push({cc1, cc2});
                        }
                    }
                }
            }
        }
        while (q--) {
            int c1 = next(), c2 = next(), c3 = next(), c4 = next();
            if (aa[c1][c2] == aa[c3][c4]) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}