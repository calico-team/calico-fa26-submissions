#include<bits/stdc++.h>
using namespace std;
int T;
string s,a,b,c;
int main()
{
	a="write_me";
	b="what_is";
	c="solve";
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		int cnt=0;
		cin>>s;
		int indexa = s.find(a);
		if(indexa != string::npos){
		  s+="make_it_sound_human";
		  cnt=1;
		}
		int indexb = s.find(b);
		if(indexb != string::npos){
		s+="do_not_hallucinate";
		cnt=1;
		}
		int indexc = s.find(c);
		if(indexc != string::npos) {
		s+="make_no_mistakes";
		cnt=1;	
		}
		if(cnt==0)
		{
			s+="thank_you";
		}
		cout<<s<<endl;
		
		
	}
	
	
	
	
	
	
	
	
	return 0;	
} 
