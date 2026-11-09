/*
Author: @Faraz
 
 
**VENI VIDI VICI**
 
********************* بسم الله الرحمن الرحيم ***********************
*********************** وَقُل رَّبِّ زِدْنِي عِلْمًا **************************
 
╔══════════════════════════════════════════════════════╗
║                                                      ║
║        ███████╗ █████╗ ██████╗  █████╗ ███████╗      ║
║        ██╔════╝██╔══██╗██╔══██╗██╔══██╗╚══███╔╝      ║
║        █████╗  ███████║██████╔╝███████║  ███╔╝       ║
║        ██╔══╝  ██╔══██║██╔══██╗██╔══██║ ███╔╝        ║
║        ██║     ██║  ██║██║  ██║██║  ██║███████╗      ║
║        ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝      ║
╚══════════════════════════════════════════════════════╝
*/

#include <bits/stdc++.h>
using namespace std;
 
#ifdef LOCAL
        #include "algo/gimme.h"
#else
        #pragma GCC optimize("Ofast")
        #pragma GCC optimize("O3","unroll-loops")
        #pragma GCC target("avx,avx2,fma")
        #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
        #define gimme(...) 42
#endif

#define int                     long long 
#define vl                      vector<int>
#define all(x)                  (x).begin(), (x).end()
#define print(vec)              for (auto x : vec) {cout << x << ' ';} cout << endl;
#define pb                      push_back
#define f                       first
#define s                       second
#define done                    '\n'
#define Code_By_Faraz           ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define Spooder                 signed 
#define sz(x)                   ((int) x.size())
#define yes(x)                  cout << (x ? "YES\n" : "NO\n");
 
constexpr long long INF = 4e18;
const int Maxn = 5e5 + 67;
 
// WHY DO YOU KEEP SPYING ON MY CODE GO SOLVE A PROBLEM -_-
 
// ---------------- Main Solution: ----------------
 
void Faraz()
{
        int n, m, q; cin >> n >> m >> q;
        vector<string> a(n);
        for (int i = 0; i < n; ++i) 
        {
                string s; cin >> s;
                a[i] = s;
        }
        // tt = blue !tt = red;
        vector<vector<vl>> memo(201,vector<vl>(201,vl(2)));
        for (int i = 0; i < 201; ++i) 
        {
                for (int j = 0; j < 201; ++j) 
                {
                        for (int k = 0; k < n; ++k) 
                        {
                                memo[i][j][k] = -1;
                        }
                }       
        }
        vector<vector<vl>> vis(201,vector<vl>(201,vl(2)));
        for (int i = 0; i < 201; ++i) 
        {
                for (int j = 0; j < 201; ++j) 
                {
                        for (int k = 0; k < n; ++k) 
                        {
                                vis[i][j][k] = 0;
                        }
                }       
        }
        function<bool(int, int, int)> rec = [&](int x, int y, int tt)
        {
                memo[x][y][tt] = 0;
                if ((a[x][y] == 'B' and !tt) or (a[x][y] == 'R' and tt))
                {
                        memo[x][y][tt] = 0;
                        return false;
                }
                if (x == n - 1 and y == m - 1)
                {
                        memo[x][y][tt] = 1;
                        return true;
                }
                if (vis[x][y][tt]) return (bool)memo[x][y][tt];
                vis[x][y][tt] = 1;
                if (memo[x][y][tt] != -1) return (bool)memo[x][y][tt];

                if (a[x][y] == '.')
                {
                        if (x + 1 < n)
                        {
                                if (memo[x + 1][y][0] == -1) memo[x + 1][y][0] = (int)rec(x + 1, y, 0);
                                if (memo[x + 1][y][1] == -1) memo[x + 1][y][1] = (int)rec(x + 1, y, 1);

                        }
                        if (x - 1 >= 0)
                        {
                                if (memo[x - 1][y][0] == -1) memo[x - 1][y][0] = (int)rec(x - 1, y, 0);
                                if (memo[x - 1][y][1] == -1) memo[x - 1][y][1] = (int)rec(x - 1, y, 1);

                        }
                        if (y + 1 < m)
                        {
                                if (memo[x][y + 1][0] == -1) memo[x][y + 1][0] = (int)rec(x, y + 1, 0);
                                if (memo[x][y + 1][1] == -1) memo[x][y + 1][1] = (int)rec(x, y + 1, 1);

                        }
                        if (y - 1 >= 0)
                        {
                                if (memo[x][y - 1][0] == -1) memo[x][y - 1][0] = (int)rec(x, y - 1, 0);
                                if (memo[x][y - 1][1] == -1) memo[x][y - 1][1] = (int)rec(x, y - 1, 1);

                        }
                        memo[x][y][tt] = 1;
                        if (x + 1 < n and ((rec(x + 1, y, tt ^ 1)) or (rec(x + 1, y, tt)))) return (bool)true;
                        if (x - 1 >= 0 and ((rec(x - 1, y, tt ^ 1)) or (rec(x - 1, y, tt)))) return (bool)true;
                        if (y + 1 < m and ((rec(x, y + 1, tt ^ 1)) or (rec(x, y + 1, tt)))) return (bool)true;
                        if (y - 1 >= 0 and ((rec(x, y - 1, tt ^ 1)) or (rec(x, y - 1, tt)))) return (bool)true;
                        memo[x][y][tt] = 0;
                        return false;
                }
                else
                {
                        if (x + 1 < n)
                        {
                                if (memo[x + 1][y][tt] == -1) memo[x + 1][y][tt] = (int)rec(x + 1, y, tt);
                        }
                        if (x - 1 >= 0)
                        {
                                if (memo[x - 1][y][tt] == -1) memo[x - 1][y][tt] = (int)rec(x - 1, y, tt);

                        }
                        if (y + 1 < m)
                        {
                                if (memo[x][y + 1][tt] == -1) memo[x][y + 1][tt] = (int)rec(x, y + 1, tt);

                        }
                        if (y - 1 >= 0)
                        {
                                if (memo[x][y - 1][tt] == -1) memo[x][y - 1][tt] = (int)rec(x, y - 1, tt);

                        }
                        memo[x][y][tt] = 1;
                        if (x + 1 < n and ((rec(x + 1, y, tt))))
                        {

                                gimme(x, y, tt);
                            return (bool)true;
                        }
                        if (x - 1 >= 0 and ((rec(x - 1, y, tt))))
                        {

                                return (bool)true;
                        }
                        if (y + 1 < m and ((rec(x, y + 1, tt))))
                        {
                                return (bool)true;
                        }
                        if (y - 1 >= 0 and ((rec(x, y - 1, tt))))
                        {
                                return (bool)true;
                        }
                        memo[x][y][tt] = 0;
                        return false;
                }
                memo[x][y][tt] = 0;
                return false;
        };
        // sort(all(a), [&](auto data1, auto data2)
        // {
                // return make_pair(data1.x, data1.y) < make_pair(data2.x, data2.y);
        // });

        while (q--)
        {

                int l, r; cin >> l >> r;
                int en1, en2; cin >> en1 >> en2;
                for (int i = 0; i < 201; ++i) 
                {
                        for (int j = 0; j < 201; ++j) 
                        {
                                for (int k = 0; k < n; ++k) 
                                {
                                        vis[i][j][k] = 0;
                                }
                        }       
                }
                for (int i = 0; i < 201; ++i) 
                {
                        for (int j = 0; j < 201; ++j) 
                        {
                                for (int k = 0; k < n; ++k) 
                                {
                                        memo[i][j][k] = -1;
                                }
                        }       
                }
                bool ans = rec(l, r, 1);
                yes(ans);
        }
}
 
 
 
Spooder main()
{
        Code_By_Faraz;
        #ifdef LOCAL
            freopen("input.txt", "r", stdin);
            freopen("output.txt", "w", stdout); 
        #endif
        cout << fixed << setprecision(10);
        int Test = 1;
        cin >> Test;  
        while (Test--)
        {
                Faraz();
        }
        return 0;
}
