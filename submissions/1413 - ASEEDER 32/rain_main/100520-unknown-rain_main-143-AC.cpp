#include<bits/stdc++.h>
using namespace std;
int T,n;
long long K;
struct node{
	int x,y,z;
	char d;
};
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>K;
		vector<node> a(n);
		map<int, vector<int> > mp;
		for(int i=0;i<n;i++){
			cin>>a[i].x>>a[i].y>>a[i].z>>a[i].d;
			if(a[i].d=='N'){
				mp[a[i].x+a[i].y].push_back(a[i].x);
			}
		}
		map<int, vector<int> >::iterator it;
		for(it=mp.begin();it!=mp.end();it++){
			sort(it->second.begin(),it->second.end());
		}
		long long cnt=0;
		for(int i=0;i<n;i++){
			if(a[i].d=='E'){
				int s=a[i].x+a[i].y;
				if(mp.find(s)==mp.end()) continue;
				vector<int> &v=mp[s];
				long long L=a[i].x;
				long long R=(long long)a[i].x+K-1;
				int l=lower_bound(v.begin(),v.end(),(int)L)-v.begin();
				int r=upper_bound(v.begin(),v.end(),(int)R)-v.begin();
				cnt+=(long long)(r-l);
			}
		}
		cout<<(long long)n*K-cnt<<endl;
	}
	return 0;
}
/* 
3
3 3
030E
211N
882E
4 2
050E
501N
132E
313N
5 5
060E
241E
422N
513N
994N
*/ 
