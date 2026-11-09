#include <bits/stdc++.h>
using namespace std;
struct Drone{long long x,y,z;char dir;};
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int T;cin>>T;while(T--){int n;long long k;cin>>n>>k;vector<Drone>a(n);for(auto &d:a)cin>>d.x>>d.y>>d.z>>d.dir;vector<vector<long long>> hidden(n);for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){long long t=-1;if(a[i].dir=='E'&&a[j].dir=='N'){long long x=a[j].x-a[i].x,y=a[i].y-a[j].y;if(x==y&&x>=0)t=x;}else if(a[i].dir=='N'&&a[j].dir=='E'){long long x=a[i].x-a[j].x,y=a[j].y-a[i].y;if(x==y&&x>=0)t=x;}if(t>=0&&t<k){if(a[i].z<a[j].z)hidden[i].push_back(t);else if(a[j].z<a[i].z)hidden[j].push_back(t);}}long long blocked=0;for(auto &v:hidden){sort(v.begin(),v.end());blocked+=unique(v.begin(),v.end())-v.begin();}long long ans=1LL*n*k-blocked;cout<<ans<<'\n';}}
