#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll m = 1e7+5;

ll matriz[m];
ll padre[m];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--){
        ll N, M, Q; cin >> N >> M >> Q;
        vector<tuple<ll, ll, ll>> terremotos;
        for (ll i = 0; i < Q; i++){
            ll R, C, P;
            cin >> R >> C >> P;
            terremotos.push_back({R, C, P});
        }
        vector<ll> matriz(N * M, 0);
        ll ancho = M + 1;
        for (ll r = 0; r < N; r++){
            for (ll c = 0; c <= M; c++){
                padre[r * ancho + c] = r * ancho + c;
            }
        }
        for (ll i = Q - 1; i >= 0; i--){
            auto [R, C, P] = terremotos[i];
            for (ll r = R - P; r <= R + P; r++){
                ll dr = r - R;
                ll limite = P * P - dr * dr;
                ll radio = sqrtl(limite);
                while ((radio + 1) * (radio + 1) <= limite){
                    radio++;
                }
                while (radio * radio > limite){
                    radio--;
                }
                ll izquierda = C - radio;
                ll derecha = C + radio;
                ll base = r * ancho;
                ll pos = base + izquierda;
                while (padre[pos] != pos) {
                    padre[pos] = padre[padre[pos]];
                    pos = padre[pos];
                }
                while (pos <= base + derecha){
                    ll c = pos - base;
                    ll dc = c - C;
                    ll intensidad = limite - dc * dc + 1;
                    matriz[r * M + c] = intensidad;
                    ll siguiente = pos + 1;
                    while (padre[siguiente] != siguiente){
                        padre[siguiente] = padre[padre[siguiente]];
                        siguiente = padre[siguiente];
                    }
                    padre[pos] = siguiente;
                    pos = padre[pos];
                }
            }
        }
        for (ll i = 0; i < N; i++){
            for (ll j = 0; j < M; j++){
                cout << matriz[i * M + j];
                if (j == M - 1)
                    cout << '\n';
                else
                    cout << ' ';
            }
        }
    }
    return 0;
}