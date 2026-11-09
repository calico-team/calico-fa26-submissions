#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);string phase;if(!(cin>>phase))return 0;int n;cin>>n;if(phase=="FIRST"){vector<int> p(n+1);int xr=0;for(int i=0,u,v;i<n-1;i++){cin>>u>>v;if(u>v)swap(u,v);p[v]=u;xr^=u;}cout<<xr;for(int i=2;i<=n;i++)cout<<' '<<p[i];cout<<'\n';}else{vector<int>a(n+1);int miss=-1,xr=0;for(int i=1;i<=n;i++){cin>>a[i];if(a[i]==-1)miss=i;else xr^=a[i];}if(miss==1)a[1]=xr;else a[miss]=a[1]^xr;for(int i=2;i<=n;i++)cout<<a[i]<<' '<<i<<'\n';}}
