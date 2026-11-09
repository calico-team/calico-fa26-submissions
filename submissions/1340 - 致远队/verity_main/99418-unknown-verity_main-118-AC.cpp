#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 解决单个测试用例
void solve() {
    int N, K;
    if (!(cin >> N >> K)) return;

    vector<char> chars(K);
    for (int i = 0; i < K; ++i) {
        cin >> chars[i];
    }

    // ans 存储最终确定的字符串，初始化为占位符，例如 '?'
    // 但实际上我们可以直接用 string 并初始化为任意字符，后续覆盖
    string ans(N, '?'); 
    
    bool solved = false;

    // 我们最多进行 K 轮探测
    for (int c_idx = 0; c_idx < K; ++c_idx) {
        char current_char = chars[c_idx];
        
        // 构造猜测字符串：所有位置都填 current_char
        string guess(N, current_char);
        
        // 输出猜测
        cout << guess << endl;
        // 刷新缓冲区，这对于交互题至关重要
        cout.flush();

        string response;
        cin >> response;

        // 检查是否猜对
        if (response == "CORRECT") {
            solved = true;
            break;
        }

        // 解析反馈
        // 反馈字符串长度应为 N
        // 如果 response[i] 不是 '_'，说明 guess[i] (即 current_char) 是正确的
        for (int i = 0; i < N; ++i) {
            if (response[i] != '_') {
                ans[i] = response[i];
            }
        }
    }

    // 如果循环结束后还没有得到 CORRECT
    // 此时 ans 中可能还有 '?' (如果 K 次探测中没有覆盖到某些位的正确字符，
    // 但实际上，如果前 K-1 个字符都不对，那第 K 个字符一定对。
    // 我们的循环跑了 K 次。
    // 如果在第 K 次循环中，response 不是 CORRECT，
    // 那么对于那些仍然是 '?' 的位置，它们一定是最后一个字符吗？
    // 不，如果在第 K 次循环（最后一个字符）中，
    // 假设隐藏串是 "AB", chars=['A','B']。
    // Round 1 ('A'): guess "AA". Resp "A_". ans becomes "A?".
    // Round 2 ('B'): guess "BB". Resp "_B". ans becomes "AB".
    // 循环结束。solved 仍为 false。
    // 我们需要最后提交一次完整的 ans。
    
    if (!solved) {
        // 理论上，经过 K 轮全字符填充猜测，所有位置都应该被确定。
        // 因为每个位置的真实字符必然在 chars 列表中。
        // 当轮到该真实字符的那一轮时，该位置会返回该字符，从而被记录。
        
        // 提交最终确定的字符串
        cout << ans << endl;
        cout.flush();
        
        string final_response;
        cin >> final_response;
        // 应该是 CORRECT
    }
}

int main() {
    // 优化 IO 操作
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
