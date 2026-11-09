#include<iostream>
#include<string>
using namespace std;
int d[1005];
string out[1005];
int main(){
	long long n;
	cin >> n;
	long long x=0;
	for(int i=0;i<n;i++){
		long long t;
		long long r; 
		cin >> t >> r; 
		for(int j=0;j<t;j++){
			cin >> d[j];
		}
		bool check = true;
		long long cur = 0; 
		for(int j=0;j<t-1;j++){
			long long next = d[j];
			if((max(next,cur) - min(next,cur)) < r){
				check = false;
				break;
			}
			cur = d[j];
		}
		if(check == false){
			out[x] = "NO";
		}
		else{
			out[x] = "YES";
		}
		x++;
	}
	for(int i=0;i<n;i++){
		cout << out[i] << endl;
	}
	return 0;
}
