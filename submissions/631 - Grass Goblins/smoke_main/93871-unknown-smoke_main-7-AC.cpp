#include<bits/stdc++.h>

#define ll long long
#define pii pair<int,int>
#define tiii tuple<int,int,int>

using namespace std;

string o;

void solve(){
    int n,r;
    cin >> n >> r;
    vector<int> arr(n+1);
    for(int i = 0; i < n; i++){
        cin >> arr[i+1];
    } 

    int cnt = 2;
    int cooldown = -1;
    for(int i = 0; i < n; i++){
        int e = arr[i+1]-arr[i];
        while(e > 0 || cooldown == 0){
            if(cnt == 2) break;
            int rem = min(cooldown,e);
            cooldown -= rem;
            e -= rem;
            if(cooldown == 0){
                cnt++;
                if(cnt != 2)cooldown = r;
                else cooldown = -1; 
            }
        }
        if(cnt == 0){
            cout << "NO\n";
            return;
        }
        cnt--;
        if(cooldown==-1)cooldown = r;
    }
    cout << "YES\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }

    //cout << o << endl;
}