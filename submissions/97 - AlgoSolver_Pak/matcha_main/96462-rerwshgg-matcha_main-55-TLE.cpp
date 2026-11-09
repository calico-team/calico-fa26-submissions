#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const int FULL = 1;
const int NULL_NODE = 0;
const int B = 29; // 0..29

struct TrieNode {
    int ch[2];
    TrieNode() { ch[0] = ch[1] = NULL_NODE; }
};

vector<TrieNode> trie;

// naya node banao
int newNode() {
    trie.push_back(TrieNode());
    return (int)trie.size() - 1;
}

// interval [L,R] ka trie banao
int buildInterval(int L, int R, int bit) {
    if (L > R) return NULL_NODE;
    if (bit < 0) return FULL;
    int total = (1 << (bit + 1)) - 1;
    if (L == 0 && R == total) return FULL;
    int mid = (1 << bit);
    int left = NULL_NODE, right = NULL_NODE;
    // bit 0 wala hissa : [0, mid-1]
    if (L < mid) {
        int nl = L;
        int nr = R < mid - 1 ? R : mid - 1;
        left = buildInterval(nl, nr, bit - 1);
    }
    // bit 1 wala hissa : [mid, 2*mid-1]
    if (R >= mid) {
        int nl = L > mid ? L - mid : 0;
        int nr = R - mid;
        right = buildInterval(nl, nr, bit - 1);
    }
    if (left == NULL_NODE && right == NULL_NODE) return NULL_NODE;
    if (left == FULL && right == FULL) return FULL;
    int id = newNode();
    trie[id].ch[0] = left;
    trie[id].ch[1] = right;
    return id;
}

unordered_map<long long,int> memoUnion, memoXor;

int uniteSets(int a, int b, int bit) {
    if (a == NULL_NODE) return b;
    if (b == NULL_NODE) return a;
    if (a == FULL || b == FULL) return FULL;
    if (bit < 0) return FULL;
    if (a == b) return a;
    long long key = ((long long)a << 32) | (unsigned int)b;
    auto it = memoUnion.find(key);
    if (it != memoUnion.end()) return it->second;
    int a0 = trie[a].ch[0], a1 = trie[a].ch[1];
    int b0 = trie[b].ch[0], b1 = trie[b].ch[1];
    int c0 = uniteSets(a0, b0, bit - 1);
    int c1 = uniteSets(a1, b1, bit - 1);
    int res;
    if (c0 == FULL && c1 == FULL) res = FULL;
    else {
        res = newNode();
        trie[res].ch[0] = c0;
        trie[res].ch[1] = c1;
    }
    memoUnion[key] = res;
    return res;
}

int xorSets(int a, int b, int bit) {
    if (a == NULL_NODE || b == NULL_NODE) return NULL_NODE;
    if (a == FULL || b == FULL) return FULL;
    if (bit < 0) return FULL;
    long long key = ((long long)a << 32) | (unsigned int)b;
    auto it = memoXor.find(key);
    if (it != memoXor.end()) return it->second;
    int a0 = trie[a].ch[0], a1 = trie[a].ch[1];
    int b0 = trie[b].ch[0], b1 = trie[b].ch[1];
    int left = uniteSets(xorSets(a0, b0, bit - 1), xorSets(a1, b1, bit - 1), bit - 1);
    int right = uniteSets(xorSets(a0, b1, bit - 1), xorSets(a1, b0, bit - 1), bit - 1);
    int res;
    if (left == FULL && right == FULL) res = FULL;
    else {
        res = newNode();
        trie[res].ch[0] = left;
        trie[res].ch[1] = right;
    }
    memoXor[key] = res;
    return res;
}

// trie me xorTag lagao (singleton ke liye)
int applyXor(int node, int tag, int bit) {
    if (node == NULL_NODE) return NULL_NODE;
    if (node == FULL) return FULL;
    if (bit < 0) return node;
    int b = (tag >> bit) & 1;
    if (b == 0) {
        int id = newNode();
        trie[id].ch[0] = applyXor(trie[node].ch[0], tag, bit - 1);
        trie[id].ch[1] = applyXor(trie[node].ch[1], tag, bit - 1);
        return id;
    } else {
        int id = newNode();
        trie[id].ch[0] = applyXor(trie[node].ch[1], tag, bit - 1);
        trie[id].ch[1] = applyXor(trie[node].ch[0], tag, bit - 1);
        return id;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        cin >> N;
        vector<int> L(N), R(N);
        for (int i = 0; i < N; i++) cin >> L[i];
        for (int i = 0; i < N; i++) cin >> R[i];

        trie.clear();
        trie.reserve(10000);
        trie.push_back(TrieNode()); // 0 = null
        trie.push_back(TrieNode()); // 1 = full

        // shuru me set = {0}
        int cur = newNode();
        int tmp = cur;
        for (int b = B; b >= 0; --b) {
            int nxt = newNode();
            trie[tmp].ch[0] = nxt;
            tmp = nxt;
        }
        

        int xorTag = 0;
        bool isFull = false;

        for (int i = 0; i < N; i++) {
            if (L[i] == R[i]) {
                xorTag ^= L[i];
                continue;
            }
            
            if (xorTag != 0) {
                cur = applyXor(cur, xorTag, B);
                xorTag = 0;
            }
            if (isFull) continue;
            // is interval ka trie
            memoXor.clear();
            memoUnion.clear();
            int bTrie = buildInterval(L[i], R[i], B);
            cur = xorSets(cur, bTrie, B);
            if (cur == FULL) isFull = true;
        }
        if (xorTag != 0) {
            cur = applyXor(cur, xorTag, B);
        }

        int ans = 0;
        if (cur == FULL) {
            ans = (1 << 30) - 1;
        } else {
            int node = cur;
            for (int b = B; b >= 0; --b) {
                if (node == FULL) {
                    ans |= (1 << (b + 1)) - 1;
                    break;
                }
                int c1 = trie[node].ch[1];
                int c0 = trie[node].ch[0];
                if (c1 != NULL_NODE) {
                    ans |= (1 << b);
                    node = c1;
                } else {
                    node = c0;
                }
                if (node == FULL) {
                    ans |= (1 << b) - 1;
                    break;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}