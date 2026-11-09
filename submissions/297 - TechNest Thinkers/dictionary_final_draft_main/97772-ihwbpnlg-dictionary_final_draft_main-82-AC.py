import sys
from array import array

BITS = 30


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    for _ in range(t):
        n = int(data[pos]); pos += 1
        A = [int(v) - 1 for v in data[pos:pos + n]]; pos += n
        V = [int(v) for v in data[pos:pos + n]]; pos += n
        out.append(" ".join(map(str, solve(n, A, V))))
    sys.stdout.write("\n".join(out) + "\n")


def solve(n, A, V):
    # ---- find cycles of the functional graph ----
    state = [0] * n          # 0 = unseen, 1 = on current walk, 2 = done
    on_cycle = [False] * n
    cycles = []
    for s in range(n):
        if state[s]:
            continue
        path = []
        u = s
        while state[u] == 0:
            state[u] = 1
            path.append(u)
            u = A[u]
        if state[u] == 1:                      # found a new cycle
            idx = path.index(u)
            cyc = path[idx:]
            cycles.append(cyc)
            for c in cyc:
                on_cycle[c] = True
        for w in path:
            state[w] = 2

    # reverse edges for the trees hanging off cycles
    children = [[] for _ in range(n)]
    for u in range(n):
        if not on_cycle[u]:
            children[A[u]].append(u)

    # ---- binary trie pool (reset per component) ----
    size = BITS * (n + 1) + 2
    ch0 = array('i', [0]) * size
    ch1 = array('i', [0]) * size
    cnt = array('i', [0]) * size
    top = [0]

    def new_node():
        k = top[0]
        top[0] = k + 1
        ch0[k] = 0
        ch1[k] = 0
        cnt[k] = 0
        return k

    def update(root, x, d):
        node = root
        for b in range(BITS - 1, -1, -1):
            if (x >> b) & 1:
                nxt = ch1[node]
                if nxt == 0:
                    nxt = new_node()
                    ch1[node] = nxt
            else:
                nxt = ch0[node]
                if nxt == 0:
                    nxt = new_node()
                    ch0[node] = nxt
            node = nxt
            cnt[node] += d

    def best(root, x):
        # max of x ^ y over the values y stored in this trie (trie must be non-empty)
        node = root
        res = 0
        for b in range(BITS - 1, -1, -1):
            if (x >> b) & 1:
                want, other = ch0[node], ch1[node]
            else:
                want, other = ch1[node], ch0[node]
            if want and cnt[want] > 0:
                res |= 1 << b
                node = want
            else:
                node = other
        return res

    P = [0] * n
    ans = [0] * n

    for cyc in cycles:
        top[0] = 1                 # node 0 is the "null" child
        f_root = new_node()
        a_root = new_node()

        # P on the cycle: prefix XOR of values before each cycle node
        acc = 0
        for c in cyc:
            P[c] = acc
            acc ^= V[c]
            update(f_root, acc, 1)   # F(t) = XOR of V(c_0..c_t)
        C = acc                       # XOR of the whole cycle

        for c in cyc:
            ans[c] = max(best(f_root, P[c]), best(f_root, P[c] ^ C))

        # DFS each tree; ancestors (excluding the cycle node) live in a_root
        for c in cyc:
            stack = [(ch, False) for ch in children[c]]
            depth = 0
            while stack:
                u, leaving = stack.pop()
                if leaving:
                    update(a_root, P[u], -1)
                    depth -= 1
                    continue
                pu = V[u] ^ P[A[u]]
                P[u] = pu
                r = max(best(f_root, pu), best(f_root, pu ^ C))
                if depth:
                    q = best(a_root, pu)
                    if q > r:
                        r = q
                ans[u] = r
                if children[u]:
                    update(a_root, pu, 1)
                    depth += 1
                    stack.append((u, True))
                    for ch in children[u]:
                        stack.append((ch, False))
    return ans


main()