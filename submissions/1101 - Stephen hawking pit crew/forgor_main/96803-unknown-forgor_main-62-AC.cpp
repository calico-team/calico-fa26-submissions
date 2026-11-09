#include <bits/stdc++.h>
#define f first
#define s second
using ll=long long;
using ull=unsigned long long;
using namespace std;
int main() {
    string s; cin >> s;
    if(s=="FIRST") {
        int n; cin >> n;
        vector<vector<int>> adj(n+1);
        for(int i=0; i<n-1; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> p(n+1, 0);
        stack<int> st;
        st.push(1);
        while(!st.empty()) {
            int u=st.top(); st.pop();
            for(auto x:adj[u]) {
                if(x!=p[u]) {
                    p[x]=u;
                    st.push(x);
                }
            }
        }
        int tot=0;
        for(int i=2; i<=n; i++) tot=(tot+p[i])%1000000;
        cout << tot << " ";
        for(int i=2; i<=n; i++) {
            cout << p[i] << " ";
        }
        cout << "\n";
    } else {
        int n; cin >> n;
        vector<int> v(n);
        int k;
        for(int i=0; i<n; i++) {
            cin >> v[i];
            if(v[i]==-1) k=i;
        }
        if(k!=0) {
            int sum=0;
            for(int i=1; i<n; i++) {
                if(i==k) continue;
                sum=(sum+v[i])%1000000;
            }
            v[k]=(v[0]-sum+1000000)%1000000;
        }
        for(int i=1; i<n; i++) {
            cout << i+1 << " " << v[i] << "\n";
        }
    }
}