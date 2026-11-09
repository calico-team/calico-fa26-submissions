//knownasjason is a coder
//euclid lowk buns <<<<< archimedes
//we ARE back

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#define ll long long
using vi = vector<ll>;
#define pb emplace_back
//using i128 = __ll128;
 ll t;
 ll call = 0;
 #define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define rep(i,n) for (ll i = 0; i < (n); i++)
#define vin(v) ll n; cin >> n; vector<ll> v(n); for (ll &x : v) cin >> x;
#define fileio(name) do { \
    freopen(name ".in", "r", stdin); \
    freopen(name ".out", "w", stdout); \
} while (0)
#define read(v) for (auto &x : v) cin >> x;
constexpr char nl = '\n';
template<typename T>
void prll(const vector<T>& a) {
    for (ll i = 0; i < sz(a); i++) {
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
 ll n; vector<ll>s,lz;
 ST(ll n):n(n),s(4*n),lz(4*n){}

 void p(ll x,ll l,ll r){
  if(!lz[x])return;
  s[x]+=lz[x]*(r-l+1);
  if(l<r)lz[x*2]+=lz[x],lz[x*2+1]+=lz[x];
  lz[x]=0;
 }

 void u(ll L,ll R,ll v,ll x,ll l,ll r){
  p(x,l,r);
  if(R<l||r<L)return;
  if(L<=l&&r<=R){
   lz[x]+=v;
   p(x,l,r);
   return;
  }
  ll m=(l+r)/2;
  u(L,R,v,x*2,l,m);
  u(L,R,v,x*2+1,m+1,r);
  s[x]=s[x*2]+s[x*2+1];
 }

 void u(ll l,ll r,ll v){
  u(l,r,v,1,0,n-1);
 }

 ll q(ll L,ll R,ll x,ll l,ll r){
  p(x,l,r);
  if(R<l||r<L)return 0;
  if(L<=l&&r<=R)return s[x];
  ll m=(l+r)/2;
  return q(L,R,x*2,l,m)+q(L,R,x*2+1,m+1,r);
 }

 ll q(ll l,ll r){
  return q(l,r,1,0,n-1);
 }
};


void onlyn() {
    call = 1;
    t=1;
}
void ihatewinning() {
    ll n,k;
    cin >> n >> k;
    vector<pair<pair<ll,ll>,pair<ll,ll>>> arr(n);

    for (ll i =0; i < n; i++) {
        ll x,y;
        ll dx=0;
        ll dy = 0;
        cin >> x>>y;
        ll r;
        cin >> r;
        char d;
        cin >> d;
        if (d=='E') {
            dx=1;
        } else {
            dy = 1;
        }
        
        arr[i]={{x,y},{dx,dy}};
    } 
    set<ll> sums;

    for (ll i = 0; i < n; i++) {
        sums.insert(arr[i].first.first+arr[i].first.second);
    }

    map<ll,ll> comp;
    ll id = 0;
    for (ll i : sums) {
        comp.insert({i,id});
        id++;
    }

    vector<vector<pair<ll, ll>>> rows(sz(sums));

    for (ll i = 0; i < n; i++) {
        ll group = comp[arr[i].first.first+arr[i].first.second];
        rows[group].push_back({arr[i].first.first,arr[i].second.first});
    }
    ll ans = k*n;

    for (auto row : rows) {
        sort(all(row));

        deque<ll> east;

        for (pair<int,int> p : row) {
            if (p.second == 1) {
                east.push_back(p.first);
            } else {
            while (!east.empty() && p.first-east.front()>=k) {
                east.pop_front();
            }

            ans -= (ll)east.size();
            }
    }
}

cout << ans << nl;


    return;
}

signed main() {
    ios::sync_with_stdio(false);
cin.tie(nullptr);
//    onlyn();
    if (call == 0) {
	cin >> t;
    }
    while (t--) {
        ihatewinning();
    }
    
}


