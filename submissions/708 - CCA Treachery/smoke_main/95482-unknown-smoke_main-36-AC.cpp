#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long

// void selfIO()
// {
// 	cin.tie(0)->sync_with_stdio(0);
// 	freopen(R"(C:\Users\steph\OneDrive\Desktop\VisCodeFiles\codeforces\Scratchpaper\input.txt)", "r", stdin);
// 	freopen(R"(C:\Users\steph\OneDrive\Desktop\VisCodeFiles\codeforces\Scratchpaper\output.txt)", "w", stdout);
// }

// void setIO(string name = "") {  // name is nonempty for USACO file I/O
// 	cin.tie(0);
// 	if (!name.empty()) {
// 		freopen((name + ".in").c_str(), "r", stdin);
// 		freopen((name + ".out").c_str(), "w", stdout);
// 	}
// }


signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	//cout << fixed << setprecision(10);
	// g++ ezscratch.cpp -o ezscratch; .\ezscratch.exe
	// R"(C:\Users\steph\OneDrive\Desktop\VisCodeFiles\codeforces\Scratchpaper

	//setIO("haybales");
	//selfIO();

    int t;
    cin >> t;
    while (t--){
        int n, r;
		cin >> n >> r;
		vector<int> arr(n, 0);
		int r1 = 0; int r2 = 0;
		for (int i = 0; i < n; i++){
			cin >> arr[i];
		}
		int yes = 1;
		for (int i = 0; i < n; i++){
			if (arr[i] < r1 && arr[i] < r2){
				yes = 0;
			} else if (arr[i] < r1 && arr[i] >= r2){
				r2 = max(arr[i]+r, r1+r);
			} else if (arr[i] >= r1 && arr[i] < r2){
				r1 = max(arr[i]+r, r2+r);
			} else {
				r1 = arr[i]+r;
			}
		}
		if (yes == 1){
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
		

        
    }
    
	
}