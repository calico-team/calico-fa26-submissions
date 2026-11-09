import sys
from array import array
import numpy as np


def solve(N, A, V):
    A = [a - 1 for a in A]
    state = [0] * N
    on_cycle = [False] * N
    cycles = []
    for st in range(N):
        if state[st] == 0:
            path = []
            cur = st
            while state[cur] == 0:
                state[cur] = 1
                path.append(cur)
                cur = A[cur]
            if state[cur] == 1:
                idx = path.index(cur)
                cyc = path[idx:]
                cycles.append(cyc)
                for x in cyc:
                    on_cycle[x] = True
            for x in path:
                state[x] = 2

    head = [-1] * N
    nxt = [-1] * N
    for i in range(N):
        if not on_cycle[i]:
            nxt[i] = head[A[i]]
            head[A[i]] = i

    # static cycle sets + queries
    keys = []
    q_val = []
    q_cid = []
    q_node = []
    P = [0] * N  # xor prefix of the root cycle node
    for cid, cyc in enumerate(cycles):
        L = len(cyc)
        pre = [0] * (L + 1)
        for r in range(L):
            pre[r + 1] = pre[r] ^ V[cyc[r]]
        C = pre[L]
        base = cid << 30
        for r in range(L):
            keys.append(base | pre[r])
            keys.append(base | (pre[r] ^ C))
        for s in range(L):
            c = cyc[s]
            P[c] = pre[s]
            q_val.append(pre[s])
            q_cid.append(cid)
            q_node.append(c)

    # dynamic trie for tree ancestors
    cap = 30 * N + 5
    ch = array('i', [0]) * (2 * cap)
    cnt = array('i', [0]) * cap
    nn = [1]

    def add(x, d):
        node = 0
        for b in range(29, -1, -1):
            idx = 2 * node + ((x >> b) & 1)
            nx = ch[idx]
            if not nx:
                nx = nn[0]
                nn[0] += 1
                ch[idx] = nx
            node = nx
            cnt[node] += d

    def best(q):
        node = 0
        res = 0
        for b in range(29, -1, -1):
            qb = (q >> b) & 1
            nx = ch[2 * node + (qb ^ 1)]
            if nx and cnt[nx] > 0:
                res |= 1 << b
                node = nx
            else:
                node = ch[2 * node + qb]
        return res

    D = [0] * N
    dyn = [0] * N
    for cyc in cycles:
        for c in cyc:
            if head[c] == -1:
                continue
            add(0, 1)
            stack = []
            ch_ = head[c]
            while ch_ != -1:
                stack.append(ch_)
                ch_ = nxt[ch_]
            while stack:
                x = stack.pop()
                if x >= 0:
                    D[x] = V[x] ^ D[A[x]]
                    P[x] = P[A[x]]
                    add(D[x], 1)
                    dyn[x] = best(D[x])
                    stack.append(~x)
                    y = head[x]
                    while y != -1:
                        stack.append(y)
                        y = nxt[y]
                else:
                    add(D[~x], -1)
            add(0, -1)

    # add tree-node static queries
    cid_of = [0] * N
    for cid, cyc in enumerate(cycles):
        for c in cyc:
            cid_of[c] = cid
    for i in range(N):
        if not on_cycle[i]:
            # find root cycle id by climbing (memoized)
            pass
    # compute cycle id for tree nodes in topological order (iterative)
    for i in range(N):
        if on_cycle[i] or cid_of[i] != 0 or False:
            pass
    known = [on_cycle[i] for i in range(N)]
    for i in range(N):
        if not known[i]:
            path = []
            cur = i
            while not known[cur]:
                path.append(cur)
                cur = A[cur]
            r = cid_of[cur]
            for x in path:
                cid_of[x] = r
                known[x] = True
    for i in range(N):
        if not on_cycle[i]:
            q_val.append(D[i] ^ P[i])
            q_cid.append(cid_of[i])
            q_node.append(i)

    dinosauraus = [0] * N
    arr = np.array(keys, dtype=np.int64)
    arr.sort()
    qv = np.array(q_val, dtype=np.int64)
    qc = np.array(q_cid, dtype=np.int64)
    prefix = qc << 30
    M = len(arr)
    for b in range(29, -1, -1):
        qb = (qv >> b) & 1
        target = prefix | ((qb ^ 1) << b)
        i = np.searchsorted(arr, target, side='left')
        ic = np.minimum(i, M - 1)
        ok = (i < M) & (arr[ic] < target + (1 << b))
        prefix = np.where(ok, target, prefix | (qb << b))
    res = ((prefix & ((1 << 30) - 1)) ^ qv).tolist()
    for k in range(len(res)):
        node = q_node[k]
        v = res[k]
        if not on_cycle[node] and dyn[node] > v:
            v = dyn[node]
        dinosauraus[node] = v
    return dinosauraus


def read_your_input():
    data = sys.stdin.buffer.read().split()
    pos = 0
    T = int(data[pos]); pos += 1
    out = []
    for _ in range(T):
        N = int(data[pos]); pos += 1
        A = list(map(int, data[pos:pos + N])); pos += N
        V = list(map(int, data[pos:pos + N])); pos += N
        out.append(" ".join(map(str, solve(N, A, V))))
    print("\n".join(out))


if __name__ == "__main__":
    read_your_input()