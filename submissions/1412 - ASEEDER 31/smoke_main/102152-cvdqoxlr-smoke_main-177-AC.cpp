#include<bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    string out;
    out.reserve(1 << 16);

    while (T--) {
        int N;
        long long R;
        cin >> N >> R;

        long long q0 = 0, q1 = 0;      // 队列里的两个完成时刻
        int pending = 0;               // 正在回复的个数
        bool ok = true;

        for (int i = 0; i < N; ++i) {
            long long t;
            cin >> t;
            if (!ok) continue;         // 已经判负，只把本测试点的输入读干净

            while (pending > 0 && q0 <= t) {   // 先结算，再处理请求
                if (pending == 2) q0 = q1;
                --pending;
            }

            if (pending == 2) { ok = false; continue; }   // 手上没有充能可用

            const long long startAt = (pending == 0) ? t : q0;   // 串行：排在上一个后面
            if (pending == 0) q0 = startAt + R;
            else q1 = startAt + R;
            ++pending;
        }

        out += ok ? "YES\n" : "NO\n";
    }

    cout << out;
    return 0;
}

