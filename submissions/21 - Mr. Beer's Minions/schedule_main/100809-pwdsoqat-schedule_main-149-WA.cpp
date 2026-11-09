#include <bits/stdc++.h>
using namespace std;

/** 
 * Return the maximum number of classes that can be taken across M semesters.
 *    
 * N: the number of classes
 * M: the number of semesters
 * K: the maximum number of classes you can take per semester
 * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
 */
template <typename T> void print(const T& container) {
    for (const auto& item : container) {
        cout << item << " ";
    }
    cout << endl;
}
vector<vector<int>> children;
vector<int> cur,nxt;
vector<int> dp;
priority_queue<pair<int,int>> greed;

void dfs(int x, vector<int> &p){
    while (x != 0){
        x = p[x-1];
        dp[x]++;
        //cout << x << endl;
    }
}
int solve(int n, int m, int k, vector<int> &p){
    children = vector<vector<int>>(n+1);
    dp = vector<int>(n+1);
    cur.clear();
    nxt.clear();
    while (!greed.empty()){
        greed.pop();
    }
    for (int i = 1; i <= n; i++){
        children[p[i-1]].push_back(i);
    }
    // get children array
    nxt.push_back(0);
    for (int i = 0; i < m; i++){
        swap(cur,nxt);
        nxt.clear();
        for (int c:cur){
            for (int d:children[c]){
                nxt.push_back(d);
            }
        }
    }
    for (int c:nxt){
        dfs(c,p);
    }
    //print(dp);
    greed.push({dp[0],0});
    int ans = 0;
    vector<pair<int,int>> unlock;
    for (int i = 0; i <= m; i++){
        int lf = k;
        while (!greed.empty() and lf > 0){
            ans++;
            lf--;
            int pr = greed.top().second;
            greed.pop();
            for (int c:children[pr]){
                unlock.push_back({dp[c],c});
            }
        }
        for (pair<int,int> c:unlock){
            greed.push(c);
        }
        unlock.clear();
    }
    return ans-1;
}

int main(){
    //freopen("00_main.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--){
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        cout << solve(N, M, K, P) << endl;
    }
}