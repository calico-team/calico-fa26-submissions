#include <bits/stdc++.h>
using namespace std;

struct Node {
    int ch[2];
    Node(int a = -1, int b = -1) { ch[0] = a; ch[1] = b; }
};

// full node is 0, empty is -1
struct Trie {
    vector<Node> t;
    Trie() { t.emplace_back(0, 0); } // 0 = full
};

int make_node(vector<Node> &nt, int l, int r) {
    if (l == 0 && r == 0) return 0;
    if (l == -1 && r == -1) return -1;
    nt.emplace_back(l, r);
    return (int)nt.size() - 1;
}

// ---------- interval trie ----------
int build_interval(vector<Node> &it, long long L, long long R, int bit) {
    if (L > R) return -1;
    if (bit < 0) return 0;
    long long full = (bit == 62 ? (long long)4e18 : ((1LL << (bit + 1)) - 1));
    // for bit up to 29, 1LL<<(bit+1) fits
    if (bit <= 29) full = (1LL << (bit + 1)) - 1;
    if (L == 0 && R == full) return 0;
    long long mid = 1LL << bit;
    int left = -1, right = -1;
    if (L < mid) left = build_interval(it, L, min(R, mid - 1), bit - 1);
    if (R >= mid) right = build_interval(it, max(L, mid) - mid, R - mid, bit - 1);
    it.emplace_back(left, right);
    return (int)it.size() - 1;
}

// forward decls for memoised combine / union
struct Solver {
    Trie *oldT = nullptr;
    vector<Node> *intervalT = nullptr;
    vector<Node> newT;
    unordered_map<long long,int> memoC;
    unordered_map<long long,int> memoU;

    int union_nodes(int a, int b, int bit) {
        if (a == 0 || b == 0) return 0;
        if (a == -1) return b;
        if (b == -1) return a;
        if (a == b) return a;
        if (bit < 0) return 0;
        long long key = ((long long)a << 32) | (unsigned int)b;
        // bit is implicit (depth determined by recursion), but a,b from same level
        // use combined key with bit
        long long key2 = key * 31 + (bit + 1);
        auto it = memoU.find(key2);
        if (it != memoU.end()) return it->second;
        int a0 = newT[a].ch[0], a1 = newT[a].ch[1];
        int b0 = newT[b].ch[0], b1 = newT[b].ch[1];
        int n0 = union_nodes(a0, b0, bit - 1);
        int n1 = union_nodes(a1, b1, bit - 1);
        int res = make_node(newT, n0, n1);
        memoU[key2] = res;
        return res;
    }

    int combine_nodes(int s, int in, int bit) {
        if (s == 0 || in == 0) return 0;
        if (s == -1 || in == -1) return -1;
        if (bit < 0) return 0;
        long long key = ((long long)s << 32) | (unsigned int)in;
        auto it = memoC.find(key);
        if (it != memoC.end()) return it->second;
        int s0 = (*