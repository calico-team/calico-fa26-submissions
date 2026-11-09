#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int max_n = 1e4 + 2;
typedef long long ll;

int pre[max_n];
int deg[max_n];

int depth[max_n];
ll sum [max_n];

vector<int> children[max_n];

void dfs(int node, int d) {
    depth[node] = d;
    ll s = 1;
    for (int n : children[node]) {
        dfs(n, d+1);
        s += sum[n];
    }
    sum[node] = s;
}



class comp {
public:
	bool operator()(int a, int b) {
        // if (deg[a] == deg[b]) {
        //     return depth[a] > depth[b];
        // }
        // return deg[a] > deg[b];
        // if (depth[a] == depth[b]) {
        //     return deg[a] > deg[b];
        // }
        // return depth[a] > depth[b];
        //

        return sum[a] > sum[b]; 
        
	}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int tc = 0; tc < T; tc++) {
        int n, m, k;
        cin >> n >> m >> k;
        for (int i = 0; i < n; i++) {
            children[i] = vector<int>();
        }

        memset(deg, 0, sizeof deg);

        for (int i = 1; i <= n; i++) {
            cin >> pre[i];
            deg[pre[i]]++;
            children[pre[i]].push_back(i);
        }

        dfs(0, 0);


        priority_queue<int, vector<int>, comp> q;
        for (int mb : children[0]) {
            q.push(mb);
        }

        ll ans = 0;
        for (int i = 0; i < m; i++) {
            vector<int> to_add = vector<int>();
            for (int j = 0; j < k; j++) {
                if (q.size() == 0) {
                    break;
                }
                ans++;
                int top = q.top();
                q.pop();

                for (int mb : children[top]) {
                    to_add.push_back(mb);
                }
            } 
            for (int mb : to_add) {
                q.push(mb);
            }
        }

        cout << ans << endl;
    }




}
