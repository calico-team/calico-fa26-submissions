#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int main(){
	int s;
	cin>>s;
	for(int i=1;i<=s;i++){
		char a[105]={};
		int tf=0;
		cin>>a;
		for(int c=0;c<105;c++){
			if(a[c]=='w' &&  a[c+1]=='r' && a[c+2]=='i' && a[c+3]=='t' && a[c+4]=='e' && a[c+5]=='_' && a[c+6]=='m' && a[c+7]=='e'){
				cout<<a<<"make_it_sound_human"<<endl;
				tf=1;
			}if(a[c]=='w' &&  a[c+1]=='h' && a[c+2]=='a' && a[c+3]=='t' && a[c+4]=='_' && a[c+5]=='i' && a[c+6]=='s'){
				cout<<a<<"do_not_hallucinate"<<endl;
				tf=1;
			}if(a[c]=='s' &&  a[c+1]=='o' && a[c+2]=='l' && a[c+3]=='v' && a[c+4]=='e'){
				cout<<a<<"make_no_mistakes"<<endl;
				tf=1;
			} 
		}
		if(tf==0){
			cout<<a<<"thank_you"<<endl;
		}
	}
	return 0;
}

