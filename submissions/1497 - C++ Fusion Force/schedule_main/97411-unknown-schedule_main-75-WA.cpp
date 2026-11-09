#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    long long t; cin >> t;
    while(t--){
        long long n, m, k; cin >> n >> m >> k;
        vector<long long> a[n+1];
        for(long long i = 0; i<n; ++i) {
            long long e; cin >> e;
            a[e].push_back(i+1);
        }
        bool done[n+1]={};
        queue<long long> q;
        for(long long j = 0; j<k && !a[0].empty(); j++) {
            if(!done[a[0].back()]) {
                q.push(a[0].back());
                done[a[0].back()] = 1;
            }
            a[0].pop_back();
        }
        long long m_ = 0;
        while(!q.empty() && m_ < m-1){
            long long curr = q.front(); q.pop();
            for(long long j = 0; j<k && !a[curr].empty(); j++) {
                if(!done[a[curr].back()]) {
                    q.push(a[curr].back());
                    done[a[curr].back()] = 1;
                }
                a[curr].pop_back();
            }
            m_++;
        }
        long long tot = 0;
        for(long long i = 0; i<=n; ++i)  tot += done[i];
        cout << tot << '\n';
    }
}