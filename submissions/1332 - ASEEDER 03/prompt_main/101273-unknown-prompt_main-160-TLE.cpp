#include <iostream>
using namespace std;
int main(){
	int a;
	bool s1=0,s2=0,s3=0;
	cin>>a;
	string s[100];
	for(int i=0; i<a; i++){
		for(int p=0; p<50; p++){
			p=0;
			cin>>s[p];
			for(int j=0; j<50; j++){
				if(s[j]+s[j+1]+s[j+2]+s[j+3]+s[j+4]+s[j+5]+s[j+6]+s[j+7]=="write_me"){
					s1=1;
					for(int z=0; z<100; z++){
						cout<<s[z];
					}
					cout<<"make_it_sound_human"<<endl;
				}
				else if(s[j]+s[j+1]+s[j+2]+s[j+3]+s[j+4]+s[j+5]+s[j+6]=="what_is"){
					s2=1;
					for(int z=0; z<100; z++){
						cout<<s[z];
					}
					cout<<"do_not_hallucinate"<<endl;
				}
				else if(s[j]+s[j+1]+s[j+2]+s[j+3]+s[j+4]=="solve"){
					s3=1;
					for(int z=0; z<100; z++){
						cout<<s[z];
					}
					cout<<"make_no_mistakes"<<endl;
				}
			}
			if(s1==0 && s2==0 && s3==0){
					for(int z=0; z<100; z++){
				 		cout<<s[z];
					}
					cout<<"thank_you"<<endl;
			}
		}
	}	
	return 0;
} 
