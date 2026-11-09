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
    		if(shen[1]-shen[0]>=r){
    			if(shen[1]-shen[0]>=r*2){
    				s++;
				}
    			continue;
			}else if(s>0){
				s--;
			}else{
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

