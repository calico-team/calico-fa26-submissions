#include<iostream>
#include<cstring>
#include<string>
using namespace std;
int main(){
    int n;
    cin>>n;
    for(int i=0;i<=n;i++){
    	char a[105]={};
    	cin>>a;
    	int t=0;
    	for(int j=0;j<=105;j++){
    		if(a[i]=='w'&&a[i+1]=='r'&&a[i+2]=='i'&&a[i+3]=='t'&&a[i+4]=='e'&&a[i+5]=='_'&&a[i+6]=='m'&&a[i+7]=='e'){
    			cout<<a<<"make_it_sound_human"<<endl;
    			t++;
			}
			else if(a[i]=='w'&&a[i+1]=='h'&&a[i+2]=='a'&&a[i+3]=='t'&&a[i+4]=='_'&&a[i+5]=='i'&&a[i+6]=='s'){
    			cout<<a<<"do_not_hallucinate"<<endl;
    			t++;
			}
			else if(a[i]=='s'&&a[i+1]=='o'&&a[i+2]=='l'&&a[i+3]=='v'&&a[i+4]=='e'){
    			cout<<a<<"make_no_mistakes"<<endl;
    			t++;
			}
		}
		if(t==0){
			cout<<a<<"thank_you";
		}
	}
}

