#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n;
string s;
void szzakioi()
{
	cin>>s;
	n=s.length();
	bool tg=false;
	for(int i=0;i+8<=n;i++)
	{
		if(tg) continue;
		if(s.substr(i,8)=="write_me")
		{
			s+="make_it_sound_human";
			tg=true;break;
		}
	}
	for(int i=0;i+7<=n;i++)
	{
		if(tg) continue;
		if(s.substr(i,7)=="what_is")
		{
			s+="do_not_hallucinate";
			tg=true;break;
		}
	}
	for(int i=0;i+5<=n;i++)
	{
		if(tg) continue;
		if(s.substr(i,5)=="solve")
		{
			s+="make_no_mistakes";
			tg=true;break;
		}
	}
	if(!tg) s+="thank_you";
	cout<<s<<endl;
}
int main()
{
	cin>>t;
	while(t--) szzakioi();
	return 0;
}
