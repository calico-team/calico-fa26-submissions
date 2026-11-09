#include<iostream>
using namespace std;
int main(){
    int n,om=2;
    cin>>n;
    for(int i=0;i<n;i++){
    	int n1;
    	cin>>n1;
    	int n2;
    	cin>>n2;
    	int x[105];
    	for(int a=0;a<n1;a++){
    		cin>>x[a];
    		int p=x[a];
				while((p-n2)>n2){
    			    om=om+1;
    			    p=p-n2;
			}
			if(om>2){
				om=2;
			}
			om=om-1;
		    if(om<0){
			    cout<<"NO"<<endl;
			    break;
		    }
		}
		if(om>0){
			cout<<"YES";
		}
	}
	return 0;
}

