#include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>
#include <cstring>
 
typedef long long ll;
using namespace std;
using namespace __gnu_pbds;
 
/*template<class T> 
using Tree=tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;*/

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    string S; cin >> S;
    if (S=="FIRST"){
        int n; cin >> n;
        vector<int> adj[n+1];
        int par[n+1]; memset(par,0,sizeof(par));
        for (int i=1; i<n; i++){
            int t1,t2; cin >> t1 >> t2;
            adj[t1].push_back(t2);
            adj[t2].push_back(t1);
            par[t1]++;
            par[t2]++;
        }
        priority_queue<int,vector<int>,greater<int>> pq;
        for (int i=1; i<=n; i++){
            if (par[i]==1) pq.push(i);
        }
        vector<int> out;
        ll sum=0;
        while (!pq.empty()){
            int x=pq.top(); pq.pop();
            for (int i: adj[x]){
                par[i]--;
                par[x]--;
                if (par[i]>=0){
                    out.push_back(i);
                    sum+=i;
                }
                if (par[i]==1){
                    pq.push(i);
                }
            }
        }
        sum%=n;
        out.push_back(n-sum);
        cout << out[0];
        for (int i=1; i<n; i++) cout << " " << out[i];
        cout << "\n";
    }
    else{
        int n; cin >> n;
        vector<int> A(n+1);
        int id=0;
        ll sum=0;
        for (int i=1; i<=n; i++){
            cin >> A[i];
            if (A[i]==-1) id=i;
            else sum+=A[i];
        }
        A[id]=(-sum)%n+n;
        A.pop_back();
        int deg[n+1]; fill(deg+1,deg+n+1,1);
        for (int i=1; i<n-1; i++){
            deg[A[i]]++;
        }
        priority_queue<int,vector<int>,greater<int>> pq;
        for (int i=1; i<=n; i++){
            if (deg[i]==1) pq.push(i);
        }
        vector<pair<int,int>> out;
        for (int i=1; i<n-1; i++){
            int j=pq.top(); pq.pop();
            out.push_back({A[i],j});
            deg[A[i]]--; deg[j]--;
            if (deg[A[i]]==1) pq.push(A[i]);
        }
        int t1=-1; int t2=-1;
        for (int i=1; i<=n; i++){
            if (deg[i]==1){
                if (t1==-1) t1=i;
                else t2=i;
            }
        }
        for (auto [a,b]: out) cout << a << " " << b << "\n";
        cout << t1 << " " << t2 << "\n";
    }
}