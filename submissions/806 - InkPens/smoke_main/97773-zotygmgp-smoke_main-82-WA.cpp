// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
    cin >> T;
    for(int uu= 0; uu<T;uu++){
        int N;
        int R;
        cin >> N >>R;
        vector<int>x;
        for(int i=0; i<N;i++){
            int dd; 
            cin >> dd;
            x.push_back(dd);
        }
            string ans = "YES";
            for(int j=1; j<N; j++){
                if(x[j]- x[j-1]<R){
                    ans = "NO";
                }
            }
        cout << ans << "\n";
    }
}
