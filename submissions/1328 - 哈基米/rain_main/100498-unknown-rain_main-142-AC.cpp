#include <bits/stdc++.h>
using namespace std;
int N,K; 
struct node{
	int x,y,z;
	char d;
};
long long solve(int N,int K,vector<node>sh){
	long long mjg,kb;
    long long answer = 1ll*N*K;
    vector<vector<int> >diags(2e5);
    vector<bool>flags;
    for(int i=0;i<N;i++){
    	diags[sh[i].x+sh[i].y].push_back(i);
	}
    long long blocked = 0;
	for(int i=0;i<N;i++){
		for(int j:diags[sh[i].x+sh[i].y]){
			if(sh[i].d=='E'&&sh[j].d=='N'){
				if(sh[j].x-sh[i].x==sh[i].y-sh[j].y){
					long long diff = sh[j].x-sh[i].x;
					if(diff<K&&diff>=0&&sh[i].z!=sh[j].z){
						blocked++;
					}
				}
			}
			if(sh[i].d=='N'&&sh[j].d=='E'){
				if(sh[i].x-sh[j].x==sh[j].y-sh[i].y){
					long long diff=sh[i].x-sh[j].x;
					if(diff<K&&diff>=0&&sh[i].z!=sh[j].z){
						blocked++;
						mjg++;
					}
				}
			}
			if(mjg==1)kb=1;
		}
		mjg=0;
	}
    return answer-blocked/2;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while (t--){
        cin>>N>>K;
        vector<node> L;
        for (int i = 0; i < N; i++){
            int X, Y, Z;
            char D;
            cin>>X>>Y>>Z>>D;
            L.push_back({X,Y,Z,D});
        }
        cout<<solve(N, K, L)<<endl;
    }
}

