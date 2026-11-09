#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;
void solve() {
    int n, m, k;
    cin>>n>>m>>k;
    vector<int> p(n+1);
    vector<vector<int>>ch(n+1);
    for(int i=1; i<=n; i++){
        cin>>p[i];
        ch[p[i]].push_back(i);          
    }
    vector<int>order;
    order.reserve(n+1);
    order.push_back(0);
    for(size_t i=0; i<order.size(); i++){
        int v=order[i];
        for(int c : ch[v]){
            order.push_back(c);
        }
    }
    vector<int> h(n+1,0), sz(n+1,0);
    for(int idx=(int)order.size()-1; idx>=1; idx--){
        int v=order[idx];
        int best=0, s=1;
        for(int c : ch[v]){
            if(h[c]>best) best=h[c];
            s+=sz[c];
        }
        h[v]=best + 1;
        sz[v]=s;
    }
    priority_queue<tuple<int, int, int>> pq;
    for(int c : ch[0]){
            pq.push(make_tuple(h[c], sz[c], c));
    }
    int ans=0;
    vector<int>taken;
    for(int sem=0; sem<m && !pq.empty(); sem++){
        taken.clear();
        while((int)taken.size()<k && !pq.empty()){
            taken.push_back(get<2>(pq.top()));
            pq.pop();
        }
        ans+=(int)taken.size();
        for(int v : taken)
            for(int c : ch[v]){
            pq.push(make_tuple(h[c], sz[c], c));
            }
    }
    cout<<ans<<"\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
     solve();
    }
    return 0;
} 
