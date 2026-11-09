#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll T;
	cin>>T;
	string j1="write_me",j2="what_is",j3="solve";
	string w1="make_it_sound_human",w2="do_not_hallucinate",w3="make_no_mistakes",w4="thank_you";
	while(T--){
		string s;
		cin>>s;
		ll ans=0;
		for(ll i=0;i<s.size();i++){
			ll jl=0;
			for(ll j=i;j<i+j1.size()&&j<s.size();j++){
				if(j1[j-i]!=s[j]){
					jl=-1;
					break;
				}
				jl++;
			}
			if(jl==j1.size()){
				ans=1;
				break;
			}
			jl=0;
			for(ll j=i;j<i+j2.size()&&j<s.size();j++){
				if(j2[j-i]!=s[j]){
					jl=-1;
					break;
				}
				jl++;
			}
			if(jl==j2.size()){
				ans=2;
				break;
			}
			jl=0;
			for(ll j=i;j<i+j3.size()&&j<s.size();j++){
				if(j3[j-i]!=s[j]){
					jl=-1;
					break;
				}
				jl++;
			}
			if(jl==j3.size()){
				ans=3;
				break;
			}
		}
		cout<<s;
		if(ans==1)cout<<w1<<endl;
		else if(ans==2)cout<<w2<<endl;
		else if(ans==3)cout<<w3<<endl;
		else cout<<w4<<endl;
	}
	return 0;
}
