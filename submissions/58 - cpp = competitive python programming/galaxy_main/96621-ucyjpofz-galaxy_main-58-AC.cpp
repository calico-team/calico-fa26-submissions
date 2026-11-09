#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

char grid[200][200];
int dsu[40000];
int find(int a) {
    if (dsu[a] == a) return a;
    return dsu[a] = find(dsu[a]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> grid[i][j];
                dsu[i * M + j] = i * M + j;
                if (i && (grid[i - 1][j] == grid[i][j] || grid[i - 1][j] == '.' || grid[i][j] == '.')) dsu[find(i * M + j)] = find((i - 1) * M + j);
                if (j && (grid[i][j - 1] == grid[i][j] || grid[i][j - 1] == '.' || grid[i][j] == '.')) dsu[find(i * M + j)] = find(i * M + j - 1);
            }
        }

        while (Q--) {
            int Rs, Cs, Re, Ce;
            cin >> Rs >> Cs >> Re >> Ce;
            if (find(Rs * M + Cs) == find(Re * M + Ce)) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}