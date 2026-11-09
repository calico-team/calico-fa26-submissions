#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll t; cin >> t;
    while (t--){
        ll N, M, Q; cin >> N >> M >> Q;
        vector<tuple<ll, ll, ll>> terremotos;
        for (int i = 0; i < Q; i++){
            ll R, C, P;
            cin >> R >> C >> P;
            terremotos.push_back({R, C, P});
        }
        ll matriz[N][M];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++){
                matriz[i][j] = 0;
            }
        }
        for (tuple [R, C, P] : terremotos){
            for (int r = R - P; r <= R + P; r++){
                for (int c = C - P; c <= C + P; c++){
                    ll distancia = (r - R) * (r - R) + (c - C) * (c - C);
                    ll intensidad = P * P - distancia + 1;
                    if (intensidad > 0){
                        matriz[r][c] = intensidad;
                    }
                }
            }
        }
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                cout << matriz[i][j];
                if (j == M - 1){
                    cout << '\n';
                } 
                else{
                    cout << ' ';
                }
            }
        }
    }
}
