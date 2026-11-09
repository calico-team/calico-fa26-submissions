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
// template<class T, class... U> void re(T& x, U&... y){
//     if constexpr(requires { cin >> x; }){
//         cin >> x;
//     } else if constexpr(requires { x.first; x.second; }){
//         re(x.first, x.second);
//     } else if constexpr(is_same_v<T, V<bool>>){
//         for(auto&& v:x){
//             bool b = false;
//             re(b);
//             v=b;
//         }
//     } else {
//         for(auto& v:x) re(v);
//     }
//     (re(y), ...);
// }

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

// fenwick tree
// 1-indexed!!!!!!!
template<typename T>
class fenwick {
  public:
    vector<T> arr;
    fenwick (int n) {
      arr.resize(n+4);
    }
    void add (int index, T val) {
        if(index<0) return;
      index++;
      for (; index < (int)arr.size(); index += (index & (-index))) {
        arr[index] += val;
      }
    }
    T query(int index) {
      index=min(index, int(1e5));
      if(index<0) return 0;
      index++;
      T sum = 0;
      for (; index > 0; index -= (index & (-index))) {
        sum += arr[index];
      }
      return sum;
    }
};

fenwick<int> rt(1e5+2), up(1e5+2);


void solve(){
    int n, k; cin >> n >> k;

    ll ans=ll(k)*n;

    
    map<int,vector<vi>> levels;
    
    rep(i,1,n){
        int x,y,z; cin >> x >> y >> z;
        char d; cin >> d;
        levels[x+y].pb({x, z, d=='N'});
    }
    
    for(auto p:levels){
        // int diag=p.f;
        // pr("diag", diag);
        V<vi> pts = p.s;
        set<int> Zs;
        map<int, V<vi>> vec;
        for(vi v:pts){
            int x=v[0], z=v[1], d=v[2];
            vec[z].pb({d, x});
            Zs.insert(-z);
        }

        // pr("pts", pts);
        // pr("Zs", Zs);

        for(int z:Zs){
            z=-z;
            sort(all(vec[z]));
            reverse(all(vec[z]));
            // pr("z", z);
            // pr("vec", z, vec[z]);
            for(auto v:vec[z]){
                int d=v[0], x=v[1];
                // pr("xd", x, d);
                if(d){ // up
                    ans-=rt.query(x)-rt.query(x-k);
                    // pr("rt query", x, rt.query(x));
                }
                else{
                    ans-=up.query(x+k-1)-up.query(x-1);
                    // pr("rt query", x, rt.query(x));
                }
            }
            for(auto v:vec[z]){
                int d=v[0], x=v[1];
                if(d){
                    up.add(x, 1);
                    // pr("up add", x);
                }
                else rt.add(x, 1);
            }
        }

        for(vi v:pts){
            int x=v[0], _=v[1], d=v[2];
            if(d) up.add(x, -1);
            else rt.add(x, -1);
        }
    }
    pr(ans);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int t=1;
    cin >> t; // Uncomment for multiple test cases.
    while(t--) solve();
    return 0;
}
