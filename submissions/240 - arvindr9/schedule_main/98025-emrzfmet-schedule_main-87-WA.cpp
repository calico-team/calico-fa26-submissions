#include <bits/stdc++.h>

using namespace std;

// debug template source: https://github.com/mzhang2021/cp-library/blob/master/implementations/temp.cpp

#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define DEBUG(...) 6
#endif
 
template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << "\033[1;35m" << s << "\033[0;32m = \033[33m" << x << "\033[0m\n";}
template<typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++; else
if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << "\033[1;35m" << s.substr(0, i) << "\033[0;32m = \033[33m" << x << "\033[31m | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}

#define int long long
#define pi pair<int,int>
#define mp make_pair
#define pb push_back
#define vi vector<int>
#define eb emplace_back
#define f first
#define s second
#define lep(i,a,b) for (int i = (a); i <= (b); i++)
#define rep(i,a,b) for (int i = (a); i >= (b); i--)
const int inf = 1e18;
int t;

void yay() {
    cout << "YES\n";
}

void gg() {
    cout << "NO\n";
}

void A(string S) {
    cout << S << "\n";
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> indeg(n+1), outdeg(n+1);
        vector<vector<int>> adj(n+1);

        lep(i,1,n) {
            int p;
            cin >> p;
            if (p != 0) {
                indeg[i]++;
                adj[p].pb(i);
            }
        }

        priority_queue<pi, vector<pi>, greater<pi>> pq; // (outdeg[u], u)
        lep(u,1,n) {
            if (indeg[u] == 0) {
                pq.push({outdeg[u],u});
            }
        }
        int ans = 0;
        // m semesters
        lep(it,1,m) {
            vector<pi> nxt;
            lep(inner,1,k) {
                if (pq.empty()) break;
                auto [_, u] = pq.top();
                pq.pop();
                ans++;
                for (int v: adj[u]) {
                    indeg[v]--;
                    if (indeg[v] == 0) {
                        nxt.pb({outdeg[v],v});
                    }
                }
            }
            for (auto [x,y]: nxt) pq.push({x,y});
        }
        cout << ans << "\n";
    }
}

/*
Reminders to self:
- Reread the problem statement (!!!)
- Have a plan before implementing
- (if possible) Read up to div2E in the first 30 minutes
- Don't confuse n and m. 1<<x vs 1LL<<x
*/