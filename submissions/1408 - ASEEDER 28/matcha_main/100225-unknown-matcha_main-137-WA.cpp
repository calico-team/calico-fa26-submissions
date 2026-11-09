#include <iostream>
#include <vector>
using namespace std;

// 状态：0 = 同时受 L、R 约束（前缀与 L、R 都相同）
//       1 = 只受 L 约束（已选前缀 > R 的前缀不可能，这里表示低位必须 >= L 的低位）
//       2 = 只受 R 约束（低位必须 <= R 的低位）
// 一旦某个区间变为"完全自由"，剩余所有低位都可以取 1，直接结束。
long long solve(int n, const vector<long long>& L, const vector<long long>& R) {
    vector<int> st(n, 0);
    long long ans = 0;
    for (int k = 29; k >= 0; --k) {
        int parity = 0, flex = 0, idx = -1;
        for (int i = 0; i < n; ++i) {
            int lb = (L[i] >> k) & 1, rb = (R[i] >> k) & 1;
            if (st[i] == 0) {
                if (lb == rb) parity ^= lb;
                else { ++flex; idx = i; }
            } else if (st[i] == 1) {
                if (lb == 1) parity ^= 1;
                else { ++flex; idx = i; }
            } else {
                if (rb == 1) { ++flex; idx = i; }
            }
        }
        if (flex >= 2) {               // 两个可选区间 => 从第 k 位起全部取 1
            ans |= (1LL << (k + 1)) - 1;
            break;
        }
        if (flex == 0) {               // 没有选择，第 k 位由奇偶性决定
            ans |= (long long)parity << k;
            continue;
        }
        // 恰好一个可选区间：让第 k 位为 1
        ans |= 1LL << k;
        int bit = parity ^ 1;
        if (st[idx] == 0) {
            st[idx] = (bit == 0) ? 1 : 2;
        } else if (st[idx] == 1) {
            if (bit == 1) { ans |= (1LL << k) - 1; break; }  // 变为自由
        } else {
            if (bit == 0) { ans |= (1LL << k) - 1; break; }  // 变为自由
        }
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
