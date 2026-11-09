#include<bits/stdc++.h>
//#define int long long
using namespace std;
int n,k,a[1000005];
bool match(string a,string b){
	int n=a.size(),m=b.size();
	for (int i=0;i+m-1<n;i++){
		int flag=1;
		for (int j=0;j<m;j++){
			if (a[i+j]!=b[j]){
				flag=0;break;
			}
		}
		if (flag)return 1;
	}
	return 0;
}
void solve(){
	string s;cin>>s;
	if (match(s,"write_me")){
		cout<<s<<"make_it_sound_human\n";
	}
	else if (match(s,"what_is")){
		cout<<s<<"do_not_hallucinate\n";
	}
	else if (match(s,"solve")){
		cout<<s<<"make_no_mistakes\n";
	}
	else{
		cout<<s<<"thank_you\n";
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin>>t;
	while (t--)solve();
} 
