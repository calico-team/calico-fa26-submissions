#include <iostream>
using namespace std;
int main(){
	int a,b,c,d,x=0;
	cin>>a>>b;
	a=a-1;
	cin>>d;
	while(a>0){
		c=d;
		cin>>d;
		if(c-d<b||d-c<b){
			x=x+0;
		}else{
			x=x+1;
		}
		
		a--;
	}
	if(x=0){
		cout<<"NO";
		
	}else{
		cout<<"YES";
	}
	return 0;
}
