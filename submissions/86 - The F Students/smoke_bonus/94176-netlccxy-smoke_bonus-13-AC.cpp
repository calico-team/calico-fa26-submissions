#include <bits/stdc++.h>
using namespace std;



void solve(){
    int n,r;
    cin >> n >> r;
    priority_queue<vector<int>,vector<vector<int>>, greater<vector<int>>> events;
    int inp;
    for(int i=0;i<n;i++){
        cin >> inp;
        events.push({inp,1});
    }
    int charges=2;
    bool recharging=false;
    while(events.size()>0){
        vector<int> event=events.top();
        events.pop();
        if(event[1]==0){
            charges++;
            if(charges==2) recharging=false;
            else{
                events.push({event[0]+r,0});
            }
        }
        else{
            if(charges<1){
                cout << "NO\n";
                return;
            }
            else{
                charges--;
                if(!recharging){
                    events.push({event[0]+r,0});
                    recharging=true;
                }
            }
        }
    }
    cout << "YES\n";
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tc=1;
  cin >> tc;
  for (int t=1;t<=tc;t++){
    solve();
  }
}