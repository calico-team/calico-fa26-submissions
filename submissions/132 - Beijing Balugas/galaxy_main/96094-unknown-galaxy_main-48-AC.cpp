#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second  

vector<int> parents;
vector<string> graph;

bool can(int i, int j, int m) {

    if(graph[i][j] == '.') {

        return true;

    }

    if(m == 0) {

        if(graph[i][j] == 'B') {

            return true;

        }
        return false;

    }

    if(graph[i][j] == 'R') {

        return true;

    }
    return false;

}

int root(int cur) {

    while(parents[cur] != cur) {

        parents[cur] = parents[parents[cur]];
        cur = parents[cur];

    }

    return cur;

}

void comb(int a, int b) {

    int rA = root(a);
    int rB = root(b);

    if(rA != rB) {

        parents[rB] = rA;

    }

}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {

        int n, m, q;
        cin >> n >> m >> q;

        int tot = n * m;
        parents.clear();
        parents.resize(2 * tot);

        for(int i = 0; i < 2 * tot; i++) {

            parents[i] = i;

        }

        graph.clear();
        graph.resize(n);
        for(int i = 0; i < n; i++) {

            cin >> graph[i];

        }

        for(int i = 0; i < n; i++) {

            for(int j = 0; j < m; j++) {

                int cur = i * m + j;
                if(graph[i][j] == '.') {

                    comb(cur, cur + tot);

                }

                for(int mode = 0; mode < 2; mode++) {

                    if(!can(i, j, mode)) {

                        continue;

                    }

                    int curS = mode * tot + cur;

                    //down
                    if(i + 1 < n && can(i + 1, j, mode)) {

                        comb(curS, curS + m);

                    }

                    if(j + 1 < m && can(i, j + 1, mode)) {

                        comb(curS, curS + 1);

                    }

                }

            }

        }

        while(q--) {

            int si, sj, ei, ej;
            //rowstart colstart rowend colend
            cin >> si >> sj >> ei >> ej;

            bool works = false;
            int start = root(si * m + sj);
            int end = ei * m + ej;

            for(int mode = 0; mode < 2; mode++) {

                if (can(ei, ej, mode) && root(mode * tot + end) == start) {

                    works = true;
                    break;

                }

            }

            if(works) {

                cout << "YES" << endl;

            } else {

                cout << "NO" << endl;

            }

        }
        
    }

}