#include <bits/stdc++.h>
using namespace std;
using ll= long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test;
    cin>>test;
    while(test--){
        int n;
        ll r;
        cin>>n>>r;
        deque<ll>q;
        bool ceck=true;
        for(int i=0;i<n;i++){
            ll t;
            cin>>t;

            while(!q.empty() && q.front()<=t){
                q.pop_front();
            }
            if(q.size()==2){
                ceck=false;
            }
            else if(ceck){
                ll st;
                if(q.empty()){
                    st=t;
                }
                else{
                    st=q.back();
                }
                q.push_back(st+r);
            }
        }
        if(ceck){
            cout<<"YES"<<'\n';
        }
        else{
            cout<<"NO"<<'\n';
        }
    }
}
