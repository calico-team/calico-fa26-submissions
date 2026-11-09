#include<bits/stdc++.h>
using namespace std;
string str;
int n,flag=0;
int main()
{
	cin>>n;
	while(n--){
		cin>>str;
		for(int i=0;i<=str.size();i++) {
			if(str[i]=='w' && str[i+1]=='r' &&str[i+2]=='i' &&str[i+3]=='t' &&str[i+4]=='e' &&str[i+5]=='_' &&str[i+6]=='m' &&str[i+7]=='e'){
				cout<<str<<"make_it_sound_human"<<endl;
				flag=1;
			}
			else if(str[i]=='w' && str[i+1]=='h' &&str[i+2]=='a' &&str[i+3]=='t' &&str[i+4]=='_' &&str[i+5]=='i' &&str[i+6]=='s'){
				cout<<str<<"do_not_hallucinate"<<endl;
				flag=1;
			}
			else if (str[i]=='s' && str[i+1]=='o' &&str[i+2]=='l' &&str[i+3]=='v' &&str[i+4]=='e'){
				cout<<str<<"make_no_mistakes"<<endl;
				flag=1;
			}
		}
		if(flag==0) cout<<str<<"thank_you"<<endl; 
		flag=0;
		str={""};
	}
	
	return 0;
 } 
