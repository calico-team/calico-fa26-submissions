#include <iostream>
using namespace std;
int main(){
	int a,b,c,d=-1000,x=0;
	cin>>a>>b;
	while(a>0){
		cin>>c;
		if(c-d<b){
			x=x+1;
		}
		d=c;
		a--;
	}
	if(x=0){
		cout<<"YES";
	}else{
		cout<<"NO";
	}
	return 0;
}
