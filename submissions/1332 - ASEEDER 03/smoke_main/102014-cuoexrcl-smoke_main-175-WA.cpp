#include<iostream>
#include<string>
using namespace std;
string out[105];
int pos[105];
int charges[2] = {1,1};
int main(){
	int n;
	cin >> n;
	int s = 0;
	for(int i=0;i<n;i++){
		int t,r;
		cin >> t;
		cin >> r;
		for(int j=0;j<t;j++){
			cin >> pos[t];
		}
		int x=0;
		int cur = 0;
		bool check = true;
		for(int j=1;j<=pos[t-1];j++){
			if(r%j == 0){
				if(charges[0] == 0 && charges[1] != 0){
					charges[0] == 1;
				}
				else if(charges[0] == 0 && charges[1] == 0){
					charges[1] == 1;
				}
		    }
		    int next = pos[x];
		    if(max(next,cur)- min(next,cur) < r){
		    	if(charges[0] == 1 && charges[1] == 1){
					charges[0] == 0;
				}
				else if(charges[0] == 0 && charges[1] == 1){
					charges[1] == 0;
				}
				else{
					check = false;
					break;
				}
			}
			cur = next;
			x++;
		}
		if(check == true){
			out[s] = "YES";
		}
		else if(check == false){
			out[s] = "NO";
		}
		s++;
	}
	for(int i=0;i<n;i++){
		cout << out[i] << endl;
	}
	return 0;
}
