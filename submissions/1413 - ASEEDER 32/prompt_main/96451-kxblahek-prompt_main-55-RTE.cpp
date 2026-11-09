#include<bits/stdc++.h>
using namespace std;
int n;
string c;
int co1(){
	string a=c;
	int k=0;
	for(int i=0;i<a.size();i++){
		if(a[i]=='w'&&a[i+1]=='r'&&a[i+2]=='i'&&a[i+3]=='t'&&a[i+4]=='e'&&a[i+5]=='_'&&a[i+6]=='m'&&a[i+7]=='e'){
			k++;
		}
		else if(a[i]=='w'&&a[i+1]=='h'&&a[i+2]=='a'&&a[i+3]=='t'&&a[i+4]=='_'&&a[i+5]=='i'&&a[i+6]=='s'){
			k+=20; 
		}
		else if(a[i]=='s'&&a[i+1]=='o'&&a[i+2]=='l'&&a[i+3]=='v'&&a[i+4]=='e'){
			k+=300; 
		}
	}
}
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>c;
		cout<<c;
		int co2=co1();
		if(i==n-1){
			cout<<"thank_you";
		}
		else{
			if(co2==1){
				cout<<"make_it_sound_human"; 
			}
			if(co2==20){
				cout<<"do_not_hallucinate"; 
			}
			if(co2==300){
				cout<<"make_no_mistakes"; 
			}
		}
		cout<<endl;
	}
}
