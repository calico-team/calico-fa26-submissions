#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string phase;
    cin >>phase;
    int n;
    cin >>n;
    if(phase== "FIRST") {
        vector<vector<int>>adj(n + 1);
        vector<int> deg(n +1, 0);
        for(int i =0; i < n - 1; i++) {
            int u, v;
            cin >> u>> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++;
            deg[v]++;
        }
        priority_queue<int, vector<int>, greater<int>> leaves;
        for (int i = 1; i <=n;i++) {
            if (deg[i]== 1) {
                leaves.push(i);
            }
        }
        vector<int> prufer;
        prufer.reserve(n- 2);
        for(int i = 0; i < n -2; i++) {
            int leaf = leaves.top();
            leaves.pop();
            int neighbor= -1;
            for (int v : adj[leaf]){
                if (deg[v] >0) {
                    neighbor = v;
                    break;
                }
            }
            prufer.push_back(neighbor);
            deg[leaf]= 0;
            deg[neighbor]--;
            if (deg[neighbor]== 1) {
                leaves.push(neighbor);
            }
        }
        vector<int>a(n, 0);
        int check = 0;
        for(int i= 0; i < n - 2; i++) {
            a[i] = prufer[i];
            check ^=prufer[i];
        }
        a[n -2] = check;
        a[n - 1]= 0;

        for(int i =0; i < n; i++) {
            if (i) cout <<' ';
            cout << a[i];
        }
        cout<< '\n';
    } else{
        vector<int> a(n);
        int missing =-1;
        for(int i= 0; i < n; i++) {
            cin >> a[i];
            if (a[i]== -1) {
                missing =i;
            }
        }
        vector<int>prufer(n - 2);
        for (int i =0; i < n - 2; i++){
            prufer[i] = a[i];
        }
        if (missing >=0 && missing < n - 2) {
            int x =a[n- 2];
            for (int i =0; i < n - 2; i++) {
                if (i != missing) {
                    x^= a[i];
                }
            }
            prufer[missing]= x;
        }
        vector<int> deg(n + 1,1);

        for (int x : prufer) {
            deg[x]++;
        }
        priority_queue<int, vector<int>, greater<int>> leaves;
        for(int i = 1; i<= n; i++) {
            if (deg[i] ==1) {
                leaves.push(i);
            }
        }
        for (int x : prufer) {
            int leaf= leaves.top();
            leaves.pop();
            cout <<leaf << ' ' << x << '\n';
            deg[leaf]--;
            deg[x]--;
            if(deg[x] == 1) {
                leaves.push(x);
            }
        }
        int u =leaves.top();
        leaves.pop();

        int v =leaves.top();

        cout <<u<< ' ' << v << '\n';
    }
    return 0;
}