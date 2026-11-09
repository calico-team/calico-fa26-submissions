#include<bits/stdc++.h>
using namespace std;
int t;
long long n,k,ne,nn,cnt[200005];
string ss;
struct node{
	int x,y,z;
} de[100005],dn[100005];
bool cmp(node u,node v){
	return u.x<v.x;
}
int main(){
	cin>>t;
	while(t--){
//		cout<<"T:"<<t<<endl;
		memset(cnt,0,sizeof(cnt));
		ne=0;nn=0;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>de[++ne].x>>de[ne].y>>de[ne].z>>ss;
			if(ss[0]=='N'){
				dn[++nn].x=de[ne].x;
				dn[nn].y=de[ne].y;
				dn[nn].z=de[ne].z;
				ne--;
			}
		}
//		cout<<"rrr"<<endl;
		sort(dn+1,dn+nn+1,cmp);
		sort(de+1,de+ne+1,cmp);
//		for(int i=1;i<=nn;i++) cout<<dn[i].x<<' '<<dn[i].y<<endl;
//		for(int i=1;i<=ne;i++) cout<<de[i].x<<' '<<de[i].y<<endl;
		long long ans=0;
		int l=1,r=0;
		for(int i=1;i<=nn;i++){
			while(r<ne&&de[r+1].x<dn[i].x){
				r++;
//				cout<<"add e "<<de[r].x<<' '<<de[r].y<<endl;
				cnt[de[r].x+de[r].y]++;
			}
			while(l<=r&&dn[i].x-de[l].x>k-1){
				cnt[de[l].x+de[l].y]--;
//				cout<<"del e "<<de[l].x<<' '<<de[l].y<<endl;
				l++;
			}
//			cout<<i<<": N "<<dn[i].x<<' '<<dn[i].y<<endl;
			ans+=cnt[dn[i].x+dn[i].y];
		}
		cout<<n*k-ans<<endl;
	}
	return 0;
}