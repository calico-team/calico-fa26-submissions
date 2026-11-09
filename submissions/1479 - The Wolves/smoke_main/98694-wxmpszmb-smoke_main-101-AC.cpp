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
// string solve(int N, int R, vector<int> A) {
	
//   int smoke1=0;
//   int smomke2=0;

//   for(int i; i<N; i++){
//     int rec=A[i];
//     int nextsmoke=0;
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

// int main() {
// 	int T; cin >> T;
// 	while (T--) {
// 		int N, R; cin >> N >> R;
// 		vector<int> A(N);
// 		for (int i = 0; i < N; i++) {
// 			cin >> A[i];
// 		}

// 		cout << solve(N, R, A) << "\n";
// 	}
// }


// int main() {
// 	int tc; cin >> tc;
//     while (tc--) {
//         int n; cin >> n;
//         int r; cin >> r;
//         int s1 = -3 * r; int s2 = -3 * r;
//         bool stillRun = true;
//         //vector<int> v;
//         for (int i = 0; i < n; i++) {
//             int tmp; cin >> tmp;
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
//             /*int tmp; cin >> tmp;
//             v.push_back(tmp);*/
//         }
//         if (stillRun) cout << "YES\n";


//     }

// }

string solve(int N, int R, vector<int> A) {
	// YOUR CODE HERE
    int smoke1=0;
    int smoke2=0;
 for(int i=0; i<N; i++){
    int rec=A[i];
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
	int T; cin >> T;
	while (T--) {
		int N, R; cin >> N >> R;
		vector<int> A(N);
		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}

		cout << solve(N, R, A) << "\n";
	}
}
