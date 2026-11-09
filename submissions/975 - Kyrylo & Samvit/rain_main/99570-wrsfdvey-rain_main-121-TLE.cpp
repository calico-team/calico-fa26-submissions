// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

struct D{long long x,y,z;char d;};
void solve(){
    int n,k;
    cin>>n>>k;
    vector<D>v(n);
    for(auto &d:v)cin>>d.x>>d.y>>d.z>>d.d;
    long long r=0;
    while(k--){
        for(int i=0;i<n;++i){
            bool c=false;
            for(int j=0;j<n&&!c;++j)
            if(i!=j&&v[i].x==v[j].x&&v[i].y==v[j].y&&v[i].z<v[j].z)c=true;
            if(!c)r++;
        }
        for(auto&d:v)(d.d=='E'?d.x:d.y)++;
    }
    cout<<r<<"\n";
}
int main(){
    int t;
    if(cin>>t)while(t--)solve();
}