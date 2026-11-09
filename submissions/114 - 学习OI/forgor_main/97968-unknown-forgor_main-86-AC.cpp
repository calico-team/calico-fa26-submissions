#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef pair<ll,ll> pii;
ll fa[1000005];
vector<ll> e[1000005];
void dfs(ll x,ll faa)
{
	fa[x]=faa;
	for(ll nd:e[x])
		if(nd!=faa) dfs(nd,x);
}
vector<ll> solve_phase1(ll n,vector<pii>& E)
{
	for(pii x:E)
	{
		e[x.first].push_back(x.second);
		e[x.second].push_back(x.first);
	}
	dfs(1,0);
	vector<ll> res;
	for(int i=1;i<=n;i++)
	{
		if(i==1) res.push_back(fa[2]);
		else if(i==n) res.push_back(fa[n]);
		else res.push_back(fa[i]^fa[i+1]);
	}
	return res;
}
vector<pii> solve_phase2(ll n,vector<ll>& A)
{
	ll pos=0;
	for(int i=0;i<n;i++)
		if(A[i]==-1) pos=i;
	for(int i=1;i<pos;i++) A[i]^=A[i-1];
	for(int i=n-2;i>pos;i--) A[i]^=A[i+1];
	vector<pii> res;
	for(int i=0;i<pos;i++) res.push_back({A[i],i+2});
	for(int i=n-1;i>pos;i--) res.push_back({A[i],i+1});
	return res;
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
	return 0;
}
