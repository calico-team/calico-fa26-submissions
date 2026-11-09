//
// Created by User on 11/8/2026.
//

#include "bits/stdc++.h"
using namespace std;

static int par[200'005];
static vector<int> adj[200'005];
static bool visited[200'005];

static int gt[200'005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin>>s;
    if (s=="FIRST") {
        int sz;
        cin>>sz;
        for (int i=0; i<sz-1; i++) {
            int x,y;
            cin>>x>>y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        //start at 1
        queue<int> q;
        visited[1]=true;
        par[1]=0;//set par[1] to the sum of all meaning if any is -1 then we just replace
        q.push(1);
        while (!q.empty()) {
            int curr=q.front();
            q.pop();
            for (int next:adj[curr]) {
                if (visited[next])continue;
                visited[next]=true;
                par[next]=curr;
                q.push(next);
            }
        }
        int sum=0;
        for (int i=2; i<=sz; i++) {
            sum+=par[i];
        }
        par[1]=sum;
        for (int i=1; i<=sz; i++) {
            cout<<par[i]<<(i==sz?"\n":" ");
        }
    }else {
        int sz;
        cin>>sz;
        int idx=0;
        int sum=0;
        for (int i=1; i<=sz; i++) {
            cin>>gt[i];
            if (gt[i]==-1) {
                idx=i;
            }else if (i>1){
                sum+=gt[i];
            }
        }
        if (idx!=1) {
            gt[idx]=gt[1]-sum;
        }
        for (int i=2; i<=sz; i++) {
            cout<<i<<" "<<gt[i]<<"\n";
        }
    }


}