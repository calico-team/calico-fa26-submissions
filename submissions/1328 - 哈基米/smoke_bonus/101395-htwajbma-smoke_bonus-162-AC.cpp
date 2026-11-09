#include<bits/stdc++.h>
using namespace std;
string solve(int N,int R,vector<long long>A) {
	int ic=2;
	int it=0;
	for(int i=0;i<N;i++){
		bool flag=false;
		if((A[i]-it)/R>=2||i==0){
			ic=2;
		}else if((A[i]-it)/R==1){
			flag=true;
			ic++;
			if(ic>=2)ic=2;
		}
		if(ic==2){
			it=A[i];
		}else if(flag){
			it+=R;
		}
		if(ic==0){
			return "NO";
		}
		ic--;
	}
	return "YES";
}
int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int T; cin >> T;
	while (T--) {
		int N, R; cin >> N >> R;
		vector<long long> A(N);
		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}
		cout << solve(N, R, A) << "\n";
	}
}

