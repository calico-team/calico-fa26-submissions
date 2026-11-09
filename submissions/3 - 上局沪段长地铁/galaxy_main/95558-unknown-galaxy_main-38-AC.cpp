#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,qe,jl[201][201],vis[201][201][3];
ll mx[4]={0,1,0,-1},my[4]={1,0,-1,0};
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	ll t;
	cin>>t;
	while(t--){
		cin>>n>>m>>qe;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				char c;
				cin>>c;
				if(c=='R')jl[i][j]=1;
				else if(c=='B')jl[i][j]=2;
				else jl[i][j]=0;
				vis[i][j][1]=vis[i][j][2]=vis[i][j][0]=0;
			}
		}
		queue<int>qi,qj,qz;
		qi.push(n);qj.push(m);qz.push(jl[n][m]);
		while(!qi.empty()){
			ll ji=qi.front(),jj=qj.front(),jz=qz.front();
			qi.pop();qj.pop();qz.pop();
			if(vis[ji][jj][jz])continue;
			vis[ji][jj][jz]=1;
			if(jl[ji][jj]==0)vis[ji][jj][1]=vis[ji][jj][2]=1;
			for(int i=0;i<4;i++){
				ll ci=ji+mx[i],cj=jj+my[i];
				if(ci<1||ci>n||cj<1||cj>m)continue;
				if(jl[ci][cj]==0){
					qi.push(ci);qj.push(cj);qz.push(0);
				}
				else if(jl[ji][jj]==0){
					qi.push(ci);qj.push(cj);qz.push(jl[ci][cj]);
				}
				else if(jl[ji][jj]==jl[ci][cj]){
					qi.push(ci);qj.push(cj);qz.push(jl[ji][jj]);
				}
			}
		}
		while(qe--){
			ll x,y,jx,jy;
			cin>>x>>y>>jx>>jy;
			x++;y++;jx++;jy++;
			if(vis[x][y][1]||vis[x][y][2]){
				cout<<"YES"<<endl;
			}
			else{
				cout<<"NO"<<endl;
			}
		}
	} 
	return 0;
} 
