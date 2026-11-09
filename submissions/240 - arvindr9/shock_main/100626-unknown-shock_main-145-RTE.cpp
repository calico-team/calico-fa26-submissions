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

int sqrrt(int x) {
    if (x < 0) return -1;
    int y = sqrt(x);
    while (y * y < x) y++;
    while (y * y > x) y--;
    return y;
}

#define i32 int32_t

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<pi> ops(q+1);
        vector<int> P(q+1);
        lep(qq,1,q) {
            cin >> ops[qq].f >> ops[qq].s;
            cin >> P[qq];
        }
        bool transposed = false;
        if (n > m) {
            swap(n,m);
            lep(qq,1,q) {
                swap(ops[qq].f, ops[qq].s);
            }
            transposed = true;
        }

        vector<vector<vector<pair<i32,i32>>>> events(n, vector<vector<pair<i32,i32>>>(m+1)); // add / remove events
        vector<vector<int>> ans(n, vector<int>(m));

        lep(qq,1,q) {
            int oi = ops[qq].f;
            int oj = ops[qq].s;
            int pval = P[qq];
            lep(i,0,n-1) {
                int di = abs(i - ops[qq].f);
                // di^2 + dj^2 <= pval^2
                // dj^2 <= pval^2 - di^2
                int dj = sqrrt(pval * pval - di * di);
                if (dj < 0) continue;
                int L = max(0LL, oj - dj);
                int R = min(m-1, oj + dj);
                DEBUG(qq,i,di,dj,L,R);
                events[i][L].pb({qq,+1});
                events[i][R+1].pb({qq,-1});
            }
        }

        // DEBUG(events[1]);

        lep(i,0,n-1) {
            set<i32> S;
            lep(j,0,m-1) {
                for (auto [v, typ]: events[i][j]) {
                    if (typ == 1) S.insert(v);
                    else S.erase(v);
                }
                if (!S.empty()) {
                    int which = *S.rbegin();

                    int di = i - ops[which].f;
                    int dj = j - ops[which].s;
                    int pval = P[which];

                    
                    int val = pval * pval - di * di - dj * dj + 1;
                    DEBUG(i,j,S,which,val);
                    ans[i][j] = val;
                }
            }
        }


        if (transposed) {
            // TODO: transpose the answer
            vector<vector<int>> nxt(m, vector<int>(n));
            lep(i,0,n-1) {
                lep(j,0,m-1) {
                    nxt[j][i] = ans[i][j];
                }
            }
            swap(ans,nxt);
            swap(n,m);
        }

        lep(i,0,n-1) {
            lep(j,0,m-1) {
                cout << ans[i][j] << " \n"[j==m-1];
            }
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