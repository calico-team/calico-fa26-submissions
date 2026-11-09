// Source: https://usaco.guide/general/io
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

string solve(long long N, long long R, vector<long long> A) {
	queue<long long> q;
	int c=2;
	for(long long t:A){
        while(!q.empty()&& q.front()<=t){
            q.pop();
            c++;
        }
        if(c==0){
            return "NO";
        }
        c--;
        long long b;
        if(q.empty())
            b=t+R;
        else
            b=q.back()+R;
            q.push(b);
    }
	
	return "YES";
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