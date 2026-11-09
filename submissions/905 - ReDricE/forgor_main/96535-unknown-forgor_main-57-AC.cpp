#include <bits/stdc++.h>
using namespace std;

char s[11];
int n;
vector<int> vtx[200005];
int p[200005];

void dfs(int cur, int par = -1){
	for(auto nxt : vtx[cur]){
		if(nxt == par) continue;
		p[nxt] = cur;
		dfs(nxt, cur);
	}
}

void s1(){
	scanf("%d", &n);
	for(int i=1; i<n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		vtx[u].push_back(v);
		vtx[v].push_back(u);
	}
	dfs(1);
	p[1] = 0;
	for(int i=2; i<=n; i++){
		p[1] ^= p[i];
	}
	for(int i=1; i<=n; i++){
		printf("%d ", p[i]);
	}
}

int r[200005];

void s2(){
	scanf("%d", &n);
	int ptr = 0;
	for(int i=1; i<=n; i++){
		scanf("%d", &r[i]);
		if(r[i] == -1) ptr = i;
	}
	r[ptr] = 0;
	for(int i=1; i<=n; i++){
		if(i == ptr) continue;
		r[ptr] ^= r[i];
	}
	for(int i=2; i<=n; i++){
		printf("%d %d\n", i, r[i]);
	}
}

int main(){
	scanf(" %s", s);
	if(s[0] == 'F') s1();
	else s2();
}