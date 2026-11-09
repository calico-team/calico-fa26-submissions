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

int di[4] = {-1,1,0,0};
int dj[4] = {0,0,-1,1};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<string> a(n);
        lep(i,0,n-1) {
            cin >> a[i];
        }

        // red: 0, blue: 1

        vector<vector<vector<bool>>> valid(n, vector<vector<bool>>(m, vector<bool>(2)));

        lep(i,0,n-1) {
            lep(j,0,m-1) {
                char c = a[i][j];
                if (c == 'R' or c == '.') valid[i][j][0] = true;
                if (c == 'B' or c == '.') valid[i][j][1] = true;
            }
        }
        vector<vector<vector<int>>> comp(n, vector<vector<int>>(m, vector<int>(2)));


        int timer = 0;
        auto dfs = [&](auto &self, int i, int j, int b) -> void {
            comp[i][j][b] = timer;
            lep(d,0,3) {
                int nexti = i + di[d];
                int nextj = j + dj[d];
                if (nexti < 0 or nexti >= n or nextj < 0 or nextj >= m) continue;
                if (!valid[nexti][nextj][b]) continue;
                if (comp[nexti][nextj][b]) continue;
                self(self,nexti,nextj,b);
            }
            int nextb = 1-b;
            if (!valid[i][j][nextb]) return;
            if (comp[i][j][nextb]) return;
            self(self,i,j,nextb);
        };

        lep(i,0,n-1) {
            lep(j,0,m-1) {
                lep(b,0,1) {
                    if (valid[i][j][b] and !comp[i][j][b]) {
                        timer++;
                        dfs(dfs,i,j,b);
                    }
                }
            }
        }

        lep(qq,1,q) {
            int r0, c0, r1, c1;
            cin >> r0 >> c0 >> r1 >> c1;
            int cS = comp[r0][c0][0];
            if (cS == comp[r1][c1][0] or cS == comp[r1][c1][1]) {
                yay();
            } else {
                gg();
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