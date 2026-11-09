#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second  

vector<vector<int>> graph;
vector<int> parents;

void dfs(int cur, int prev) {

    parents[cur] = prev;
    for(int i : graph[cur]) {

        if(i == prev) {

            continue;

        }

        dfs(i, cur);

    }

}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string phase;
    cin >> phase;

    if(phase == "FIRST") {

        int n;
        cin >> n;

        graph.resize(n);
        parents.resize(n);

        for(int i = 0; i < n - 1; i++) {

            int u, v;
            cin >> u >> v;

            u--, v--;
            graph[u].push_back(v);
            graph[v].push_back(u);

        }
        dfs(0, -1);

        int xSum = 0;

        for(int i = 1; i < parents.size(); i++) {

            xSum = xSum ^ parents[i];

        }
        parents[0] = xSum;

        for(int i = 0; i < n; i++) {

            cout << parents[i] << " ";

        }

    } else {

        int n;
        cin >> n;
        
        vector<int> a(n);
        int del = 0;
        for(int i = 0; i < n; i++) {

            cin >> a[i];
            if(a[i] == -1) {

                del = i;

            }

        }

        if(del != 0) {

            int xSum = 0;
            for(int i = 1; i < n; i++) {

                if(i == del) {

                    continue;

                }

                xSum = xSum ^ a[i];

            }

            a[del] = a[0] ^ xSum;

        }

        for(int i = 1; i < n; i++) {

            cout << i + 1 << " " << a[i] + 1 << "\n";

        }

    }

}