#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		string(a);
		cin>>a;
		int l=0;
		for(int j=0;j<100;j++){
			if(a[j]=='w'){
				if(a[j+1]=='r'){
					if(a[j+2]=='i'){
						if(a[j+3]=='t'){
							if(a[j+4]=='e'){
								cout<<a<<"make_it_sound_human"<<endl;
								l=1;
								break;
							}
						}
					}
				}
			} 
			if(a[j]=='w'){
				if(a[j+1]=='h'){
					if(a[j+2]=='a'){
						if(a[j+3]=='t'){
							cout<<a<<"do_not_hallucinate"<<endl; 
							l=1;
							break;
						}
					}
				}
			} 
			if(a[j]=='s'){
				if(a[j+1]=='o'){
					if(a[j+2]=='l'){
						if(a[j+3]=='v'){
							if(a[j+4]=='e'){
								cout<<a<<"make_no_mistakes"<<endl;
								l=1;
								break;
							}
						}
					}
				}
			} 
		}
		if(l==0){
			cout<<a<<"thank_you"<<endl;
		}
	}
	  
	return 0;
} 
