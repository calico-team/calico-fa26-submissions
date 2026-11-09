#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, M, Q;
        scanf("%d %d %d", &N, &M, &Q);
        int W = M + 2;
        int size = (N + 2) * W;
        vector<unsigned char> cell(size, 0);
        char row[512];
        for (int r = 0; r < N; r++) {
            scanf("%s", row);
            for (int c = 0; c < M; c++) {
                unsigned char v = row[c] == '.' ? 3 : (row[c] == 'B' ? 1 : 2);
                cell[(r + 1) * W + c + 1] = v;
            }
        }
        vector<int> comp(2 * size, -1);
        int label = 0;
        vector<int> st;
        for (int s = 0; s < 2 * size; s++) {
            int m0 = s >= size;
            int q0 = s - m0 * size;
            if (!(cell[q0] & (1 << m0)) || comp[s] >= 0) continue;
            comp[s] = label;
            st.push_back(s);
            while (!st.empty()) {
                int v = st.back();
                st.pop_back();
                int m = v >= size;
                int q = v - m * size;
                int off = m * size;
                int d[4] = {-1, 1, -W, W};
                for (int k = 0; k < 4; k++) {
                    int nq = q + d[k];
                    if ((cell[nq] & (1 << m)) && comp[off + nq] < 0) {
                        comp[off + nq] = label;
                        st.push_back(off + nq);
                    }
                }
                if (cell[q] == 3) {
                    int o = (1 - m) * size + q;
                    if (comp[o] < 0) {
                        comp[o] = label;
                        st.push_back(o);
                    }
                }
            }
            label++;
        }
        string out;
        for (int i = 0; i < Q; i++) {
            int sr, sc, er, ec;
            scanf("%d %d %d %d", &sr, &sc, &er, &ec);
            int s = (sr + 1) * W + sc + 1;
            int e = (er + 1) * W + ec + 1;
            int lab = comp[s];
            bool ok;
            if (cell[e] == 2) ok = comp[size + e] == lab;
            else ok = comp[e] == lab;
            out += ok ? "YES\n" : "NO\n";
        }
        fputs(out.c_str(), stdout);
    }
    return 0;
}
 