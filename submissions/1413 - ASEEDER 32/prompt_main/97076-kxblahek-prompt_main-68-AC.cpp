#include<bits/stdc++.h>
using namespace std;
int n;
string c;
int v(){
	string a=c;
	int k=0;
	for(int i=0;i<a.length();i++){
		if(i+7<a.length()&&a[i]=='w'&&a[i+1]=='r'&&a[i+2]=='i'&&a[i+3]=='t'&&a[i+4]=='e'&&a[i+5]=='_'&&a[i+6]=='m'&&a[i+7]=='e'){
			k++;
		}
		if(i+6<a.length()&&a[i]=='w'&&a[i+1]=='h'&&a[i+2]=='a'&&a[i+3]=='t'&&a[i+4]=='_'&&a[i+5]=='i'&&a[i+6]=='s'){
			k+=20; 
		}
		if(i+4<a.length()&&a[i]=='s'&&a[i+1]=='o'&&a[i+2]=='l'&&a[i+3]=='v'&&a[i+4]=='e'){
			k+=300; 
		}
	}
	return k;
}
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>c;
		cout<<c;
		int x=v();
		if(x==1){
			cout<<"make_it_sound_human"; 
		}
		else if(x==20){
			cout<<"do_not_hallucinate"; 
		}
		else if(x==300){
			cout<<"make_no_mistakes"; 
		}
		else{
			cout<<"thank_you";
		}
		cout<<endl;
	}
}
