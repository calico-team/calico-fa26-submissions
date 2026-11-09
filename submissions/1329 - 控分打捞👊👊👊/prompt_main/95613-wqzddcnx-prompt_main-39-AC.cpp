#include<bits/stdc++.h>
using namespace std;
int main(){
	int a;
	cin>>a;
	string k[a];
	for(int i=0;i<a;i++){
		cin>>k[i];
	}
	string t;
	bool b1=false,b2=false,b3=false;
	for(int i=0;i<a;i++){
		t=k[i];
		b1=false;
		b2=false;
		b3=false;
		for(int j=0;j<t.size();j++){
			if((j+7)<t.size() and t[j]=='w' and t[j+1]=='r' and t[j+2]=='i' and t[j+3]=='t' and t[j+4]=='e' and t[j+5]=='_' and t[j+6]=='m' and t[j+7]=='e'){
				b1=true;
			}else if((j+6)<t.size() and t[j]=='w' and t[j+1]=='h' and t[j+2]=='a' and t[j+3]=='t' and t[j+4]=='_' and t[j+5]=='i' and t[j+6]=='s'){
				b2=true;
			}else if((j+4)<t.size() and t[j]=='s' and t[j+1]=='o' and t[j+2]=='l' and t[j+3]=='v' and t[j+4]=='e'){
				b3=true;
			}
		}
		if(b1){
			cout<<t<<"make_it_sound_human"<<endl;
		}else if(b2){
			cout<<t<<"do_not_hallucinate"<<endl;
		}else if(b3){
			cout<<t<<"make_no_mistakes"<<endl;
		}else{
			cout<<t<<"thank_you"<<endl;
		}
	}
	return 0;
}
