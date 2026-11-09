#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;


const int N = 100005;

void solve(){

    int n,k; cin >> n >> k;
    vector<array<int,3>> a(n); //0 means north 1 means east
    for(int i=0; i<n; i++){
        int x,y,z; cin >> x >> y >> z;
        char c; cin >> c;
        a[i][0] = x;
        a[i][1] = y;
        a[i][2] = (c == 'E' ? 1 : 0);
    }
    sort(a.begin(),a.end());
    
    vector<vector<int>> cnt(2*N,vector<int>(2));
    int l = 0;
    ll res = 0;
    for(int r=0; r<n; r++){
        while(l < r && a[r][0] - a[l][0] >= k){
            //remove l
            cnt[a[l][0] + a[l][1]][a[l][2]]--;
            l++;
        }
        int sum = a[r][0] + a[r][1];
        int tp = a[r][2];
        if(tp == 0) res += cnt[sum][1];
        cnt[sum][tp]++;
    }

    cout << 1LL*n*k - res << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        solve();
    }
}   