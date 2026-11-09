#include<bits/stdc++.h>
using namespace std;
int T,N,M,Q;
vector<int> p;
int id(int mode,int r,int c){
	return mode*N*M+r*M+c;
}
int find(int x){
	if(p[x]==x) return x;
	return p[x]=find(p[x]);
}
void uni(int a,int b){
	a=find(a);
	b=find(b);
	if(a!=b) p[b]=a;
}
bool ok(char ch,int mode){
	if(ch=='.') return true;
	if(ch=='B') return mode==0;
	if(ch=='R') return mode==1;
	return false;
}
int main(){
	cin>>T;
	while(T--){
		cin>>N>>M>>Q;
		vector<string> g(N);
		for(int i=0;i<N;i++) cin>>g[i];
		int tot=2*N*M;
		p.resize(tot);
		for(int i=0;i<tot;i++) p[i]=i;
		for(int r=0;r<N;r++){
			for(int c=0;c<M;c++){
				if(g[r][c]=='.'){
					uni(id(0,r,c),id(1,r,c));
				}
				for(int mode=0;mode<2;mode++){
					if(!ok(g[r][c],mode)) continue;
					if(r+1<N&&ok(g[r+1][c],mode)){
						uni(id(mode,r,c),id(mode,r+1,c));
					}
					if(c+1<M&&ok(g[r][c+1],mode)){
						uni(id(mode,r,c),id(mode,r,c+1));
					}
				}
			}
		}
		while(Q--){
			int sr,sc,er,ec;
			cin>>sr>>sc>>er>>ec;
			int s=find(id(0,sr,sc));
			int e;
			char ch=g[er][ec];
			if(ch=='R'){
				e=find(id(1,er,ec));
			}
			else{
				e=find(id(0,er,ec));
			}
			cout<<(s==e?"YES":"NO")<<"\n";
		}
	}
	return 0;
}

