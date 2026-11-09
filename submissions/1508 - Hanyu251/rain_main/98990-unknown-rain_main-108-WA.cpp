#include<bits/stdc++.h>
using namespace std;
#define printf if(false)


void solve(){
    int n,k;
    cin>>n>>k;
    vector<pair<int,int>>ngoing,egoing;
    int maxxpy=0;
    for(int i=0;i<n;++i){
        int x,y,z;cin>>x>>y>>z;
        char d;cin>>d;
        if(d=='N')ngoing.push_back({x,y});
        if(d=='E')egoing.push_back({x,y});
        maxxpy=max(maxxpy,x+y);
    }
    vector<vector<pair<int,int>>>table(maxxpy+1);

    sort(ngoing.begin(),ngoing.end(),less<>());
    sort(egoing.begin(),egoing.end());
    for(auto[x,y]:ngoing){
        // if(table[x+y].empty())table[x+y].push_back({-1,1});
        table[x+y].push_back({x,table[x+y].size()+1});
    }

    for(int xpy=0;xpy<=maxxpy;++xpy){
        if(table[xpy].empty())continue;
        printf("table[%d]:\t",xpy);
        for(auto [x,count]:table[xpy]){
            printf("(x=%d,#=%d), ",x,count);
        }
        // cout<<endl;
    }

    long long ans=n*k;

    for(auto[x,y]:egoing){
        auto upper=upper_bound(table[x+y].begin(),table[x+y].end(),pair<int,int>{x+k-1,1e9});
        auto lower=lower_bound(table[x+y].begin(),table[x+y].end(),pair<int,int>{x,1e9});
        printf("egoing %d,%d, %d,%s,%d,%s\n",x,y,upper!=table[x+y].end()?upper->second:-1,upper==table[x+y].end()?"hitupper":"",lower!=table[x+y].end()?lower->second:-1,lower==table[x+y].end()?"hitlower":"");
        int delta=            (upper==table[x+y].end()?table[x+y].size()+1:upper->second)
            -(lower==table[x+y].end()?table[x+y].size()+1:lower->second);

        ans-=delta;
        printf("\tdt=-%d\n",delta);
    }

    cout<<ans<<endl;
}
int main(){
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    int t;cin>>t;while(t--){
        solve();
    }
}
