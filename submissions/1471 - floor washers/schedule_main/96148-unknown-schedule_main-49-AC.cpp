#include <bits/stdc++.h>
using namespace std;

int t;
int N,M,K;
int parent[10100];
vector<int> children[10100];
int d[10100];
int md[10100];

int dfs(int i, int de){
	d[i] = de;
	int num = de;
	for(int j : children[i]){
		num = max(num,dfs(j,de + 1));
	}
	md[i] = num - de;
	
	return num;
}

int main(){
	
	scanf(" %d",&t);
	
	while(t--){
		
		scanf(" %d",&N);
		scanf(" %d",&M);
		scanf(" %d",&K);
		
		children[0].clear();
		for(int i = 1; i <= N; i++){
			children[i].clear();
			parent[i] = -1;
			d[i] = -1;
			md[i] = 0;
 		}
 		d[0] = 0;
		
		for(int i = 1; i <= N; i++){
			scanf(" %d",&parent[i]);
			children[parent[i]].push_back(i);
		}
		
		int a = dfs(0,0);
		
		priority_queue<pair<int,int>> q;
		
		for(int i = 1; i <= N; i++){
			if(parent[i] == 0) q.push({md[i],i});
		}
		
		int cont = 0;
		
		for(int i = 0; i < M; i++){
			vector<pair<int,int>> add;
			
			for(int _ = 0; _ < K; _++){
				if(q.empty()) break;
				cont++;
				pair<int,int> ii = q.top();
				q.pop();
				
				for(int i : children[ii.second]) add.push_back({md[i],i});
			}
			
			for(pair<int,int> ii : add) q.push(ii);
			if(q.empty()) break;
		}
		
		printf("%d\n",cont);
	}
	
}
