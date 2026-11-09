#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> G(N);

        for (int f = 0; f < N; f++) {
            cin >> G[f];
        }

        vector<vector<vector<bool>>> visitado(
            N, vector<vector<bool>>(M, vector<bool>(2, false))
        );

        queue<tuple<int, int, int>> cola;

        int f = N - 1;
        int c = M - 1;

        if (G[f][c] == '.' || G[f][c] == 'B') {
            visitado[f][c][0] = true;
            cola.push({f, c, 0});
        }

        if (G[f][c] == '.' || G[f][c] == 'R') {
            visitado[f][c][1] = true;
            cola.push({f, c, 1});
        }

        int desplazamientoFilas[] = {-1, 1, 0, 0};
        int desplazamientoColumnas[] = {0, 0, -1, 1};

        while (!cola.empty()) {
            auto [filaActual, columnaActual, modo] = cola.front();
            cola.pop();

            if (G[filaActual][columnaActual] == '.') {
                int nuevoModo = 1 - modo;

                if (!visitado[filaActual][columnaActual][nuevoModo]) {
                    visitado[filaActual][columnaActual][nuevoModo] = true;
                    cola.push({filaActual, columnaActual, nuevoModo});
                }
            }
            for (int direccion = 0; direccion < 4; direccion++) {
                int nuevaFila = filaActual + desplazamientoFilas[direccion];
                int nuevaColumna = columnaActual + desplazamientoColumnas[direccion];

                if (nuevaFila < 0 || nuevaFila >= N ||
                    nuevaColumna < 0 || nuevaColumna >= M) {
                    continue;
                }

                if (G[nuevaFila][nuevaColumna] != '.' &&
                    !((modo == 0 && G[nuevaFila][nuevaColumna] == 'B') ||
                      (modo == 1 && G[nuevaFila][nuevaColumna] == 'R'))) {
                    continue;
                }

                if (!visitado[nuevaFila][nuevaColumna][modo]) {
                    visitado[nuevaFila][nuevaColumna][modo] = true;
                    cola.push({nuevaFila, nuevaColumna, modo});
                }
            }
        }

        while (Q--) {
            int filaInicial, columnaInicial, filaFinal, columnaFinal;
            cin >> filaInicial >> columnaInicial >> filaFinal >> columnaFinal;

            if(visitado[filaInicial][columnaInicial][0]) {
                cout << "YES" << endl;
            }else {
                cout << "NO" << endl;
            }
        }
    }
}
    