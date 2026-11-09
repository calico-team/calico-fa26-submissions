// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

// /**
//  * Output whether all of the requests can be fulfilled.
//  *
//  * N: Number of smoke requests
//  * R: Number of seconds needed for a smoke charge to recharge
//  * A: List of timestamps where smokes are requested
//  */
// string solve(long long N, long long R, vector<long long> A) {
	
//   long long smoke1=0;
//   long long smomke2=0;

//   for(long long i; i<N; i++){
//     long long rec=A[i];
//     long long nextsmoke=0;
//     if(rec>=smokme1){
//         smoke1=smoke2;
//         smoke2=rec+R;
//     }else{
//         rec=smoke1;
//         smoke2
//     }
//   }  
    
//     // YOUR CODE HERE





// 	return "";
// }

// long long main() {
// 	long long T; cin >> T;
// 	while (T--) {
// 		long long N, R; cin >> N >> R;
// 		vector<long long> A(N);
// 		for (long long i = 0; i < N; i++) {
// 			cin >> A[i];
// 		}

// 		cout << solve(N, R, A) << "\n";
// 	}
// }


// long long main() {
// 	long long tc; cin >> tc;
//     while (tc--) {
//         long long n; cin >> n;
//         long long r; cin >> r;
//         long long s1 = -3 * r; long long s2 = -3 * r;
//         bool stillRun = true;
//         //vector<long long> v;
//         for (long long i = 0; i < n; i++) {
//             long long tmp; cin >> tmp;
//             if (s1 < tmp && stillRun) {
//                 if (s2 <= tmp) {
//                     s1 += r;
//                 } else {
//                     s1 = s2 + r;
//                 }
//             } else if (s2 < tmp && stillRun) {
//                 if (s1 <= tmp) {
//                     s2 += r;
//                 } else  {
//                     s2 = s1 + r;
//                 }
//             } else if (stillRun) {
//                 /*cout << tmp << endl;
//                 cout << s1 << " " << s2 << endl;*/
//                 cout << "NO\n";
//                 stillRun = false;
//             }
//             /*long long tmp; cin >> tmp;
//             v.push_back(tmp);*/
//         }
//         if (stillRun) cout << "YES\n";


//     }

// }

string solve(long long N, long long R, vector<long long> A) {
	// YOUR CODE HERE
    long long smoke1=0;
    long long smoke2=0;
 for(long long i=0; i<N; i++){
    long long rec=A[i];
    if(smoke1<=smoke2){
    
        if(rec>=smoke1){
            smoke1=max(rec,smoke2)+R;
        }else{
            return"NO";
        }
    }else{
        if(rec>=smoke2){
            smoke2=max(rec,smoke1)+R;
        }else{
            return "NO";
        }
    }
 }

	return "YES";
}

int main() {

    // sets up the fast io
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	long long T; cin >> T;
	while (T--) {
		long long N, R; cin >> N >> R;
		vector<long long> A(N);
		for (long long i = 0; i < N; i++) {
			cin >> A[i];
		}

		cout << solve(N, R, A) << "\n";
	}
}
