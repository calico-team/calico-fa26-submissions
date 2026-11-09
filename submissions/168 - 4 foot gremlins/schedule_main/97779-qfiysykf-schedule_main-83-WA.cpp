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

void getNodesBelow(int i, int n, vector<int> &nodesBelow, vector<vector<int>> &graph){
    nodesBelow[i] = 0;
    for(int j : graph[i]){
        if(nodesBelow[j]==-1) getNodesBelow(j,n,nodesBelow,graph);
        nodesBelow[i]+=1+nodesBelow[j];
    }
}

void solve(){
    int n,m,k; cin >> n >> m >> k;
    vector<vector<int>> graph(n+1);
    vector<int> nodesBelow(n+1,-1);
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
    //     if(nodesBelow[i]==-1) getNodesBelow(i,n,nodesBelow,graph);
    //     cout << nodesBelow[i] << " ";
    // }
    // cout << "\n";


    // for(int i = 1; i <= n; i++){
    //     cout << i << ":";
    //     for(int a : graph[i]) cout << " " << a;
    //     cout << "\n";
    // }
    int ans = 0;

    priority_queue<pair<int,int>> q;
    for(int i = 1; i <= n; i++){
        if(indeg[i]==0) q.push({nodesBelow[i],i});
    }

    // printQ(q);
    for(int iii = 0; iii < m; iii++){
        // cout << "iii: " << iii << "\n";
        // cout << "ii running " << min(static_cast<int>(q.size()),k) << " times\n";
        int sz = min(static_cast<int>(q.size()),k);
        vector<pair<int,int>> temp; temp.reserve(n+2);
        for(int ii = 0; ii < sz; ii++){
            pair<int,int> p = q.top(); q.pop();
            ans++;
            for(int j : graph[p.second]){
                indeg[j]--;
                if(indeg[j]==0) temp.push_back({nodesBelow[j],j});
            }
            // cout << "at end of " << ii << ", ";
            // printQ(q);
        }
        for(pair<int,int> a : temp) q.push(a);
    }
    cout << ans << endl;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while(t--) solve();

    return 0;
}
