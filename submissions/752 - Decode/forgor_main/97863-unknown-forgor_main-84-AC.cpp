#include <bits/stdc++.h>

using namespace std;

/**
 * Output a list N integers A_1 .. A_N
 *
 * N: the number of vertices
 * E: the N - 1 edges of the tree as (u, v) pairs
 */
vector<int> solve_phase1(int N, vector<pair<int, int>>& E) {
	
	vector<int> parent(N + 1, -1);

	parent[1] = -1;

	vector<vector<int>> adj(N + 1);

	for(pair<int, int> p : E)
	{
		adj[p.first].push_back(p.second);
		adj[p.second].push_back(p.first);
	}

	queue<int> q;

	q.push(1);

	while(!q.empty())
	{
		int cur = q.front();
		q.pop();

		for(int i : adj[cur])
		{
			if(parent[cur] == i)
				continue;

			parent[i] = cur;
			q.push(i);
		}
	}

	vector<int> packed(N);

	int checksum = 0;

	for(int i = 2; i <= N; i++)
		checksum ^= parent[i];
	
	packed[0] = checksum;

	for(int i = 1; i < N; i++)
		packed[i] = parent[i+1];
	
	return packed;
}

/**
 * The N - 1 edges of the original tree as (u, v) pairs
 *
 * N: the number of vertices
 * A: the N integers A_1 .. A_N with one value replaced with -1
 */
vector<pair<int, int>> solve_phase2(int N, vector<int>& A) {
	vector<pair<int, int>> edges;

	int checksum = A[0];
	int reconval = 0;

	int missing = 0;

	for(int i = 1; i < N; i++)
	{
		if(A[i] == -1)
			missing = i;
		else
			reconval ^= A[i];
	}

	if(missing != 0)
	{
		int corrected = checksum ^ reconval;

		A[missing] = corrected;
	}

	for(int i = 1; i < N; i++)
	{
		edges.push_back({A[i], i + 1});
	}

	return edges;
}

int main() {
    string phase;
    cin >> phase;
    int N;
    cin >> N;

    if (phase == "FIRST") {
        vector<pair<int, int>> E(N - 1);
        for (int i = 0; i < N - 1; i++) {
            cin >> E[i].first >> E[i].second;
        }
        vector<int> A = solve_phase1(N, E);
        for (int i = 0; i < N; i++) {
            if (i > 0) cout << ' ';
            cout << A[i];
        }
        cout << '\n';
    } else {
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        vector<pair<int, int>> edges = solve_phase2(N, A);
        for (auto& e : edges) {
            cout << e.first << ' ' << e.second << '\n';
        }
    }
}
