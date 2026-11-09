#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define endl '\n'
#define int long long
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int BLOCK = 90;
void solve(){
  int n,k; cin>>n>>k;
  map<int,vector<int>> a,b;
  for(int i=0;i<n; i++){
    int x,y,z;cin>>x>>y>>z;
    char dir; cin>>dir;
    if(dir == 'E') a[x+y].push_back(y);
    else b[x+y].push_back(y);
  }
  int ans = n * k;
  for(auto [aa,bb]: b){
    auto &rr = a[aa];
    sort(all(rr));
    for(auto e: bb){
      int l = lower_bound(all(rr), e) - rr.begin();
      int r = lower_bound(all(rr), e+k) - rr.begin();
      ans -= r - l;
    }
  }
  cout << ans << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t=1; cin>>t;
    while(t--)solve();
}
