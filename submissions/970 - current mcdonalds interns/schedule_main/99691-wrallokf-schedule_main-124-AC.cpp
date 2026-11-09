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
    int n, m, k; cin>>n>>m>>k; //courses, sems, and maximum num of courses per sem
    vec<vec<int>> tree(n+1); //tree[course] holds the courses that have this course as a prereq
    for (int i=1; i<n+1; i++) { //read the prereq for each course
        int prereq; cin>>prereq; //0 means the course has no prereq, and is the root of its own tree
        tree[prereq].pb(i); //put this course under its prereq or 0 if none
    }
    vec<int> dep(n+1); //dep(i) counts courses whose earliest semester is d
    queue<pii> crs; //queue holds each course and its depth
    for (int c:tree[0]) crs.push({c, 1}); //courses with no prereq start at depth 1
    while (!crs.empty()) { //while the course queue isnt empty
        auto [c, d] = crs.fr(); crs.pop(); //take the course and its depth (starting from earliest)
        //map the pair to its course and depth to be handled separately
        dep[d]++; //count this course at its earliest possible semester, since its a prereq to all of its children
        for (int ch:tree[c]) crs.push({ch, d+1}); //its children need one more semester than the current course, so just push them onto it with d+1;
    }
    int w = 0, c = 0; //w = temp to hold the ones from next sem, c = is the running total
    for (int i=1; i<min(m, n)+1; i++) { //for every sem, we need to find the courses that can be taken
        w+=dep[i]; //add courses which earliest can be taken in i
        int tak = min(k, w); //count the courses that can be taken now
        c+=tak; //add the taken in this sem to the total
        w-=tak; //leave the rest of them till next sem, if there are any left
    }
    cout<<c<<"\n"; //print the maximum number of courses
}
int main() {
    //str fn = ""; fio(fn);
    fast;
    int t; cin>>t;
    while (t--) solve();
    return 0;
}

