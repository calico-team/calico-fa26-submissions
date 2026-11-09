#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second

using namespace std;

/**
 * Output a list N integers A_1 .. A_N
 *
 * N: the number of vertices
 * E: the N - 1 edges of the tree as (u, v) pairs
 */
vector<int> solve_phase1(int n, vector<pair<int, int>>& e) {
	for(int i=0;i<n-1;i++) e[i].f--, e[i].s--;
    vector<vector<int>> a(n); for(int i=0;i<n-1;i++) a[e[i].f].pb(e[i].s), a[e[i].s].pb(e[i].f);
    vector<int> b(n); for(int i=0;i<n;i++) b[i] = a[i].size();
    priority_queue<int> q; for(int i=0;i<n;i++) if(b[i] == 1) q.push(-i);
    vector<int> c(n,1); vector<bool> d(n,1); long long whatamievendoing = 0;
    for(int i=0;i<n-2;i++) {
    	int x = -q.top(); q.pop(); 
    	for(auto j:a[x]) if(d[j]) c[i] = j, b[j]--, whatamievendoing += j;
    	d[x] = 0;
    }
	c[n-2] = whatamievendoing/1000000, c[n-1] = whatamievendoing%1000000;
	return c;
}

/**
 * The N - 1 edges of the original tree as (u, v) pairs
 *
 * N: the number of vertices
 * A: the N integers A_1 .. A_N with one value replaced with -1
 */
vector<pair<int, int>> solve_phase2(int n, vector<int>& a) {
	if(a[n-1] != -1 && a[n-2] != -1) {
		int y = 0; long long x = a[n-2]*1000000+a[n-1];
		for(int i=0;i<n-2;i++) {if(a[i] == -1) y = i; else x -= a[i];}
		a[y] = x;
	}
	map<int,int> m; for(int i=0;i<n-2;i++) m[a[i]]++; // maimai
	priority_queue<int> q; for(int i=0;i<n;i++) if(m[i] == 0) q.push(-i);
	vector<pair<int,int>> v(n-1);
	for(int i=0;i<n-2;i++) {v[i].f = -q.top(), v[i].s = a[i], m[a[i]]--; q.pop(); if(!m[a[i]]) q.push(-a[i]);}
	v[n-2].f = -q.top(); q.pop(); v[n-2].s = -q.top();
	return v;
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
            cout << e.first+1 << ' ' << e.second+1 << '\n';
        }
    }
}
