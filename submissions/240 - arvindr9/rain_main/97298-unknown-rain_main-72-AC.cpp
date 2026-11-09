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
        int n, k;
        cin >> n >> k;
        vector<int> X(n+1), Y(n+1), Z(n+1);
        vector<char> dir(n+1);
        map<int,vector<int>> e_groups, n_groups;
        lep(i,1,n) {
            cin >> X[i] >> Y[i] >> Z[i] >> dir[i];
            if (dir[i] == 'E') {
                e_groups[X[i]+Y[i]].pb(i);
            } else {
                n_groups[X[i]+Y[i]].pb(i);
            }
        }

        int sub = 0;

        for (auto [x,v]: n_groups) {
            DEBUG(x,v);
        }

        for (auto [xpy, ve]: e_groups) {
            DEBUG(xpy,ve);
            // DEBUG(n_groups);
            if (!n_groups.count(xpy)) continue;
            vector<int> vn = n_groups[xpy];
            DEBUG(vn);
            vector<int> xmys;
            for (int idx: vn) {
                xmys.pb(X[idx] - Y[idx]);
            }
            sort(xmys.begin(),xmys.end());

            int se = ve.size();
            int sn = vn.size();

            for (int e_idx: ve) {
                int xmy = X[e_idx] - Y[e_idx];
                DEBUG(e_idx,xmy,xmys);
                // find range 
                int L = lower_bound(xmys.begin(),xmys.end(),xmy) - xmys.begin();
                int R = lower_bound(xmys.begin(),xmys.end(),xmy+2*(k-1)+1) - xmys.begin()-1;
                DEBUG(L,R);
                if (L <= R) sub += (R-L+1);
            }

        }

        DEBUG(sub);


        int ans = k * n - sub;

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