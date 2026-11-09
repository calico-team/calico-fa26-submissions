#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 7;

int t, n, m;
int a[N], dp[N][2]; // dp[index][what is the thing used by i - 1] = maximum health of the other one

void solve(){

    cin >> n >> m;
    for(int i = 1; i <= n; i ++)
        cin >> a[i];
    bool OK = 0;
    dp[1][0] = dp[1][1] = m; // 0: smoke 1, 1: smoke 2
    for(int i = 2; i <= n; i ++){
        dp[i][0] = dp[i][1] = -1;
        if(a[i] - a[i - 1] >= m) dp[i][0] = max(dp[i][0], min(m, dp[i - 1][0] + a[i] - a[i - 1] - m)); // use smoke 1 at (i - 1) and (i)
        if(dp[i - 1][1] + a[i] - a[i - 1] >= m) dp[i][0] = max(dp[i][0], min(m, a[i] - a[i - 1] - (m - dp[i - 1][1]))); // use smoke 2 at (i - 1), smoke 1 at (i)
        if(a[i] - a[i - 1] - (m - dp[i - 1][1]) >= m) dp[i][1] = max(dp[i][1], m); // use smoke 2 at (i - 1) and (i)
        if(dp[i - 1][0] == m) dp[i][1] = max(dp[i][1], min(m, a[i] - a[i - 1] - m)); // use smoke 1 at (i - 1), smoke 2 at (i)
        else if(a[i] - a[i - 1] - m >= m - dp[i - 1][0]) dp[i][1] = max(dp[i][1], m);
        if(dp[i][0] < 0 && dp[i][1] < 0) OK = 1;
    }
    if(OK) cout << "NO\n";
    else cout << "YES\n";

}

int main(){

    cin >> t;
    while(t --) solve();

    return 0;
}
