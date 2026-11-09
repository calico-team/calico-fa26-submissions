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

string query(string S) {
    cout << S << endl;
    string res;
    cin >> res;
    return res;
}



signed main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string alpha;
        lep(i,1,k) {
            string S;
            cin >> S;
            alpha += S;
        }
        string ans;
        lep(i,1,n) ans += '_';
        bool done = false;
        lep(i,0,k-1) {
            string S;
            lep(j,1,n) S += alpha[i];
            string res = query(S);
            lep(j,0,n-1) {
                if (res[j] != '_') ans[j] = res[j];
            }
            if (res == "CORRECT") {
                done = true;
                break;
            }
        }
        if (!done) query(ans);
    }
}

/*
Reminders to self:
- Reread the problem statement (!!!)
- Have a plan before implementing
- (if possible) Read up to div2E in the first 30 minutes
- Don't confuse n and m. 1<<x vs 1LL<<x
*/