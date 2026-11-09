#include <bits/stdc++.h>
using namespace std;
struct Earthquake {
    int r,c, p;
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >>T;
    while (T--){
        int N,M, Q;
        cin >>N >> M >>Q;
        vector<Earthquake>events(Q);
        for (auto &e : events) {
            cin >> e.r >> e.c>> e.p;
        }
        bool transposed= (N > M);
        int S= min(N, M);
        int L = max(N, M);
        int stride = L +1;
        vector<int> nxt((size_t)S * stride);
        for(int s =0; s < S; ++s) {
            iota(nxt.begin() +(size_t)s* stride,nxt.begin() + (size_t)(s +1) * stride,0);
        }
        auto find_next = [&](int s, int x) {
            int base= s* stride;
            int y = x;
            while (nxt[base +y] !=y) {
                y = nxt[base +y];
            }
            while (nxt[base + x] != x) {
                int z = nxt[base+ x];
                nxt[base +x] = y;
                x = z;
            }
            return y;
        };
        vector<int>ans((size_t)N * M, 0);
        for (int qi= Q -1; qi >= 0; --qi) {
            const auto &e =events[qi];
            int a = transposed ? e.c : e.r;
            int b =transposed ? e.r : e.c;
            long long p2= 1LL *e.p * e.p;
            for(int s = a - e.p; s <= a + e.p;++s){
                long long ds = s - a;
                long long rem = p2- ds * ds;
                int w =(int)sqrt((long double)rem);
                while(1LL* (w + 1) * (w + 1) <= rem) {
                    ++w;
                }
                while (1LL * w * w > rem) {
                    --w;
                }
                int left = b - w;
                int right =b + w;
                int t = find_next(s, left);
                while(t<= right) {
                    long long dt = t - b;
                    int value = (int)(
                        p2 - ds * ds -dt* dt + 1
                    );
                    int r = transposed ? t : s;
                    int c =transposed ? s : t;
                    ans[(size_t)r* M + c] = value;
                    int base = s * stride;
                    nxt[base + t] =find_next(s, t + 1);

                    t = nxt[base+ t];
                }
            }
        }
        for (int r =0; r < N; ++r) {
            for (int c =0;c < M; ++c) {
                if(c) cout <<' ';
                cout << ans[(size_t)r* M + c];
            }
            cout <<'\n';
        }
    }
    return 0;
}