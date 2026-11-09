/*
 * Problem: galaxy2 (CALICO Fall '26) — 兼容 C++98
 *
 * 状态图: (r, c, md), md 0=蓝 1=红; 移动+旋转均为无向边, 每条代价 1。
 * 查询 (s,e,K): min{ dist((s,蓝),(e,m)) : m 与 e 相容 } <= K ?
 *
 * 四层加速:
 *  A. 一次遍历标号所有连通分量 (BFS 中直接写 comp), 并记录每个分量
 *     "代表源" 的距离 d1[md][r][c]。
 *  B. 三角不等式快判: |d1[s]-d1[e]| <= dist <= d1[s]+d1[e]
 *     (取相容 m 的最优组合)。下界>K => NO; 上界<=K => YES。
 *     分量大小-1 也可作为上界补充。
 *  C. 图无向 => 查询可在起点端或终点端做 BFS。按端点频次贪心选端,
 *     每个被选端点做一次 BFS 服务其全部查询 (排序+二分分组, 无 O(Q^2))。
 *  D. BFS 限深 (组内 maxK) + 组内目标全部到达即提前终止 (tflag+pending)。
 */
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 12, MAXM = 4005;
int N, M;
char grid[MAXN][MAXM];
int dist_[2][MAXN][MAXM];
int stamp_[2][MAXN][MAXM];
int comp_[2][MAXN][MAXM];
int d1_[2][MAXN][MAXM];
long long csize[2 * MAXN * MAXM];
int qnode[2 * MAXN * MAXM];
int tflag[2][MAXN][MAXM];
int cur_stamp = 0, tcur = 0, pending_ = 0;

const int dr[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

inline bool walkable(int r, int c, int md) {
    char t = grid[r][c];
    return t == '.' || (t == 'R' && md == 1) || (t == 'B' && md == 0);
}
inline int encs(int md, int r, int c) { return (md * MAXN + r) * MAXM + c; }

// 标号 BFS: 从 (md0,r0,c0) 出发, 把整个分量标 compId, 记录 d1
void labelBfs(int md0, int r0, int c0, int compId) {
    cur_stamp++;
    int head = 0, tail = 0;
    stamp_[md0][r0][c0] = cur_stamp;
    comp_[md0][r0][c0] = compId;
    d1_[md0][r0][c0] = 0;
    csize[compId] = 1;
    qnode[tail++] = encs(md0, r0, c0);
    while (head < tail) {
        int s = qnode[head++];
        int md = s / (MAXN * MAXM), rc = s % (MAXN * MAXM);
        int r = rc / MAXM, c = rc % MAXM;
        int d = d1_[md][r][c];
        if (grid[r][c] == '.') {                 // 旋转
            int nm = 1 - md;
            if (stamp_[nm][r][c] != cur_stamp) {
                stamp_[nm][r][c] = cur_stamp;
                comp_[nm][r][c] = compId;
                d1_[nm][r][c] = d + 1;
                csize[compId]++;
                qnode[tail++] = (nm * MAXN + r) * MAXM + c;
            }
        }
        for (int k = 0; k < 4; k++) {             // 移动
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            if (!walkable(nr, nc, md)) continue;
            if (stamp_[md][nr][nc] != cur_stamp) {
                stamp_[md][nr][nc] = cur_stamp;
                comp_[md][nr][nc] = compId;
                d1_[md][nr][nc] = d + 1;
                csize[compId]++;
                qnode[tail++] = (md * MAXN + nr) * MAXM + nc;
            }
        }
    }
}

// 查询 BFS: 多源, 限深 limit (0=不限), targets 全到达即停 (NULL=不停)
void queryBfs(const vector<int>& srcs, int limit, const vector<int>* targets) {
    cur_stamp++;
    pending_ = 0;
    if (targets) {
        tcur++;
        for (size_t i = 0; i < targets->size(); i++) {
            int t = (*targets)[i];
            int tmd = t / (MAXN * MAXM), trc = t % (MAXN * MAXM);
            int tr = trc / MAXM, tc = trc % MAXM;
            if (tflag[tmd][tr][tc] != tcur) {
                tflag[tmd][tr][tc] = tcur;
                pending_++;
            }
        }
    }
    int head = 0, tail = 0;
    for (size_t i = 0; i < srcs.size(); i++) {
        int s = srcs[i];
        int md = s / (MAXN * MAXM), rc = s % (MAXN * MAXM);
        int r = rc / MAXM, c = rc % MAXM;
        if (!walkable(r, c, md)) continue;
        stamp_[md][r][c] = cur_stamp;
        dist_[md][r][c] = 0;
        qnode[tail++] = s;
        if (targets && tflag[md][r][c] == tcur) pending_--;
    }
    if (targets && pending_ <= 0) return;
    while (head < tail) {
        int s = qnode[head++];
        int md = s / (MAXN * MAXM), rc = s % (MAXN * MAXM);
        int r = rc / MAXM, c = rc % MAXM;
        int d = dist_[md][r][c];
        if (limit > 0 && d >= limit) continue;
        if (grid[r][c] == '.') {
            int nm = 1 - md;
            if (stamp_[nm][r][c] != cur_stamp) {
                stamp_[nm][r][c] = cur_stamp;
                dist_[nm][r][c] = d + 1;
                qnode[tail++] = (nm * MAXN + r) * MAXM + c;
                if (targets && tflag[nm][r][c] == tcur && --pending_ == 0) return;
            }
        }
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            if (!walkable(nr, nc, md)) continue;
            if (stamp_[md][nr][nc] != cur_stamp) {
                stamp_[md][nr][nc] = cur_stamp;
                dist_[md][nr][nc] = d + 1;
                qnode[tail++] = (md * MAXN + nr) * MAXM + nc;
                if (targets && tflag[md][nr][nc] == tcur && --pending_ == 0) return;
            }
        }
    }
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int Q;
        scanf("%d %d %d", &N, &M, &Q);
        for (int i = 0; i < N; i++) scanf("%s", grid[i]);

        // ---- A. 分量标号 + 代表源距离 (一次 BFS 标一个分量, 总 O(NM)) ----
        int ncomp = 0;
        memset(comp_, -1, sizeof(comp_));
        for (int r = 0; r < N; r++)
            for (int c = 0; c < M; c++)
                for (int md0 = 0; md0 < 2; md0++) {
                    if (comp_[md0][r][c] != -1) continue;
                    if (!walkable(r, c, md0)) continue;
                    labelBfs(md0, r, c, ncomp++);
                }

        vector<int> rs(Q), cs(Q), re(Q), ce(Q);
        vector<long long> K(Q);          // K <= 1e9, 用 int 读再转 (兼容旧 MinGW)
        for (int i = 0; i < Q; i++) {
            int kTmp;
            scanf("%d %d %d %d %d", &rs[i], &cs[i], &re[i], &ce[i], &kTmp);
            K[i] = kTmp;
        }

        // ---- B. 快判: 可达性 + 三角不等式 + 分量大小 ----
        vector<char> ans(Q, 2);        // 2 未决
        vector<int> und;
        for (int i = 0; i < Q; i++) {
            int sComp = comp_[0][rs[i]][cs[i]];
            int sD = d1_[0][rs[i]][cs[i]];
            char te = grid[re[i]][ce[i]];
            long long bestLow = -1, bestUp = -1;   // min over 相容 m
            int mA = (te == 'R') ? 1 : 0;
            int mB = (te == '.') ? 1 : -1;
            int ms[2] = {mA, mB};
            for (int t = 0; t < 2; t++) {
                if (t == 1 && mB == -1) break;
                int m = ms[t];
                if (comp_[m][re[i]][ce[i]] != sComp) continue;   // 该模式不可达
                int eD = d1_[m][re[i]][ce[i]];
                long long low = sD - eD; if (low < 0) low = -low;
                long long up = (long long)sD + eD;
                if (csize[sComp] - 1 < up) up = csize[sComp] - 1;
                if (bestLow < 0 || low < bestLow) bestLow = low;
                if (bestUp < 0 || up < bestUp) bestUp = up;
            }
            if (bestUp < 0) { ans[i] = 0; continue; }       // 完全不可达
            if (bestLow > K[i]) { ans[i] = 0; continue; }    // 下界 > K
            if (bestUp <= K[i]) { ans[i] = 1; continue; }    // 上界 <= K
            und.push_back(i);
        }

        // ---- C. 贪心端点分组 (排序 + 二分, 无 O(Q^2)) ----
        if (!und.empty()) {
            // 键打包: r<<20 | c  (c < 4000 < 2^12? c<4000 需要 12 位; r<10 4 位)
            vector<long long> allKeys;
            allKeys.reserve(und.size() * 2);
            vector<long long> skeyOf(und.size()), ekeyOf(und.size());
            for (size_t i = 0; i < und.size(); i++) {
                int qi = und[i];
                skeyOf[i] = ((long long)rs[qi] << 20) | cs[qi];
                ekeyOf[i] = ((long long)re[qi] << 20) | ce[qi];
                allKeys.push_back(skeyOf[i]);
                allKeys.push_back(ekeyOf[i]);
            }
            sort(allKeys.begin(), allKeys.end());
            // 每个查询: 起点频次 vs 终点频次
            vector< pair<long long, char> > gassign(und.size()); // (gkey, isStart)
            for (size_t i = 0; i < und.size(); i++) {
                long long sk = skeyOf[i], ek = ekeyOf[i];
                long long sf = upper_bound(allKeys.begin(), allKeys.end(), sk) -
                               lower_bound(allKeys.begin(), allKeys.end(), sk);
                long long ef = upper_bound(allKeys.begin(), allKeys.end(), ek) -
                               lower_bound(allKeys.begin(), allKeys.end(), ek);
                if (sf >= ef) gassign[i] = make_pair(sk, 1);
                else         gassign[i] = make_pair(ek, 0);
            }
            // 按 (gkey, isStart) 排序分组
            vector< pair< pair<long long, char>, int > > gd(und.size());
            for (size_t i = 0; i < und.size(); i++)
                gd[i] = make_pair(gassign[i], (int)i);
            sort(gd.begin(), gd.end());

            size_t i = 0;
            while (i < gd.size()) {
                size_t j = i;
                while (j < gd.size() &&
                       gd[j].first.first == gd[i].first.first &&
                       gd[j].first.second == gd[i].first.second) j++;
                // 组 [i, j): 源端点
                long long gkey = gd[i].first.first;
                bool isStart = gd[i].first.second == 1;
                int keyr = (int)(gkey >> 20), keyc = (int)(gkey & 0xFFFFF);
                long long maxK = 0;
                vector<int> qis;
                for (size_t t = i; t < j; t++) {
                    int qi = und[gd[t].second];
                    qis.push_back(qi);
                    if (K[qi] > maxK) maxK = K[qi];
                }
                // BFS 源与目标
                vector<int> srcs, targets;
                if (isStart) {
                    srcs.push_back(encs(0, keyr, keyc));
                    for (size_t t = 0; t < qis.size(); t++) {
                        int qi = qis[t];
                        char te2 = grid[re[qi]][ce[qi]];
                        if (te2 != 'R') targets.push_back(encs(0, re[qi], ce[qi]));
                        if (te2 != 'B') targets.push_back(encs(1, re[qi], ce[qi]));
                    }
                } else {
                    char te2 = grid[keyr][keyc];
                    if (te2 != 'R') srcs.push_back(encs(0, keyr, keyc));
                    if (te2 != 'B') srcs.push_back(encs(1, keyr, keyc));
                    for (size_t t = 0; t < qis.size(); t++) {
                        int qi = qis[t];
                        targets.push_back(encs(0, rs[qi], cs[qi]));
                    }
                }
                int limit = (maxK > 100000000) ? 0 : (int)maxK;  // K 上界内限深
                queryBfs(srcs, limit, &targets);
                for (size_t t = 0; t < qis.size(); t++) {
                    int qi = qis[t];
                    int best = 0x3f3f3f3f;
                    if (isStart) {
                        char te2 = grid[re[qi]][ce[qi]];
                        if (te2 != 'R' && stamp_[0][re[qi]][ce[qi]] == cur_stamp)
                            if (dist_[0][re[qi]][ce[qi]] < best)
                                best = dist_[0][re[qi]][ce[qi]];
                        if (te2 != 'B' && stamp_[1][re[qi]][ce[qi]] == cur_stamp)
                            if (dist_[1][re[qi]][ce[qi]] < best)
                                best = dist_[1][re[qi]][ce[qi]];
                    } else {
                        if (stamp_[0][rs[qi]][cs[qi]] == cur_stamp)
                            best = dist_[0][rs[qi]][cs[qi]];
                    }
                    ans[qi] = (best <= K[qi]) ? 1 : 0;
                }
                i = j;
            }
        }

        string out;
        out.reserve((size_t)Q * 4 + 8);
        for (int i = 0; i < Q; i++)
            out += (ans[i] == 1) ? "YES\n" : "NO\n";
        fputs(out.c_str(), stdout);
    }
    return 0;
}
