
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

int N, M;
vector<int> uf;  

int findRoot(int base, int x) {          
    int root = x;
    while (uf[base + root] != root) root = uf[base + root];
    while (uf[base + x] != root) {        
        int nx = uf[base + x];
        uf[base + x] = root;
        x = nx;
    }
    return root;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int Q;
        scanf("%d %d %d", &N, &M, &Q);
        vector<int> R(Q), C(Q), P(Q);
        for (int i = 0; i < Q; i++)
            scanf("%d %d %d", &R[i], &C[i], &P[i]);

        vector<int> ans((size_t)N * M, 0);
        uf.assign((size_t)N * (M + 1), 0);
        for (int r = 0; r < N; r++) {     
            int base = r * (M + 1);
            for (int c = 0; c <= M; c++) uf[base + c] = c;
        }

        for (int qi = Q - 1; qi >= 0; qi--) {   
            int p = P[qi], r0 = R[qi], c0 = C[qi];
            int rlo = r0 - p; if (rlo < 0) rlo = 0;
            int rhi = r0 + p; if (rhi > N - 1) rhi = N - 1;
            for (int r = rlo; r <= rhi; r++) {
                long long dr = r - r0;
                long long rem = (long long)p * p - dr * dr;
                if (rem < 0) continue;           
                int w = (int)sqrt((double)rem);  
                while ((long long)(w + 1) * (w + 1) <= rem) w++;
                while ((long long)w * w > rem) w--;
                int left = c0 - w; if (left < 0) left = 0;
                int right = c0 + w; if (right > M - 1) right = M - 1;
                int base = r * (M + 1);
                int c = findRoot(base, left);
                while (c <= right) {             
                    long long dc = c - c0;
                    ans[(size_t)r * M + c] = (int)(rem + 1 - dc * dc);
                    uf[base + c] = c + 1;        
                    c = findRoot(base, c + 1);
                }
            }
        }

       
        vector<char> out;
        out.reserve((size_t)N * M * 4 + N + 16);
        char buf[16];
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                int v = ans[(size_t)r * M + c];
                int len = 0;
                if (v == 0) buf[len++] = '0';
                while (v > 0) { buf[len++] = (char)('0' + v % 10); v /= 10; }
                while (len > 0) out.push_back(buf[--len]);
                out.push_back(c == M - 1 ? '\n' : ' ');
            }
        }
        fwrite(&out[0], 1, out.size(), stdout);
    }
    return 0;
}
