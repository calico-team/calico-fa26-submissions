#include<iostream>
#include<string>
using namespace std;
int data[1005];
string out[1005];
int main(){
	int n;
	cin >> n;
	int x = 0;
	for(int i=0;i<n;i++){
		int t;
		int r; 
		cin >> t >> r; 
		for(int j=0;j<t;j++){
			cin >> data[j];
		}
		bool check = true;
		for(int j=0;j<t-1;j++){
			int cur = data[j];
			int next = data[j+1];
			if((next - cur) < r){
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
