#include<bits/stdc++.h>
const int N = 1e4 + 5;
using namespace std;
int T, n, m, k;
int fa[N];
vector<int> son[N];
deque<int> a;
vector<int> now;
int main(){
    // freopen("yyz.in", "r", stdin);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T--){
        a.clear();
        cin >> n >> m >> k;
        for(int i = 1; i <= n; ++i){
            son[i].clear();
        }
        for(int i = 1; i <= n; ++i){
            cin >> fa[i];
            if(fa[i] != 0) son[fa[i]].push_back(i);
        }
        if(m >= n){
            cout << n << endl;
            continue;
        }
        for(int i = 1; i <= n; ++i){
            if(fa[i] == 0){
                if(son[i].empty()) a.push_front(i);
                else a.push_back(i);
            }
        }
        int ans = 0;
        while(m-- && !a.empty()){
            now.clear();
            int cnt = 0;
            while(!a.empty() && cnt < k){
                ++ans;
                ++cnt;
                int u = a.back();
                a.pop_back();
                // cout << " " << u << endl;
                for(int v : son[u]){
                    now.push_back(v);
                }
            }
            for(int u : now){
                if(son[u].empty()) a.push_front(u);
                else a.push_back(u);
            }
        }
        cout << ans << endl;
    }
    return 0;
}/*
T6 Average Berkeley CS Major
easy
*/