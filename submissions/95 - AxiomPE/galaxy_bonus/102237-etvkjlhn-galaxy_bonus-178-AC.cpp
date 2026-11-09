#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(){

    int t;
    cin >> t;

    while (t--){

        int n, m, q;
        cin >> n >> m >> q;

        vector<string> g(n);

        for (int i = 0; i < n; i++){
            cin >> g[i];
        }

        int z = n * m;

        vector<int> p(2 * z);
        vector<int> sz(2 * z, 1);

        for (int i = 0; i < 2 * z; i++){
            p[i] = i;
        }

        auto find = [&](int x){

            while (p[x] != x){
                p[x] = p[p[x]];
                x = p[x];
            }

            return x;
        };

        auto unir = [&](int a, int b){

            a = find(a);
            b = find(b);

            if (a == b) return;

            if (sz[a] < sz[b]){
                swap(a, b);
            }

            p[b] = a;
            sz[a] += sz[b];
        };

        for (int i = 0; i < n; i++){

            for (int j = 0; j < m; j++){

                int a = i * m + j;

                if (g[i][j] == '.'){
                    unir(a, a + z);
                }

                if (j + 1 < m) {

                    if (g[i][j] != 'R' && g[i][j + 1] != 'R'){
                        unir(a, a + 1);
                    }

                    if (g[i][j] != 'B' && g[i][j + 1] != 'B'){
                        unir(a + z, a + 1 + z);
                    }
                }

                if (i + 1 < n) {

                    if (g[i][j] != 'R' && g[i + 1][j] != 'R'){
                        unir(a, a + m);
                    }

                    if (g[i][j] != 'B' && g[i + 1][j] != 'B'){
                        unir(a + z, a + m + z);
                    }
                }
            }
        }

        for (int i = 0; i < q; i++){

            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;

            int a = r1 * m + c1;
            int b = r2 * m + c2;

            if (g[r2][c2] == 'R'){
                b += z;
            }

            if (find(a) == find(b)){
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}