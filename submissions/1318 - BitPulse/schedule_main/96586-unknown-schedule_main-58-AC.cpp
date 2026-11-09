
#include <cstdio>
#include <vector>
using namespace std;

const int MAXL = 1005;   

int P[10005];           
int lvl[10005];         
long long cnt[MAXL + 2];

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int N, M, K;
        scanf("%d %d %d", &N, &M, &K);

        vector< vector<int> > child(N + 1);  
        vector<int> q;                       

        for (int i = 1; i <= N; i++) {
            scanf("%d", &P[i]);
            lvl[i] = 0;
        }
        for (int i = 1; i <= N; i++) {
            if (P[i] == 0) { lvl[i] = 1; q.push_back(i); }
            else child[P[i]].push_back(i);
        }
        for (size_t h = 0; h < q.size(); h++) {   
            int u = q[h];
            for (size_t j = 0; j < child[u].size(); j++) {
                int c = child[u][j];
                lvl[c] = lvl[u] + 1;
                q.push_back(c);
            }
        }


        int maxl = 0;
        for (int i = 1; i <= N; i++)
            if (lvl[i] > maxl) maxl = lvl[i];
        for (int d = 0; d <= maxl + 1; d++) cnt[d] = 0;
        for (int i = 1; i <= N; i++) cnt[lvl[i]]++;
        for (int d = maxl; d >= 1; d--) cnt[d] += cnt[d + 1];  // cnt[d] = S(d)

        
        long long drop = 0;
        for (int d = 1; d <= maxl; d++) {
            long long semis = M - d + 1;
            if (semis < 0) semis = 0;          // d > M: 完全没学期可用
            long long cap = semis * (long long)K;   // M*K <= 5e4*1e4 = 5e8, 用 long long
            long long loss = cnt[d] - cap;
            if (loss > drop) drop = loss;
        }

        printf("%lld\n", (long long)N - drop);
    }
    return 0;
}
