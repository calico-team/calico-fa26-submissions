#include<bits/stdc++.h>
using namespace std;

vector<int>a(1e5+1);

void solve(){
    int n,u;cin>>n>>u;
    vector<char>totest(u);
    for(int i=0;i<u;++i)cin>>totest[i];
    string out="";
    for(int i=0;i<n;++i)out.append("_");
    for(char tt:totest){
        for(int i=0;i<n;++i)if(out[i]=='_')out[i]=tt;
        cout<<out<<endl;
        cin>>out;
        bool wrong=false;
        for(char i:out){
            if(i=='_')wrong=true;
        }
        if(!wrong)break;
    }
    cin>>out;
}
int main(){
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    int t;cin>>t;while(t--){
        solve();
    }
}
