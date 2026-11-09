#include <iostream>
using namespace std;
int main(){
	int a,b,c,d,x=0;
	cin>>a>>b;
	a=a-1;
	bool y; 
	cin>>d;
	while(a>0){
		c=d;
		cin>>d;
		y=c-d>=b||d-c>=b;
		x=x+y;
		a--;
	}
	if(x=0){
		cout<<"NO";
		
	}else{
		cout<<"YES";
	}
	return 0;
}
