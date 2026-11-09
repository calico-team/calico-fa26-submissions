#include <iostream>
using namespace std;
int main(){
	int a;
	cin>>a;
    for(int i=0;i<a;i++){
    	int n,r,s=1,shen[10005]={},f=1;
    	cin>>n>>r>>shen[0];
    	for(int b=1;b<n;b++){
    		cin>>shen[b];
    		if(shen[b]-shen[b-1]>=r){
    			if(shen[b]-shen[b-1]>=r*2 && s<=1){
    				s++;
				}
    			continue;
			}else if(s>=1){
				s--;
			}else if(s==0){
				f=0;
			}
		}if(f==1){
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}

