#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> child;
int dfscounter(int x, int last, int last2){
    int total = 0;
    for(int i = 0; i<child[x].size(); i++){
        total ++;
        total += dfscounter(child[x][i].second, x, i);
    }
    child[last][last2].first = total;
    return total;
}
void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    child = vector<vector<pair<int, int>>> (n+1);
    for(int i = 0; i<n; i++){
        int a;
        cin >> a;
        child[a].push_back({0, i});
    }
    dfscounter(0, 0, 0);
    for(vector<pair<int, int>> v: child){
        sort(v.begin(), v.end());
    }
    deque<int> dq;
    dq.push_back(0);
    int res = 0;
    while (m > 0){
        while(!dq.empty()){
            int x = dq.front();
            dq.pop_front();
            int left = k;
            for(pair<int, int> p: child[x]){
                if(left > 0) dq.push_back(p.second);
                left--;
                res ++;
            }
        }
        m--;
    }
    cout << res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}