#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	string(b[t]);
	int c[t];
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
								if(a[j+5]=='_'){
									if(a[j+6]=='m'){
										if(a[j+7]=='e'){
											b[i]=a;
											c[i]=1;
											l=1;
											break;
										}
									}
								}
								
							}
						}
					}
				}
			} 
			if(a[j]=='w'){
				if(a[j+1]=='h'){
					if(a[j+2]=='a'){
						if(a[j+3]=='t'){
							if(a[j+4]=='_'){
								if(a[j+5]=='i'){
									if(a[j+6]=='s'){
										b[i]=a;
										c[i]=2; 
										l=1;
										break;
									}
								}
							}
							
						}
					}
				}
			} 
			if(a[j]=='s'){
				if(a[j+1]=='o'){
					if(a[j+2]=='l'){
						if(a[j+3]=='v'){
							if(a[j+4]=='e'){
								b[i]=a;
								c[i]=3;
								l=1;
								break;
							}
						}
					}
				}
			} 
		}
		if(l==0){
			b[i]=a;
			c[i]=4;
		}
	}
	for(int i=0;i<t;i++){
		if(c[i]==1){
			cout<<b[i]<<"make_it_sound_human"<<endl;
		}
		if(c[i]==2){
			cout<<b[i]<<"do_not_hallucinate"<<endl; 
		}
		if(c[i]==3){
			cout<<b[i]<<"make_no_mistakes"<<endl;
		}
		if(c[i]==4){
			cout<<b[i]<<"thank_you"<<endl;
		}
	}
	return 0;
} 
