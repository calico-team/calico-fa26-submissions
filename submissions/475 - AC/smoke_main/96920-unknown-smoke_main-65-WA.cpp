#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i=(a); i<=(b); i++)
#define per(i, a, b) for(int i=(a); i>=(b); i--)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second
#define nl '\n'
#define V vector

typedef long long ll;
typedef V<int> vi;
typedef pair<int, int> pii;

template<class T> bool ckmin(T& a, const T& b){
    return b<a ? a=b, 1 : 0;
}
template<class T> bool ckmax(T& a, const T& b){
    return a<b ? a=b, 1 : 0;
}

// Size containers first: vi a(n); V<V<ll>> g(n, V<ll>(m)); re(a, g);
// Reads scalars, strings, pairs, arrays, and nested vectors in order (C++20).


// Keep your original display format: vectors [1, 2], pairs (1, 2).
template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p);
template<class T> ostream& operator<<(ostream& os, const V<T>& v);

template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p){
    return os << '(' << p.first << ", " << p.second << ')';
}
template<class T> ostream& operator<<(ostream& os, const V<T>& v){
    os << '[';
    rep(i, 0, sz(v)-1){
        if(i) os << ", ";
        os << v[i];
    }
    return os << ']';
}
template<class... T> void pr(const T&... x){
    int i=0;
    ((cout << (i++ ? " " : "") << x), ...);
    cout << nl;
}

void solve(){
    int n, r; cin >> n >> r;
    vi a(n);
    rep(i,0,n-1) cin >> a[i];
    bool ok=1;
    // sort(all(a));
    rep(i,1,n-1){
        if(a[i]-a[i-1]<r) ok=0;
    }
    pr(ok?"YES":"NO");
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int t=1;
    cin>>t; // Uncomment for multiple test cases.
    while(t--) solve();
    return 0;
}
