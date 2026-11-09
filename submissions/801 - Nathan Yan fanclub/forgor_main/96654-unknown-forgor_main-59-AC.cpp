//knownasjason is a coder
//euclid lowk buns <<<<< archimedes
//we ARE back

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#define int long long
using vi = vector<int>;
#define pb emplace_back
//using i128 = __int128;
 int t;
 int call = 0;
 #define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define rep(i,n) for (int i = 0; i < (n); i++)
#define vin(v) int n; cin >> n; vector<int> v(n); for (int &x : v) cin >> x;
#define fileio(name) do { \
    freopen(name ".in", "r", stdin); \
    freopen(name ".out", "w", stdout); \
} while (0)
#define read(v) for (auto &x : v) cin >> x;
constexpr char nl = '\n';
template<typename T>
void print(const vector<T>& a) {
    for (int i = 0; i < sz(a); i++) {
        cout << a[i] << " \n"[i == sz(a) - 1];
    }
}
ll binexpo(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
// lazy segment tree
// ST xyz(n);
// xyz.u(l,r,x); add x to [l,r]
// xyz.q(l,r); query sum on [l,r] inclusive
struct ST{
 int n; vector<ll>s,lz;
 ST(int n):n(n),s(4*n),lz(4*n){}

 void p(int x,int l,int r){
  if(!lz[x])return;
  s[x]+=lz[x]*(r-l+1);
  if(l<r)lz[x*2]+=lz[x],lz[x*2+1]+=lz[x];
  lz[x]=0;
 }

 void u(int L,int R,ll v,int x,int l,int r){
  p(x,l,r);
  if(R<l||r<L)return;
  if(L<=l&&r<=R){
   lz[x]+=v;
   p(x,l,r);
   return;
  }
  int m=(l+r)/2;
  u(L,R,v,x*2,l,m);
  u(L,R,v,x*2+1,m+1,r);
  s[x]=s[x*2]+s[x*2+1];
 }

 void u(int l,int r,ll v){
  u(l,r,v,1,0,n-1);
 }

 ll q(int L,int R,int x,int l,int r){
  p(x,l,r);
  if(R<l||r<L)return 0;
  if(L<=l&&r<=R)return s[x];
  int m=(l+r)/2;
  return q(L,R,x*2,l,m)+q(L,R,x*2+1,m+1,r);
 }

 ll q(int l,int r){
  return q(l,r,1,0,n-1);
 }
};


void onlyn() {
    call = 1;
    t=1;
}
void ihatewinning() {
    string s;
    cin >> s;
    if (s=="FIRST") {
        int n;
        cin >> n;

        vector<vector<int>> adj(n+1);
        for (int i = 0; i < n-1; i++) {
            int a,b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        vi seen(n+1,0);
        seen[1]=1;
        queue<int> q;
        q.push(1);
        vi parent(n+1,-1);

        while (!q.empty()) {
            int x = q.front();
            q.pop();

            for (int i : adj[x]) {
                if (seen[i]==0) {
                    q.push(i);
                    seen[i]=1;
                    parent[i]=x;
                }
            }

        }
      //  print(parent);

        vector<int> ans(n);
        int cur = 0;
        for (int i = n; i > 1; i--) {
            ans[i-1]=parent[i]-1;
            cur = cur^(parent[i]-1);
        }
        ans[0]=cur;


        print(ans);










    } else {
        int n;
        cin >> n;
        vi arr(n);
        read(arr);
        int cur = 0;

        for (int i = 0; i < n; i++) {
            if (arr[i] != -1) {
                cur = cur^arr[i];
            }
        }

        for (int i = 0; i < n; i++) {
            if (arr[i]==-1) {
                arr[i]=cur;
            }
        }

        for (int i = 1; i < n; i++) {
            cout << i+1<<" "<<arr[i]+1<< nl;

        }
        //print(arr);



    }


    return;
}

signed main() {
    ios::sync_with_stdio(false);
cin.tie(nullptr);
   onlyn();
    if (call == 0) {
	cin >> t;
    }
    while (t--) {
        ihatewinning();
    }
    
}


