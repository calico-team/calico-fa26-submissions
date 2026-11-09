#include <bits/stdc++.h>
using namespace std;
#define int long long
bool cmp(pair<int,int> a, pair<int,int> b){
	if(a.first+a.second==b.first+b.second) return a.first<b.first;
	return a.first+a.second < b.first+b.second;
}
bool eq(pair<int,int> a, pair<int,int> b){
	return a.first+a.second == b.first+b.second;
}
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
		int n,m;
		cin >> n >> m;
		long long ans=(long long)n*m;
		vector<pair<int,int> > arr[2];
		for(int i=0; i<n; i++){
			int x,y,z;
			char d;
			cin >> x >> y >> z >> d;
			if(d=='N') arr[0].push_back({x,y});
			else arr[1].push_back({x,y});
		}
		sort(arr[0].begin(),arr[0].end(),cmp);
		sort(arr[1].begin(),arr[1].end(),cmp);
		int p1=0,p2=0;
		while(p1<(int)arr[0].size()&&p2<(int)arr[1].size()){
			if(arr[0][p1].first==-1) p1++;
			else if(arr[1][p2].first==-1) p2++;
			else if(arr[0][p1].first+arr[0][p1].second<arr[1][p2].first+arr[1][p2].second){
				p1++;
			}
			else if(arr[0][p1].first+arr[0][p1].second>arr[1][p2].first+arr[1][p2].second){
				p2++;
			}
			else{
				int c1=p2,c2=p2-1,c3=p1;
				while(c3<(int)arr[0].size()&&eq(arr[0][p1],arr[0][c3])){
					while(c2+1<(int)arr[1].size()&&eq(arr[1][c2+1],arr[0][c3])&&arr[1][c2+1].first<=arr[0][c3].first){
						c2++;
					}
					while(c1<=c2&&arr[1][c1].first<=arr[0][c3].first-m){
						c1++;
					}
					ans-=c2-c1+1;
					//cout << c3 << ' ' << c1 << ':' << c2 << '\n';
					c3++;
				}
				p1=c3;
				p2=max(p2,c2);
			}
		}
		cout << ans << '\n';
	}
}
