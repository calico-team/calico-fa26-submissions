// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int T; cin >> T;
    while(T--){
        int N, R; cin >> N >> R;
        bool es = true;
        int c = 2;
        vector<int> fa(N);
        int b1 = 0, b2 = 0;
        for(int i = 0; i < N; i++){
            cin >> fa[i]; 
        }
        for(int i = 0; i < N ; i++){
            while(b1 > 0 && fa[i] >= b1) {
                c++;
                b1 = b2;
                b2 = 0;
            }
            if(c <= 0){
                es = false;
                break;
            }if(b1 == 0) {
                b1  = fa[i] + R; 
            }
            else if (b2 == 0) {
                b2 = b1 + R; 
            }
            c--;
        }
        if(es){
            cout << "YES" << "\n";
        }else{
            cout << "NO" << "\n";
        }
    }


    
return 0;
}