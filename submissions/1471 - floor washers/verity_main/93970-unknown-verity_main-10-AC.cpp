#include <bits/stdc++.h>
using namespace std;

int t;
int N;
int K;
char lst[200];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> t;
	
	while(t--){
		cin >> N;
		cin >> K;
		
		vector<char> v;
		
		for(int i = 0; i < K; i++){
			char c;
			cin >> c;
			v.push_back(c);
		}
		
		set<int> sat;
		
		for(int i = 0; i < N; i++){
			sat.insert(i);
		}
		
		for(int i = 0; i < K; i++){
			for(int j : sat) lst[j] = v[i];
			
			for(int j = 0; j < N; j++){
				printf("%c",lst[j]);
			}
			printf("\n");
			fflush(stdout);
			
			string s;
			cin >> s;
			
			if(s == "CORRECT"){
				break;
			}
			else{
				sat.clear();
				for(int i = 0 ; i < N; i++){
					if(s[i] == '_') sat.insert(i);
				}
			}
		}
	}
	
}
