
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 12, MAXM = 4005;
const int MAXSTATES = 2 * MAXN * MAXM;          
const int MAXLM = 16;                            
const int LM_BUDGET = 64;                       
const long long BIG_COMP = 500;               

int N, M;
char grid[MAXN][MAXM];
int dist_[2][MAXN][MAXM];
int stamp_[2][MAXN][MAXM];
int comp_[2][MAXN][MAXM];
int d1_[2][MAXN][MAXM];                          
long long csize[MAXSTATES];
int qnode[MAXSTATES];
int tflag[2][MAXN][MAXM];
int cur_stamp = 0, tcur = 0, pending_ = 0;

// 路标距离池: dl_pool[slot][md][r][c]
int dl_pool[LM_BUDGET][2][MAXN][MAXM];
int lm_slot = 0;                                 
vector< vector<int> > compLm;                   

const int dr[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

inline bool walkable(int r, int c, int md) {
    char t = grid[r][c];
    return t == '.' || (t == 'R' && md == 1) || (t == 'B' && md == 0);
}
inline int encs(int md, int r, int c) { return (md * MAXN + r) * MAXM + c; }


void labelBfs(int md0, int r0, int c0, int compId) {
    cur_stamp++;
    int head = 0, tail = 0;
    stamp_[md0][r0][c0] = cur_stamp;
    comp_[md0][r0][c0] = compId;
    csize[compId] = 1;
    qnode[tail++] = encs(md0, r0, c0);
    while (head < tail) {
        int s = qnode[head++];
        int md = s / (MAXN * MAXM), rc = s % (MAXN * MAXM);
        int r = rc / MAXM, c = rc % MAXM;
        if (grid[r][c] == '.') {
            int nm = 1 - md;
            if (stamp_[nm][r][c] != cur_stamp) {
                stamp_[nm][r][c] = cur_stamp;
                comp_[nm][r][c] = compId;
                csize[compId]++;
                qnode[tail++] = (nm * MAXN + r) * MAXM + c;
            }
        }
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            if (!walkable(nr, nc, md)) continue;
            if (stamp_[md][nr][nc] != cur_stamp) {
                stamp_[md][nr][nc] = cur_stamp;
                comp_[md][nr][nc] = compId;
                csize[compId]++;
                qnode[tail++] = (md * MAXN + nr) * MAXM + nc;
            }
        }
    }
}


void lmBfs(int md0, int r0, int c0, int slot) {
    int* D = &dl_pool[slot][0][0][0];            
    cur_stamp++;
    int head = 0, tail = 0;
    stamp_[md0][r0][c0] = cur_stamp;
    D[(md0 * MAXN + r0) * MAXM + c0] = 0;
    qnode[tail++] = encs(md0, r0, c0);
    while (head < tail) {
        int s = qnode[head++];
        int md = s / (MAXN * MAXM), rc = s % (MAXN * MAXM);
        int r = rc / MAXM, c = rc % MAXM;
        int d = D[(md * MAXN + r) * MAXM + c];
        if (grid[r][c] == '.') {
            int nm = 1 - md;
            if (stamp_[nm][r][c] != cur_stamp) {
                stamp_[nm][r][c] = cur_stamp;
                D[(nm * MAXN + r) * MAXM + c] = d + 1;
                qnode[tail++] = (nm * MAXN + r) * MAXM + c;
            }
        }
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            if (!walkable(nr, nc, md)) continue;
            if (stamp_[md][nr][nc] != cur_stamp) {
                stamp_[md][nr][nc] = cur_stamp;
                D[(md * MAXN + nr) * MAXM + nc] = d + 1;
                qnode[tail++] = (md * MAXN + nr) * MAXM + nc;
            }
        }
    }
}

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

        // ---- A. 分量标号 ----
        int ncomp = 0;
        memset(comp_, -1, sizeof(comp_));
        vector< pair<int,int> > compSeed;          // (md, state) 每分量种子
        for (int r = 0; r < N; r++)
            for (int c = 0; c < M; c++)
                for (int md = 0; md < 2; md++) {
                    if (comp_[md][r][c] != -1) continue;
                    if (!walkable(r, c, md)) continue;
                    labelBfs(md, r, c, ncomp);
                    compSeed.push_back(make_pair(md, encs(md, r, c)));
                    ncomp++;
                }
        compLm.assign(ncomp, vector<int>());

        
        lm_slot = 0;
        for (int ci = 0; ci < ncomp; ci++) {
            if (csize[ci] < BIG_COMP) continue;                 
            if (lm_slot >= LM_BUDGET) break;
            
            int s0 = compSeed[ci].second;
            int m0 = s0 / (MAXN * MAXM), rc0 = s0 % (MAXN * MAXM);
            lmBfs(m0, rc0 / MAXM, rc0 % MAXM, lm_slot);
            compLm[ci].push_back(lm_slot++);
            
            for (int md = 0; md < 2; md++)
                for (int r = 0; r < N; r++)
                    for (int c = 0; c < M; c++)
                        if (comp_[md][r][c] == ci)
                            d1_[md][r][c] = dl_pool[compLm[ci][0]][md][r][c];
            while ((int)compLm[ci].size() < MAXLM &&
                   lm_slot < LM_BUDGET) {
                
                int bestD = -1, bestS = -1;
                for (int md = 0; md < 2; md++)
                    for (int r = 0; r < N; r++)
                        for (int c = 0; c < M; c++)
                            if (comp_[md][r][c] == ci &&
                                d1_[md][r][c] > bestD) {
                                bestD = d1_[md][r][c];
                                bestS = encs(md, r, c);
                            }
                if (bestD >= 0 && bestD <= 8) break;             
                int bm = bestS / (MAXN * MAXM), brc = bestS % (MAXN * MAXM);
                lmBfs(bm, brc / MAXM, brc % MAXM, lm_slot);
                int nslot = lm_slot++;
                compLm[ci].push_back(nslot);
                int* Dn = &dl_pool[nslot][0][0][0];
                for (int md = 0; md < 2; md++)
                    for (int r = 0; r < N; r++)
                        for (int c = 0; c < M; c++)
                            if (comp_[md][r][c] == ci) {
                                int v = (md * MAXN + r) * MAXM + c;
                                if (Dn[v] < d1_[md][r][c])
                                    d1_[md][r][c] = Dn[v];
                            }
            }
        }

        
        vector<int> rs(Q), cs(Q), re(Q), ce(Q);
        vector<long long> K(Q);
        for (int i = 0; i < Q; i++) {
            int kTmp;
            scanf("%d %d %d %d %d", &rs[i], &cs[i], &re[i], &ce[i], &kTmp);
            K[i] = kTmp;
        }

        
        vector<char> ans(Q, 2);
        vector<int> und;
        for (int i = 0; i < Q; i++) {
            int sComp = comp_[0][rs[i]][cs[i]];
            char te = grid[re[i]][ce[i]];
            int ms[2] = { (te == 'R') ? 1 : 0, (te == '.') ? 1 : -1 };
            long long minLow = -1, minUp = -1;      
            for (int t = 0; t < 2; t++) {
                if (t == 1 && ms[1] == -1) break;
                int m = ms[t];
                if (comp_[m][re[i]][ce[i]] != sComp) continue;   
                long long low = 0;
                long long up = csize[sComp] - 1;
                vector<int>& lms = compLm[sComp];
                for (size_t li = 0; li < lms.size(); li++) {
                    int a = dl_pool[lms[li]][0][rs[i]][cs[i]];
                    int b = dl_pool[lms[li]][m][re[i]][ce[i]];
                    long long lo2 = a - b; if (lo2 < 0) lo2 = -lo2;
                    if (lo2 > low) low = lo2;
                    long long up2 = (long long)a + b;
                    if (up2 < up) up = up2;
                }
                if (minLow < 0 || low < minLow) minLow = low;
                if (minUp < 0 || up < minUp) minUp = up;
            }
            if (minUp < 0) { ans[i] = 0; continue; }        
            if (minLow > K[i]) { ans[i] = 0; continue; }    
            if (minUp <= K[i]) { ans[i] = 1; continue; }    
            und.push_back(i);
        }

        //
        if (!und.empty()) {
            vector<long long> allKeys;
            allKeys.reserve(und.size() * 2);
            for (size_t i = 0; i < und.size(); i++) {
                int qi = und[i];
                allKeys.push_back(((long long)rs[qi] << 20) | cs[qi]);
                allKeys.push_back(((long long)re[qi] << 20) | ce[qi]);
            }
            sort(allKeys.begin(), allKeys.end());
            vector< pair<long long, char> > gassign(und.size());
            for (size_t i = 0; i < und.size(); i++) {
                int qi = und[i];
                long long sk = ((long long)rs[qi] << 20) | cs[qi];
                long long ek = ((long long)re[qi] << 20) | ce[qi];
                long long sf = upper_bound(allKeys.begin(), allKeys.end(), sk) -
                               lower_bound(allKeys.begin(), allKeys.end(), sk);
                long long ef = upper_bound(allKeys.begin(), allKeys.end(), ek) -
                               lower_bound(allKeys.begin(), allKeys.end(), ek);
                gassign[i] = (sf >= ef) ? make_pair(sk, (char)1)
                                        : make_pair(ek, (char)0);
            }
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
                int limit = (maxK > 100000000) ? 0 : (int)maxK;
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
