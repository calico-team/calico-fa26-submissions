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
    int n,r;cin>>n>>r;
    int arr[2] = {(int)-1e9, (int)-1e9};
    int a[n];
    for(int i=0;i<n;i ++) cin >> a[i];
    for(int i=0;i<n; i++){
      int x = a[i];
      sort(arr, arr+2);
      if(arr[0] >  x){
        cout << "NO\n";
        return;
      }
      arr[0] = max(arr[1] + r, x + r);
    }
    cout << "YES\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t=1; cin>>t;
    while(t--)solve();
}
