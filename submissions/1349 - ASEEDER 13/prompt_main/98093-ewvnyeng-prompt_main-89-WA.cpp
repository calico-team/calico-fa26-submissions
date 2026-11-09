#include<bits/stdc++.h>
#include<string>
using namespace std;

int main()
{
	
	
	int t;
	
	cin>>t;
	
	for(int i=0;i<t;i++)
	  {
	    //ios::sync_with_stdio(false);
	    //cin.tie(nullptr);
	    
	    string s;
	    string x="write_me",y="what_is",z="solve";
	    
	  	cin>>s;
	  	
	  	if(s.find(x)!=0)
	  	  {
	  	  	s+="make_it_sound_human";
			}
		else{
		
		  if(s.find(y)!=0)
	  	    {
	  	  	  s+="do_not_hallucinate";
			}
		  else{
		  	if(s.find(z)!=0)
	  	      {
	  	  	    s+="make_no_mistakes";
			  }
		    else{
		    	if(s.find(x)== 0 && s.find(y)== 0 && s.find(z)== 0 )
	  	          {
	  	  	        s+="thank_you";
			      }
			}
		  }
		}
		
		
		cout<<s<<endl;
	  }
	return 0;
}
