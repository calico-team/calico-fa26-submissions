#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;

void solve(){
    int n,k,x,y,z;
    char d[10];
    vector<pair<int,int>> nor;
    map<int,vector<int>> east;
    scanf("%d %d",&n,&k);
    for(int i=0; i<n; i++){
        scanf("%d %d %d %s",&x,&y,&z,d);
        if(d[0]=='E') east[x+y].push_back(x);
        else nor.push_back({x,y});
    }
    int res=n*k;
    for(auto [x,y]:nor){
        if(!east.count(x+y)) continue;
        auto &t=east[x+y];
        res-=lower_bound(t.begin(),t.end(),x)-lower_bound(t.begin(),t.end(),x-k+1);
    }
    printf("%d\n",res);
}

int main(){
    //freopen("p4.in","r",stdin);
    //freopen("p4.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--) solve();
    return 0;
}