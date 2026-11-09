#include<bits/stdc++.h>
#define randint rand()*rand()+rand()*rand()
#define lowbit(x) (x&(-x))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef __int128 i128;
typedef unsigned __int128 u128;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		string s;
		cin>>s;
		if(s.find("write_me")<s.size())
			cout<<s<<"make_it_sound_human\n";
		else if(s.find("what_is")<s.size())
			cout<<s<<"do_not_hallucinate\n";
		else if(s.find("solve")<s.size())
			cout<<s<<"make_no_mistakes\n";
		else cout<<s<<"thank_you\n";
	}
	return 0;
}

