// Source: https://usaco.guide/general/io
#include <iostream>
#include <vector>
using namespace std;

string solve(long long N, long long R, vector<long long> A) {
	string answer="YES";
    for(int i=1; i<N; i++){
        if(A[i]-A[i-1]<R){
            answer="NO";
            break;
        }
    }
    return answer;
}

int main() {
	int T; cin >> T;
	while (T--) {
		long long N, R; cin >> N >> R;
		vector<long long> A(N);
		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}

		cout << solve(N, R, A) << "\n";
	}
}