#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    string s;
    cin >> s;
    if (s == "FIRST"){
        int n;
        cin >> n;
        vector<vector<int>> adj(n);
        for (int i = 0; i < n-1; i++){
            int a, b;
            cin >> a >> b;
            adj[--a].push_back(--b);
            adj[b].push_back(a);
        }
        vector<int> children(n, -1);
        queue<int> q;
        q.push(0);
        vector<int> ans(n, -1);
        while (!q.empty()){
            int cur = q.front();
            children[cur] = (int)adj[cur].size()-1;
            q.pop();
            for (int i : adj[cur]){
                if (children[i] != -1) continue;
                q.push(i);
                ans[i] = cur;
            }
        }
        ans[0] = 6e5+5;
        children[0]++;
        for (int i = 0; i < n-1; i++){
            if (children[i]%2 == 1){
                ans[i] += 3e5;
            }
            cout << ans[i] << " ";
        }
        if (children[n-1]%2 == 1) ans[n-1] += 3e5;
        cout << ans[n-1];
    }
    else{
        int n;
        cin >> n;
        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<vector<int>> adj(n);
        vector<bool> odd(n, false);
        int badi = 0;
        if (a[0] == -1){
            for (int i = 1; i < n; i++){
                if (a[i] > 3e5){
                    a[i] -= 3e5;
                }
                cout << a[i]+1 << " " << i+1 << endl;
            }
            return 0;
        }
        if (a[0] == 9e5+5) odd[0] = true;
        for (int i = 1; i < n; i++){
            if (a[i] == -1) {badi = i; continue;}
            if (a[i] > 3e5){
                a[i] -= 3e5;
                odd[i] = true;
            }
            cout << i+1 << " " << a[i]+1 << endl;
            adj[i].push_back(a[i]);
            adj[a[i]].push_back(i);
        }
        vector<int> children(n, 0);
        for (int i = 1; i < n; i++){
            if (i != badi) {
                children[a[i]]++;
            }
        }
        for (int i = 0; i < n; i++){
            if (i == badi) continue;
            if (children[i]%2 == 0 && odd[i] || children[i]%2 == 1 && !odd[i]){
                cout << i+1 << " " << badi+1 << endl;
            }
        }
    }
}