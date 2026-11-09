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
    string S;
    cin >> S;
    if (S == "FIRST") {
        int n;
        cin >> n;
        vector<vector<int>> adj(n+1);
        lep(i,1,n-1) {
            int u,v;
            cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vector<int> par(n+1);
        auto dfs = [&](auto &self, int u, int p) -> void {
            if (p != 0) {
                par[u] = p;
            }
            for (int v: adj[u]) {
                if (v != p) {
                    self(self,v,u);
                }
            }
        };
        dfs(dfs,1,0);
        int x = 0;
        lep(i,2,n) x ^= par[i];
        par[1] = x;
        lep(i,1,n) {
            cout << par[i] << " \n"[i==n];
        }
    } else {
        int n;
        cin >> n;
        vector<int> a(n+1);
        lep(i,1,n) {
            cin >> a[i];
        }
        if (a[1] != -1) {
            int x = 0;
            lep(i,1,n) {
                if (a[i] != -1) x ^= a[i];
            }
            lep(i,1,n) {
                if (a[i] == -1) a[i] = x;
            }
        }
        lep(u,2,n) {
            cout << a[u] << " " << u << "\n";
        }
    }
}

/*
Reminders to self:
- Reread the problem statement (!!!)
- Have a plan before implementing
- (if possible) Read up to div2E in the first 30 minutes
- Don't confuse n and m. 1<<x vs 1LL<<x
*/