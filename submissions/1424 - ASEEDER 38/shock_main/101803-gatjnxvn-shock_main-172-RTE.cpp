#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,p[1000005],r[1000005],c[1000005];
int flag=0;

void setsize(vector<int> &v,int k){
	v.clear();
	for (int i=0;i<=k;i++)v.push_back(0);
}
vector<int> a[1005],f[1005];
int find(int i,int j){
	if (f[i][j]==j)return j;
	else return f[i][j]=find(i,f[i][j]);
}
void solve(){
	cin>>n>>m>>q;
	//if (n>m)swap(n,m),flag=1;
	for (int i=1;i<=n;i++){
		setsize(a[i],m);
		setsize(f[i],m+1);
		for (int j=1;j<=m+1;j++)f[i][j]=j;
	}
	for (int i=1;i<=q;i++){
		cin>>r[i]>>c[i]>>p[i];
		r[i]++,c[i]++;
		if (flag)swap(r[i],c[i]);
	}
	for (int i=q;i>=1;i--){
		for (int j=1;j<=n;j++){
			if (p[i]*p[i]-(r[i]-j)*(r[i]-j)<0)continue;
			int temp=sqrt(p[i]*p[i]-(r[i]-j)*(r[i]-j));
			int L=c[i]-temp,R=c[i]+temp;
			L=max(1LL,L);R=min(m,R);
			int now=find(j,L);
			while (now<=R){
				a[j][now]=p[i]*p[i]-(r[i]-j)*(r[i]-j)-(c[i]-now)*(c[i]-now)+1;
				now=f[j][now]=find(j,now+1);
			}
		}
	}
	if (flag==0){
		for (int i=1;i<=n;i++){
	    	for (int j=1;j<=m;j++){
	    		cout<<a[i][j]<<" ";
	    	}
	    	cout<<"\n";
    	}
	}
	else{
		for (int i=1;i<=m;i++){
			for (int j=1;j<=n;j++){
				cout<<a[j][i]<<" ";
			}
			cout<<"\n";
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t=1;cin>>t;
	while (t--)solve();
}
