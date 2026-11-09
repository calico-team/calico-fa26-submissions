#include <bits/stdc++.h>
using namespace std;

int t;
int N,M,Q;
int P[20100];
int X[20100];
int Y[20100];
bool flip = false;

int root(int i, int parent[]){
	if(parent[i] == i) return i;
	return parent[i] = root(parent[i],parent);
}


int main(){
	
	scanf(" %d",&t);
	
	while(t--){
		scanf(" %d",&N);
		scanf(" %d",&M);
		scanf(" %d",&Q);
		
		if(M > N){
			flip = true;
			swap(N,M);
		}
		else flip = false;
		
		for(int i = 0; i < Q; i++){
			scanf(" %lld",&X[i]);
			scanf(" %lld",&Y[i]);
			if(flip) swap(X[i],Y[i]);
			scanf(" %lld",&P[i]);
		}
	
		
		long long int label[N + 5][M + 5];
		
		for(int i = 0; i < N; i++){
			for(int j = 0; j < M; j++){
				label[i][j] = 0;
			}
		}
		
		for(int i = 0; i < M; i++){		
			int parent[N + 5];
			int rank[N + 5];
			int rs[N+5];
			int re[N+5];
			int done[N + 5];
			
			for(int i = 0; i < N; i++){
				parent[i] = i;
				rs[i] = i;
				re[i] = i;
				rank[i] = 0;
				done[i] = false;
			}
			
			for(int j = Q - 1; j >= 0; j--){
				if(abs(Y[j] - i) > P[j]) continue;
				int diff = (int)sqrt(P[j] * P[j] - (i - Y[j]) * (i - Y[j]) );
				if((diff + 1) * (diff + 1) + (i - Y[j]) * (i - Y[j]) <= P[j] * P[j]) diff++;
				
				pair<pair<int,int>,long long int> ii = {{X[j] - diff, X[j] + diff},P[j] * P[j] - (i - Y[j]) * (i - Y[j])};
				
				long long int mid = (ii.first.first + ii.first.second)/2;
				int r = ii.first.first;
				
				if(!done[r]){
					label[r][i] = ii.second -  (r - mid) * (r - mid) + 1;
					done[r] = true;
				}
				
				while(re[root(r,parent)] + 1 <= ii.first.second){
					int r1 = root(re[root(r,parent)] + 1,parent);
					//printf("%d ",r1);
					if(!done[r1]){
						label[r1][i] = ii.second -  (r1 - mid) * (r1 - mid) + 1;
						//printf("%d %d) ",ii.second, (r1 - mid) * (r1 - mid));
						done[r1] = true;
					}
					
					done[root(r1,parent)] = true;
					r = root(r,parent);
					r1 = root(r1,parent);
					if(rank[r1] > rank[r]) swap(r1,r);
					
					rank[r]++;
					parent[r1] = r;
					rs[r] = min(rs[r],rs[r1]);
					re[r] = max(re[r],re[r1]); 
				}
				//printf("\n");
			}
		}
		
		if(flip){
			for(int i = 0; i < M; i++){
				for(int j = 0; j < N; j++){
					printf("%lld ",label[j][i]);
				}
				printf("\n");
			}
		}
		else{
			for(int i = 0; i < N; i++){
				for(int j = 0; j < M; j++){
					printf("%lld ",label[i][j]);
				}
				printf("\n");
			}
			
			/*for(int i = 0; i < N; i++){
				printf("")
			}*/
		}
		printf("\n");
	}
		
}
