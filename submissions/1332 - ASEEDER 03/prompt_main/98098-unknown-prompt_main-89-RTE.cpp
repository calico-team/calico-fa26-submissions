#include <iostream>
using namespace std;
int main(){
	int a;
	bool s1=0,s2=0,s3=0;
	cin>>a;
	string s[100];
	for(int i=0; i<a; i++){
		for(int p=0; p<100; p++){
			p=0;
			cin>>s[p];
			for(int j=0; j<100; j++){
				if(s[j]+s[j+1]+s[j+2]+s[j+3]+s[j+4]+s[j+5]+s[j+6]+s[j+7]=="write_me"){
					s1=1;
					for(int z=0; z<100; z++){
						cout<<s[z];
					}
					cout<<"make_it_sound_human"<<endl;
					break;
				}
				else if(s[j]+s[j+1]+s[j+2]+s[j+3]+s[j+4]+s[j+5]+s[j+6]=="what_is"){
					s2=1;
					for(int z=0; z<100; z++){
						cout<<s[z];
					}
					cout<<"do_not_hallucinate"<<endl;
					break;
				}
				else if(s[j]+s[j+1]+s[j+2]+s[j+3]+s[j+4]=="solve"){
					s3=1;
					for(int z=0; z<100; z++){
						cout<<s[z];
					}
					cout<<"make_no_mistakes"<<endl;
					break;
				}
				else{
					continue;
				} 
			}
			if(s1==0 && s2==0 && s3==0){
				for(int z=0; z<100; z++){
					cout<<s[z];
				}
				cout<<"thank_you"<<endl;
				break;
			}
		}
	}	
	return 0;
} 
