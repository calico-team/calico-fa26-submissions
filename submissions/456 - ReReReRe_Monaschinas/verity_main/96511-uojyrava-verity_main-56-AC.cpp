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
  int n,k;cin>>n>>k;
  vector<int> a(n,-1);
  vector<char>let(k);
  for(auto &e: let)cin >> e;
  for(int i=0;i<k; i++){
    string cur = "";
    for(int j=0;j<n; j++){
      if(a[j]!=-1) cur += let[a[j]];
      else cur += let[i];
    }
    cout << cur << endl;
    cout.flush();
    
    string res; cin>>res;
    if(res == "CORRECT"){
      return;
    }
    for(int j=0;j<n; j++){
      if(res[j]==let[i]) a[j]=i;
    }
  }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t=1; cin>>t;
    while(t--)solve();
}
