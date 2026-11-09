#include<bits/stdc++.h>
//#define int long long
using namespace std;
int n,k;
struct node{
	int x,y,z;
	char d;
}a[1000005];
bool cmp(node a,node b){
	if (a.y+a.x==b.y+b.x){
		return a.x<b.x;
	}
	return a.y+a.x<b.y+b.x;
}
int m;
struct BIT{
	int c[1000005],n;
	void init(int N){
		n=N;
		for (int i=0;i<=n;i++)c[i]=0;
	}
	void add(int k,int x){
		for (int i=k;i<=n;i+=(i&-i))c[i]+=x;
	}
	int sum(int k){
		int ans=0;
		for (int i=k;i;i-=(i&-i))ans+=c[i];
		return ans;
	}
}A;
int cal(int l,int r){
	vector<int> v;
	for (int i=l;i<=r;i++){
		v.push_back(a[i].z);
    }
    sort(v.begin(),v.end());
    for (int i=l;i<=r;i++){
    	a[i].z=lower_bound(v.begin(),v.end(),a[i].z)-v.begin()+1;
    }
	int ans=(r-l+1)*k,j=l-1,cnt=0;
	for (int i=l;i<=r;i++){
		while (j<r&&a[j+1].x-a[i].x<k){
			++j;
			if (a[j].d=='N')cnt++;
	    }
	    if (a[i].d=='N')--cnt;
	    else ans-=cnt;
	}
	return ans;
}
void solve(){
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].z>>a[i].d; 
	}
	sort(a+1,a+1+n,cmp);
	int lst=1,ans=0;
	for (int i=2;i<=n;i++){
		if (a[i].y+a[i].x>a[i-1].y+a[i-1].x){
			ans+=cal(lst,i-1);
			lst=i;
		}
	}
	ans+=cal(lst,n);
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin>>t;
	while (t--)solve();
} 
