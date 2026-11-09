#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string fase;
    cin >> fase;
    int n;
    cin >> n;

    if (fase == "FIRST") {
        vector<vector<int>> vecinos(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            vecinos[u].push_back(v);
            vecinos[v].push_back(u);
        }

        vector<int> padre(n + 1, 0);
        vector<int> cola;
        cola.push_back(1);
        padre[1] = -1;                
        for (int idx = 0; idx < (int)cola.size(); idx++) {
            int u = cola[idx];
            for (int v : vecinos[u]) {
                if (v == padre[u]) continue;  
                padre[v] = u;
                cola.push_back(v);
            }
        }


        vector<int> A(n + 1, 0);
        int xorTodos = 0;
        for (int i = 2; i <= n; i++) {
            A[i] = padre[i];
            xorTodos ^= A[i];
        }
        A[1] = xorTodos;     

        for (int i = 1; i <= n; i++) cout << A[i] << " ";
        cout << "\n";
    }   else {
        vector<int> A(n + 1);
        for (int i = 1; i <= n; i++) cin >> A[i];

        int k = -1;
        for (int i = 1; i <= n; i++)
            if (A[i] == -1) k = i;

        if (k >= 2) {
            int resto = A[1];
            for (int i = 2; i <= n; i++)
                if (i != k) resto ^= A[i];
            A[k] = resto;
        }

        for (int i = 2; i <= n; i++)
            cout << i << " " << A[i] << "\n";
    }
    return 0;
} 
    