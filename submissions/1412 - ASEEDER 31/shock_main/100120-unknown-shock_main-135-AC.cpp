#include<bits/stdc++.h>
using namespace std;
void appendInt(string &s, int v) {
    char buf[12];
    int len = 0;
    if (v == 0) {
        buf[len++] = '0';
    } else {
        while (v > 0) {
            buf[len++] = char('0' + v % 10);
            v /= 10;
        }
    }
    while (len > 0) s.push_back(buf[--len]);
}

// 并查集式“下一个尚未涂色的列”（路径减半，下标为展平后的一维位置）
int findNext(vector<int> &nxt, int idx) {
    while (nxt[idx] != idx) {
        nxt[idx] = nxt[nxt[idx]];
        idx = nxt[idx];
    }
    return idx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    string out;
    out.reserve(1 << 22);

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<int> er(Q), ec(Q), ep(Q);
        for (int i = 0; i < Q; ++i) {
            cin >> er[i] >> ec[i] >> ep[i];
        }

        const int W = M + 1;   // 每行末尾多留一个永不涂色的哨兵
        vector<int> nxt((size_t)N * W);
        for (size_t i = 0; i < nxt.size(); ++i) nxt[i] = (int)i;

        vector<int> ans((size_t)N * M, 0);

        // 逆序处理：第一次被涂到，就是正序里最后一次覆盖它的地震
        for (int i = Q - 1; i >= 0; --i) {
            const int R = er[i], C = ec[i], P = ep[i];
            const long long p2 = (long long)P * P;

            // 涂掉第 r 行上被本次地震覆盖、且尚未涂色的格子
            auto paintRow = [&](int r, int w, long long rem) {
                const int lo = max(0, C - w), hi = min(M - 1, C + w);
                const int base = r * W;
                int cur = findNext(nxt, base + lo);
                while (cur - base <= hi) {
                    const int c = cur - base;
                    const long long dc = (long long)c - C;
                    ans[(size_t)r * M + c] = (int)(rem - dc * dc + 1);
                    nxt[cur] = cur + 1;               // 标记已涂色
                    cur = findNext(nxt, cur);
                }
            };

            // 从震中向外逐行扩展，半宽 w 单调不增，因此不需要每行开方
            int w = P;
            for (int r = R; r >= max(0, R - P); --r) {
                const long long dr = (long long)r - R;
                const long long rem = p2 - dr * dr;
                while (w > 0 && (long long)w * w > rem) --w;
                paintRow(r, w, rem);
            }
            w = P;
            for (int r = R + 1; r <= min(N - 1, R + P); ++r) {
                const long long dr = (long long)r - R;
                const long long rem = p2 - dr * dr;
                while (w > 0 && (long long)w * w > rem) --w;
                paintRow(r, w, rem);
            }
        }

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                if (c) out.push_back(' ');
                appendInt(out, ans[(size_t)r * M + c]);
            }
            out.push_back('\n');
        }
    }
    cout << out << endl;
    return 0;
}
