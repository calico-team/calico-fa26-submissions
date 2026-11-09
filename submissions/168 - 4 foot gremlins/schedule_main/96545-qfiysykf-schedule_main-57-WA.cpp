#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

void printQ(queue<int> q){
    cout << "q:";
    while(q.size()>0){
        cout << " " << q.front(); q.pop();
    }
    cout << "\n";
}

void solve(){
    int n,m,k; cin >> n >> m >> k;
    vector<vector<int>> graph(n+1);
    vector<int> indeg(n+1,0);

    int pi;
    for(int i = 1; i <= n; i++){
        cin >> pi;
        if(pi!=0){
            graph[pi].push_back(i);
            indeg[i]++;
        }
    }

    // for(int i = 1; i <= n; i++){
    //     cout << i << ":";
    //     for(int a : graph[i]) cout << " " << a;
    //     cout << "\n";
    // }
    int ans = 0;

    queue<int> q;
    for(int i = 1; i <= n; i++){
        if(indeg[i]==0) q.push(i);
    }
    // printQ(q);
    for(int iii = 0; iii < m; iii++){
        // cout << "iii: " << iii << "\n";
        // cout << "ii running " << min(static_cast<int>(q.size()),k) << " times\n";
        int sz = q.size();
        for(int ii = 0; ii < min(static_cast<int>(sz),k); ii++){
            int i = q.front(); q.pop();
            ans++;
            for(int j : graph[i]){
                indeg[j]--;
                if(indeg[j]==0) q.push(j);
            }
            // cout << "at end of " << ii << ", ";
            // printQ(q);
        }
    }
    cout << ans << endl;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while(t--) solve();

    return 0;
}
