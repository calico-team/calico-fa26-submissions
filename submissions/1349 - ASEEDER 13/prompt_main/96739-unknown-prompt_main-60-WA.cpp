#include<bits/stdc++.h>
#include<string>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t;
	
	cin>>t;
	
	for(int i=0;i<t;i++)
	  {
	    string s;
	    string a="make_it_sound_human",b="do_not_hallucinate",c="make_no_mistakes",d="thank_you";
	    //string x="write_me",y="write_me",z="make_no_mistakes";
	    
	    
	  	getline(cin,s);
		
		char m=s.find('write_me'),n=s.find('what_is'),o=s.find('make_no_mistakes');
	  	
	  	if(m == 'write_me')
	  	  {
	  	  	s+=a;cout<<s<<endl;
			}
		if(n == 'what_is')
	  	  {
	  	  	s+=b;cout<<s<<endl;
			}
		if(o == 'make_no_mistakes')
	  	  {
	  	  	s+=c;cout<<s<<endl;
			}
		if(m != 'write_me' && n != 'what_is' && o != 'make_no_mistakes')
	  	  {
	  	  	s+=d;cout<<s<<endl;
			}
		//cout<<s<<endl;
	  }
	return 0;
}
