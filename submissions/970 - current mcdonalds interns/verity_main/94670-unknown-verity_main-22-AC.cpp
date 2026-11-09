#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
void fio(const std::string& fn) {freopen((fn+".in").c_str(), "r", stdin); freopen((fn+".out").c_str(), "w", stdout);}
#define vec vector
#define str string
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fi first
#define se second
#define fr front
#define bk back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define rep(i, st, end) for (int i=(st); i<(end); i++)
#define arrin(a) for (auto &x:(a)) cin>>x
#define cont continue
#define accum accumulate
#define sum(a) accum(all(a), 0LL)
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define uset unordered_set
#define umap unordered_map
#define umset unordered_multiset
#define hmap hash_map
#define hmset hash_multiset
#define hset hash_set
#define mset multiset
#define que queue
#define dq deque
#define pq priority_queue
#define dpq pq<int, vec<int>, greater<int>>
#define ipq pq<int, vec<int>, less<int>>
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long double ld;
typedef long long ll;
using namespace std;
inline void solve() {
    int n, k; cin>>n>>k; //n = length, k = num of letters;
    vec<char> al(k); arrin(al); //holds alphabet of letters we can use
    string known(n, al[0]); //assume the first letter until another is confirmed
    for (int i=1; i<k; i++) { //i = current letter we check from al (i=1 bc we start al[0])
        string cand(n, al[i]); //make a cand to check a single letter fully at any position
        cout<<cand<<endl; //check our newest guess of just a single char
        string resp; if (!(cin>>resp)) return; //judge response to check against
        if (resp=="CORRECT") return; //exit if we get it right
        for (int j=0; j<n; j++) { //j is pos of letter in guess,
            if (resp[j]!='_') { //if we have any letters back, update known to track it
                known[j] = resp[j];
            }
        }
    }
    cout<<known<<endl; //after each letter in al has been checked
    string resp; cin>>resp; //output the built string
}
int main() {
    //str fn = ""; fio(fn);
    fast;
    int t = 1; cin>>t;
    while (t--) solve();
    return 0;
}
