// CALICO Fall '26  Problem 6: Average Berkeley CS Major (schedule)
// 题意：M 个学期，每学期最多修 K 门课。N 门课，每门课 i 有前置课 P_i（P_i=0 表示无前置）。
//       前置课必须在"更早的学期"修完（不能同一学期）。求 M 学期内最多能修几门课。
//       保证：前置关系构成森林（无环），且任意前置链长度 <= 1000。
//
// 核心结论（Hu's algorithm / 关键路径优先）：
//   这是树形优先约束 + 每学期容量 K 的并行调度问题。对树形单元时间任务，
//   每学期优先选「tail 最大」的可用课程（tail = 从该课往下到叶子、含自身的最长链长）
//   是最优调度（T. C. Hu, 1961）。
//
//   为什么不是"深度（到根的距离）优先"？
//   深度只反映"它自身最早何时能修"，而 tail 反映"它后面还卡着多长的必经链"。
//   优先处理 tail 长的（即更靠近"关键路径"底部的）课程，才不会让后面的链来不及完成。
//
// 实现：大根堆（按 tail）维护"当前学期可选"的课程；每学期弹出至多 K 个，
//       其子课程延迟到下一学期入堆（前置与课程不能同学期）。
// 复杂度：O(N log N)，与 M 无关。
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while(T--){
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N + 1, 0);
        for(int i = 1; i <= N; i++) cin >> P[i];

        // 建子节点列表（森林）
        vector<vector<int>> ch(N + 1);
        for(int i = 1; i <= N; i++) if(P[i] != 0) ch[P[i]].push_back(i);

        // tail[i] = 从 i 到叶子的最长链长度（含 i 自身），记忆化 DFS
        vector<int> tail(N + 1, 0);
        function<int(int)> getTail = [&](int x) -> int {
            if(tail[x]) return tail[x];
            int m = 0;
            for(int c : ch[x]) m = max(m, getTail(c));
            return tail[x] = m + 1;
        };
        for(int i = 1; i <= N; i++) getTail(i);

        // 大根堆：当前学期可选的课程，按 tail 降序
        priority_queue<pair<int,int>> ready; // (tail, id)
        for(int i = 1; i <= N; i++) if(P[i] == 0) ready.push({tail[i], i});

        long long ans = 0;
        vector<int> pending; // 本学期选中课程的子课程，延迟到下一学期才可选

        for(int sem = 0; sem < M; sem++){
            int take = min(K, (int)ready.size());
            if(take == 0) break; // 没有课可修（或全修完）

            pending.clear();
            for(int t = 0; t < take; t++){
                int id = ready.top().second;
                ready.pop();
                ans++;
                for(int s : ch[id]) pending.push_back(s);
            }
            // 下一学期开始前，把这些子课程放入可选堆
            for(int s : pending) ready.push({tail[s], s});
        }
        cout << ans << "\n";
    }
    return 0;
}
