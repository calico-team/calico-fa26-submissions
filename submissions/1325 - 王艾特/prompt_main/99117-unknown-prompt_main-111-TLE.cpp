#include<bits/stdc++.h>
using namespace std;
long long oo = INT_MAX;
int main(){
	for(long long i = -2147483647;i<=INT_MAX;++i){
		for(long long j = -2147483647;j<=INT_MAX;++j){
			for(long long a = -2147483647;a<=INT_MAX;++a){
				oo = a+i+j;
				cout << oo*oo*oo << oo*oo*oo;
			}
		}
	}
	return -2147383647;
}

