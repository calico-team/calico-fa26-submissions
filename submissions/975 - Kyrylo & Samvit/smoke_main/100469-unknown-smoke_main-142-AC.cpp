// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    long long r;
    cin>>n>>r;
    vector<long long>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int charges=2;
    queue<long long>q;
    for(int i=0;i<n;i++){
        long long t=a[i];
        while(!q.empty()&&q.front()<=t){
            q.pop();
            charges++;
        }
        if(charges==0){
            cout<<"NO\n";
            return;
        }
        long long finish_time=q.empty()?t+r:q.back()+r; 
        q.push(finish_time);
        charges--;
    }
    cout<<"YES\n";
}


int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if(cin>>t){
        while(t--){
            solve();
        }
    }
    return 0;
}
