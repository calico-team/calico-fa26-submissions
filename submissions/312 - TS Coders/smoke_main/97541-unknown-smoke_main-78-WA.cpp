#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int T;cin>>T;while(T--){int n;long long r;cin>>n>>r;priority_queue<long long,vector<long long>,greater<long long>> q;for(int i=0;i<n;i++){long long t;cin>>t;while(!q.empty()&&q.top()<=t)q.pop();if(q.size()>=2){cout<<"NO\n";for(++i;i<n;i++)cin>>t;goto next_case;}q.push(t+r);}cout<<"YES\n";next_case:;}}
