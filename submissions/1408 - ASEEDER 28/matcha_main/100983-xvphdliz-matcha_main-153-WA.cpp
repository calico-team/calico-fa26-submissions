#include <iostream>
#include <vector>
using namespace std;

/*
 * 思路
 * ----
 * 观察：最优解中，每一天 f_i 要么取端点 L_i / R_i，要么是"某一天 i* 沿着 L_i（或 R_i）
 * 的二进制前缀走到第 J 位后翻转该位，之后低 J 位任意"。一旦有一天拥有低 J 位的完全自由，
 * 答案的第 0..J 位都可以凑成 1。
 *
 * 因此答案 = max over (端点选择 σ, 自由位 J) 的 [ XOR_σ 的高位 (> J) ] << (J+1) | (2^(J+1)-1)
 * 约束：存在 i 使得 σ_i 这一侧在第 J 位可以"放开"，即
 *   L 侧：s_i > J 且 L_i 第 J 位为 0；   R 侧：s_i > J 且 R_i 第 J 位为 1
 * （s_i 为 L_i、R_i 最高不同位）。令 a_i / b_i 为 L 侧 / R 侧能放开的最高位，则
 *   σ 在层级 J 合法 <=> 存在 i: (σ_i = L 且 a_i >= J) 或 (σ_i = R 且 b_i >= J)。
 *
 * 固定 J：令 d_i = (L_i>>(J+1)) ^ (R_i>>(J+1))。XOR_σ 的高位 = V ^ (某个 d 子集异或)。
 *  - 若有某个 i 两侧都合法：无约束 -> 线性基求最大。
 *  - 否则 E = {恰有一侧合法的 i}，非法的只有"E 全在坏侧"这一种赋值。
 *    把 E 中向量打上标记插入线性基；若有 E 向量线性相关 -> 实际无约束；
 *    否则要求结果至少包含一个 E 基向量：贪心求最大，若未包含任何 E 向量，
 *    则在 E 向量中最低主元处强制包含，其余位继续贪心（可证明这是最优偏离）。
 *
 * 复杂度 O(31 * N * 30)。
 */

static int highestBit(long long x) {       // -1 if x == 0
    int h = -1;
    while (x) { ++h; x >>= 1; }
    return h;
}

long long solve(int n, const vector<long long>& L, const vector<long long>& R) {
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        int s = highestBit(L[i] ^ R[i]);
        if (s < 0) { a[i] = b[i] = -1; continue; }
        long long low = (1LL << s) - 1;
        a[i] = highestBit(low & ~L[i]);      // L 侧：s 以下最高的 0 位
        b[i] = highestBit(low & R[i]);       // R 侧：s 以下最高的 1 位
    }

    long long ans = 0;
    long long basis[31];
    bool isE[31];
    vector<long long> Evec;

    for (int J = -1; J <= 29; ++J) {
        int sh = J + 1;
        for (int k = 0; k < 31; ++k) { basis[k] = 0; isE[k] = false; }
        Evec.clear();
        long long V = 0;
        bool unconstrained = (J == -1);

        auto insert = [&](long long x, bool tagE) -> bool {   // 返回是否成功插入（线性无关）
            for (int k = 29 - sh; k >= 0; --k) {
                if (!((x >> k) & 1)) continue;
                if (!basis[k]) { basis[k] = x; isE[k] = tagE; return true; }
                x ^= basis[k];
            }
            return false;
        };

        for (int i = 0; i < n; ++i) {
            long long hL = L[i] >> sh, hR = R[i] >> sh, d = hL ^ hR;
            if (J == -1) {
                V ^= hL;
                if (d) insert(d, false);
                continue;
            }
            bool okL = a[i] >= J, okR = b[i] >= J;
            if (okL && okR) { unconstrained = true; V ^= hL; if (d) insert(d, false); }
            else if (okL)   { V ^= hR; Evec.push_back(d); }   // 坏侧是 R
            else if (okR)   { V ^= hL; Evec.push_back(d); }   // 坏侧是 L
            else            { V ^= hL; if (d) insert(d, false); }
        }
        if (J >= 0 && !unconstrained && Evec.empty()) continue;   // 该层级不可行

        for (long long d : Evec)
            if (!insert(d, true)) unconstrained = true;           // E 向量线性相关 -> 无约束

        long long cur = V;
        bool gotE = false;
        for (int k = 29 - sh; k >= 0; --k) {
            if (basis[k] && !((cur >> k) & 1)) { cur ^= basis[k]; if (isE[k]) gotE = true; }
        }
        if (!unconstrained && !gotE) {
            int be = -1;
            for (int k = 0; k <= 29 - sh; ++k) if (basis[k] && isE[k]) { be = k; break; }
            cur = V;
            for (int k = 29 - sh; k >= 0; --k) {
                if (!basis[k]) continue;
                if (k == be) cur ^= basis[k];                       // 强制包含
                else if (!((cur >> k) & 1)) cur ^= basis[k];
            }
        }
        long long cand = (cur << sh) | ((1LL << sh) - 1);
        if (cand > ans) ans = cand;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> L(n), R(n);
        for (auto& x : L) cin >> x;
        for (auto& x : R) cin >> x;
        cout << solve(n, L, R) << '\n';
    }
}
