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
        int n, k; cin >> n >> k;
        vl a(n);
        for (auto &x : a) cin >> x;

        int timer1 = INF;
        int timer2 = INF;
        int cnt1 = 0;
        int cnt2 = 1;

        timer1 = a[0] + k;
        for (int i = 1; i < n; ++i) 
        {
                if (a[i] >= timer1)
                {
                        cnt1 = 1;
                        timer1 = INF;
                }
                if (a[i] >= timer2)
                {
                        cnt2 = 1;
                        timer2 = INF;
                }
                if (cnt1 == 0 and cnt2 == 0)
                {
                        yes(0);
                        return;
                }
                if (cnt1)
                {
                        cnt1--;
                        if (timer2 != INF) timer1 = timer2 + k;
                        else timer1 = a[i] + k;
                        continue;
                }
                cnt2--;
                if (timer1 != INF) timer2 = timer1 + k;
                else timer2 = a[i] + k;
        }
        yes(1);


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
