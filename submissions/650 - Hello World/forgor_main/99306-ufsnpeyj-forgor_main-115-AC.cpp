#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int main() {
    string phase;
    int n;
    cin >> phase >> n;
    vector<int> parent(n + 1, 0);
    int xr = 0;
     

    if (phase=="FIRST") {
        vector<vector<int>> adj(n + 1);

        for (int i =1; i < n; i++) {
            int u, v;
            cin >>u>>v;
             adj[u].push_back(v);
             
            adj[v].push_back(u);
        }




        queue<int> q;
        q.push(1);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (v == parent[u]) continue;

                parent[v] = u;
                xr ^= u;
                q.push(v);
            } }
        cout << xr;
        for (int i = 2; i <= n; i++) {
            cout << ' ' << parent[i];

        }
        cout <<'\n';
    } else {
          int missing = 0;

        for (int i = 1; i <=n; i++) {
           cin >>parent[i];

            if (parent[i] == -1) missing = i;
             else xr ^= parent[i];
        }
        parent[missing] = xr;

        for (int i=2; i<= n; i++) {

             cout << parent[i] <<' ' << i<< '\n';
        }
    }
    return 0;}