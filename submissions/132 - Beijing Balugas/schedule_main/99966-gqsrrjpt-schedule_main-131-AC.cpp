#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second  
#define int long long

vector<int> graph, depth;

void calc(int cur) {

    int val = cur;
    vector<int> used;
    while(depth[val] == -1) {

        used.push_back(val);
        val = graph[val];

    }

    for(int i = used.size() - 1; i >= 0; i--) {

        depth[used[i]] = depth[val] + used.size() - i;

    }

}

signed main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {

        int n, m, k;
        cin >> n >> m >> k;

        graph.clear();
        graph.resize(n);
        depth.clear();
        depth.resize(n, -1);
        for(int i = 0; i < n; i++) {

            cin >> graph[i];
            graph[i]--;

            if(graph[i] == -1) {

                depth[i] = 0;

            }

        }

        for(int i = 0; i < n; i++) {

            if(depth[i] == -1) {

                calc(i);

            }

        }

        vector<int> vals(1003);
        for(int i = 0; i < n; i++) {

            vals[depth[i]]++;

        }

        int l = 0, r = n;
        while(l < r) {

            int mid = (l + r + 1) / 2;
            vector<int> b(1003);

            int cur = mid;

            for(int i = 0; i < 1003; i++) {

                b[i] = min(vals[i], cur);
                cur -= vals[i];

                if(cur <= 0) {

                    break;

                }

            }

            bool works = true;
            cur = 0;
            for(int i = 1002; i >= 0; i--) {

                cur += b[i];
                if(m >= i && cur > (m - i) * k) {

                    works = false;
                    break;

                }

            }

            if(works) {

                l = mid;

            } else {

                r = mid - 1;

            }

        }

        cout << l << "\n";
        
    }

}