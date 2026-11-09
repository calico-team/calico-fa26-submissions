
#include <cstdio>
#include <vector>
using namespace std;

int main() {
    char phase[16];
    if (scanf("%s", phase) != 1) return 0;
    int N;
    scanf("%d", &N);

    if (phase[0] == 'F') {                 
    
        vector<int> head(N + 1, -1);
        vector<int> nxt(2 * N), to(2 * N);
        int ecnt = 0;
        for (int e = 0; e < N - 1; e++) {
            int u, v;
            scanf("%d %d", &u, &v);
            to[ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt++;
            to[ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt++;
        }
        
        vector<int> parent(N + 1, 0), order;
        order.reserve(N);
        order.push_back(1);
        parent[1] = 1;                    
        for (size_t h = 0; h < order.size(); h++) {
            int u = order[h];
            for (int e = head[u]; e != -1; e = nxt[e]) {
                int v = to[e];
                if (parent[v] == 0 && v != 1) {
                    parent[v] = u;
                    order.push_back(v);
                }
            }
        }
        int par = 0;                      
        for (int i = 2; i <= N; i++) {     
            printf("%d ", parent[i]);
            par ^= parent[i];
        }
        printf("%d\n", par);             
    } else {                              
        vector<int> A(N + 1);
        int missPos = -1;
        long long x = 0;                  
        for (int i = 1; i <= N; i++) {
            scanf("%d", &A[i]);
            if (A[i] == -1) {
                missPos = i;
            } else if (i <= N - 1) {
                x ^= A[i];
            }
        }
        if (missPos == -1) {              
            missPos = N;
            A[N] = 0;
        }
        if (missPos <= N - 1)             
            A[missPos] = A[N] ^ (int)x;
        for (int i = 2; i <= N; i++) {    
            printf("%d %d\n", i, A[i - 1]);
        }
    }
    return 0;
}
