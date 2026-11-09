// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int T; cin >> T;
    while(T--){
        int N, M, K; cin >> N >> M >> K;
        vector<int> P;
        P.push_back(0);
        for(int i = 0; i < N; i++) {
            int x; cin >> x;
            P.push_back(x);
        }
        vector <int> D(N + 1, 0);
        bool H = true;
        while (H) {
            H = false;
            for (int i = 1; i <= N; i++) {
                int pr = P[i];
                int nv = 1;
                if (pr != 0 && pr <= N) {
                    nv = D[pr] + 1;
                }
                if (D[i] != nv) {
                    D[i] = nv;
                    H = true;
                }
            }
        }
        vector<int> freq(max(N + 2,M + 2), 0);
        for(int i = 1; i <= N; i++) {
            if(D[i] <= M && D[i] < freq.size()) {
                freq[D[i]]++;
            }
        }
        int contador = 0, contiene = 0;
        for(int s = 1; s <= M;s++) {
            contiene += freq[s];
            int g = min(K, contiene);
            contiene -= g;

            contador += g;
        }

        cout << contador << "\n";
    }    
return 0;
}