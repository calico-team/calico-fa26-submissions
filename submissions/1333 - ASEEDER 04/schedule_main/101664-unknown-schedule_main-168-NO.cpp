#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/** 
 * Return the maximum number of classes that can be taken across M semesters.
 *    
 * N: the number of classes
 * M: the number of semesters
 * K: the maximum number of classes you can take per semester
 * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
 */
int solve(int N, int M, int K, vector<int> &P)
{
    vector<vector<int>> g(N + 1);
    vector<int> d(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        if (P[i] != 0)
        {
            g[P[i]].push_back(i + 1);
            d[i + 1]++;
        }
    }
    queue<int> q;
    for (int i = 1; i <= N; i++)
    {
        if (d[i] == 0) q.push(i);
    }
    int ans = 0;
    for (int i = 0; i < M; i++)
    {
        if (q.empty()) break;
        int sz = q.size();
        int cnt = min(sz, K);
        ans += cnt;
        vector<int> nxt;
        for (int j = 0; j < cnt; j++)
        {
            int u = q.front();
            q.pop();
            for (int v : g[u])
            {
                d[v]--;
                if (d[v] == 0) nxt.push_back(v);
            }
        }
        for (int j = cnt; j < sz; j++)
        {
            nxt.push_back(q.front());
            q.pop();
        }
        for (int v : nxt) q.push(v);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--)
	{
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        solve(N, M, K, P);
    }
}

