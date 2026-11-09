#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int M = 1000000;
int deg[200005];
vector<int> adj[200005];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string ph;
    int n;
    if (!(cin >>ph>> n)) return 0;

    if (ph == "FIRST") {
        vector<pair<int,int>> e(n - 1);
        for (int i = 0; i < n -1; ++i) {
            cin >> e[i].first >> e[i].second;
            adj[e[i].first].push_back(e[i].second);
            adj[e[i].second].push_back(e[i].first);
            deg[e[i].first]++;
            deg[e[i].second]++;
        }

        priority_queue<int,vector<int>, greater<int>> pq;
        for (int i =1; i <=n; ++i) {
            if (deg[i] ==1) pq.push(i);
        }

        vector<int> a(n);
        int sm =0;
        
        // n kecil pake pq aman O(N log N)
        for (int i = 0;i < n - 2; ++i) {
            int x =pq.top(); 
            pq.pop();
            int y = -1;
            for (int z :adj[x]) {
                if (deg[z]) { 
                    y =z; 
                    break; 
                }
            }
            a[i] =y;
            sm =(sm + y) % M;
            deg[x]--;
            if (--deg[y] == 1) pq.push(y);
        }

        a[n - 2] = a[n - 1] = sm;

        for (int i =0; i < n; ++i) {
            cout <<a[i] << (i + 1 == n ? '\n' : ' ');
        }
        return 0;
    }

    vector<int> a(n);
    int miss = -1;
    for (int i = 0; i <n; ++i) {
        cin >>a[i];
        if (a[i]== -1) miss = i;
    }

    int chk = (miss ==n - 2 ? a[n - 1] : a[n - 2]);

    if (miss <n - 2) {
        int sm = 0;
        for (int i = 0; i < n - 2; ++i) {
            if (i == miss) continue;
            sm= (sm + a[i]) % M;
        }
        a[miss] =(chk - sm + M) % M;
    }

    fill(deg + 1, deg + n + 1, 1);
    for (int i =0; i < n - 2; ++i) {
        deg[a[i]]++;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] == 1) pq.push(i);
    }

  
    for (int i = 0; i < n -2; ++i) {
        int x = pq.top(); 
        pq.pop();
        int y =a[i];
        cout << x<< ' ' << y << '\n';
        deg[x]--;
        if (--deg[y] ==1) pq.push(y);
    }

    int u = pq.top(); 
    pq.pop();
    int v = pq.top();
    cout << u<< ' ' << v << '\n';

    return 0;
}