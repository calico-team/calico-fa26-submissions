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
	    string x="write_me",y="write_me",z="make_no_mistakes";
	    
	    
	  	cin>>s;
		
		//char m=s.find('write_me'),n=s.find('what_is'),o=s.find('make_no_mistakes');
	  	
	  	if(s.find(x)!=0)
	  	  {
	  	  	s+=a;
			}
		else{
		
		  if(s.find(y)!=0)
	  	    {
	  	  	  s+=b;
			}
		  else{
		  	if(s.find(z)!=0)
	  	      {
	  	  	    s+=c;
			  }
		    else{
		    	if(s.find(x)== 0 && s.find(y)== 0 && s.find(z)== 0 )
	  	          {
	  	  	        s+=d;
			      }
			}
		  }
		}
		
		
		cout<<s<<endl;
	  }
	return 0;
}
