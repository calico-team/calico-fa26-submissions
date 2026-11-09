#include <bits/stdc++.h>
#include <iostream>

using namespace std;

const int MAXN = 1e4+5;

int n, h[MAXN], in[MAXN];

vector<int> adj[MAXN];


/*
given a directed forest
at any time we can take nodes from a certain level given that we have unlocked it
We can count available nodes
When we are allowed to activate new nodes, what is optimal to unlock 

unlock highest candidates first
*/


void dfs(int node){
    for(int child : adj[node]){
        dfs(child);
        h[node] = max(h[node], h[child]+1);
    }
}

int main(){
    int tt; cin >> tt;

    while(tt--){
        int m,k; cin >> n >> m >> k;

        for(int i = 1; i <= n; i++){
            in[i] = 0;
            h[i] = 0;
            adj[i].clear();
        }

        for(int i = 1; i <= n; i++){
            int x; cin >> x;

            if(!x) continue;
            in[i]++;
            adj[x].push_back(i);
        }

        for(int i = 1; i <= n; i++){
            if(!in[i]) dfs(i);
        }


        set<pair<int,int>> s;


        for(int i = 1; i <= n; i++){
            if(!in[i]) s.insert({-h[i], i});
        }

        int ans = 0;

        for(int i = 1; i <= m; i++){

            set<pair<int,int>> nxt;
            for(int j = 0; j < k; j++){
                if(!s.size()) break;

                auto [d, x] = *s.begin();   
                s.erase(s.begin());
                ans++;
                for(int child : adj[x]) nxt.insert({-h[child], child});
            }

            if(nxt.size() > s.size()) nxt.swap(s);
            for(pair<int,int> i : nxt) s.insert(i);
        }

        cout << ans << "\n";

    }
}