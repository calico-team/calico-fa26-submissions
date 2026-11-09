#include<iostream>
#include<string>
using namespace std;
int d[10005];
string out[10005];
int main(){
	int n;
	cin >> n;
	int x = 0;
	for(int i=0;i<n;i++){
		int t;
		int r; 
		cin >> t >> r; 
		for(int j=0;j<t;j++){
			cin >> d[j];
		}
		bool check = true;
		for(int j=0;j<t-1;j++){
			int cur = d[j];
			int next = d[j+1];
			if((max(next,cur) - min(next,cur)) < r){
				check = false;
				break;
			}
		}
		if(check == false){
			out[x] = "NO";
		}
		else{
			out[x] = "YES";
		}
		x++;
	}
	for(int i=0;i<x;i++){
		cout << out[i] << endl;
	}
	return 0;
}
