import sys
from array import array
from collections import deque


def batch_max_xor(vals, queries, maxb):
    """For each x in queries, return max over v in vals of (v ^ x)."""
    res = [0] * len(queries)
    if not queries:
        return res
    vals = list(set(vals))
    if not vals:
        return res
    # build a binary trie of vals level by level (bulk partitioning)
    c0 = array("i", [-1])
    c1 = array("i", [-1])
    rep = array("i", [-1])  # representative value for size-1 subsets
    stack = [(0, vals, maxb)]
    while stack:
        node, vs, bit = stack.pop()
        if len(vs) == 1:
            rep[node] = vs[0]
            continue
        if bit < 0:
            rep[node] = vs[0]
            continue
        lo = [v for v in vs if not (v >> bit) & 1]
        hi = [v for v in vs if (v >> bit) & 1]
        if lo:
            child = len(c0)
            c0.append(-1); c1.append(-1); rep.append(-1)
            c0[node] = child
            stack.append((child, lo, bit - 1))
        if hi:
            child = len(c0)
            c0.append(-1); c1.append(-1); rep.append(-1)
            c1[node] = child
            stack.append((child, hi, bit - 1))
    # walk query groups down the trie; each group shares its answer prefix.
    # groups hold (x, original_index) pairs.
    stack = [(0, list(zip(queries, range(len(queries)))), maxb, 0)]
    while stack:
        node, qs, bit, acc = stack.pop()
        if not qs:
            continue
        if bit < 0 or rep[node] != -1:
            if rep[node] != -1 and bit >= 0:
                v = rep[node]
                keep = (1 << (bit + 1)) - 1
                for x, i in qs:
                    res[i] = acc | ((v ^ x) & keep)
            else:
                for x, i in qs:
                    res[i] = acc
            continue
        ch0 = c0[node]
        ch1 = c1[node]
        q1 = [p for p in qs if (p[0] >> bit) & 1]
        q0 = [p for p in qs if not (p[0] >> bit) & 1]
        b = 1 << bit
        if q0:
            if ch1 != -1:
                stack.append((ch1, q0, bit - 1, acc | b))
            elif ch0 != -1:
                stack.append((ch0, q0, bit - 1, acc))
        if q1:
            if ch0 != -1:
                stack.append((ch0, q1, bit - 1, acc | b))
            elif ch1 != -1:
                stack.append((ch1, q1, bit - 1, acc))
    return res


def solve_case(n, W, V):
    maxb = max(V).bit_length() - 1 if n else 0
    # find cycle nodes by indegree elimination
    indeg = [0] * n
    for w in W:
        indeg[w] += 1
    dq = deque(i for i in range(n) if indeg[i] == 0)
    removed = [False] * n
    order = []
    while dq:
        u = dq.popleft()
        removed[u] = True
        order.append(u)
        w = W[u]
        indeg[w] -= 1
        if indeg[w] == 0:
            dq.append(w)

    # down[u] = xor of V along the tail from u up to (excluding) the cycle;
    # entry[u] = the cycle node where u's chain lands.
    down = [0] * n
    entry = list(range(n))
    for u in reversed(order):
        w = W[u]
        down[u] = V[u] ^ down[w]
        entry[u] = entry[w]

    radj = [[] for _ in range(n)]
    for u in range(n):
        radj[W[u]].append(u)

    ans = [0] * n
    cycle_part = [0] * n
    seen = [False] * n
    cycles = []
    for start in range(n):
        if removed[start] or seen[start]:
            continue
        cyc = []
        u = start
        while not seen[u]:
            seen[u] = True
            cyc.append(u)
            u = W[u]
        cycles.append(cyc)

    tails_of = {}
    for u in range(n):
        if removed[u]:
            tails_of.setdefault(entry[u], []).append(u)

    # binary trie (with multiplicities) for the down-values on a DFS path.
    # One packed int32 array, 3 slots per node: [child0, child1, count].
    # A deep tail can hold ~1e5 path values at once (~1e6 trie nodes), and
    # plain lists of Python ints for those nodes would blow the memory limit.
    tt = array("i", [-1, -1, 0])
    NEW_NODE = (-1, -1, 0)

    def trie_insert(x):
        t = tt
        node = 0
        t[2] += 1
        for i in range(maxb, -1, -1):
            slot = node + ((x >> i) & 1)
            nxt = t[slot]
            if nxt == -1:
                nxt = len(t)
                t[slot] = nxt
                t.extend(NEW_NODE)
            node = nxt
            t[node + 2] += 1

    def trie_erase(x):
        t = tt
        node = 0
        t[2] -= 1
        for i in range(maxb, -1, -1):
            node = t[node + ((x >> i) & 1)]
            t[node + 2] -= 1

    def trie_max_xor(x):
        t = tt
        node = 0
        res = 0
        for i in range(maxb, -1, -1):
            bit = (x >> i) & 1
            nxt = t[node + (1 - bit)]
            if nxt != -1 and t[nxt + 2] > 0:
                res |= 1 << i
                node = nxt
            else:
                node = t[node + bit]
        return res

    for cyc in cycles:
        c = len(cyc)
        P = [0] * c
        acc = 0
        pos = {}
        for j in range(c):
            P[j] = acc
            pos[cyc[j]] = j
            acc ^= V[cyc[j]]
        cyc_xor = acc

        # batch all cycle-related max-xor queries for this cycle
        queries = []
        owners = []
        for j, node in enumerate(cyc):
            queries.append(P[j])
            queries.append(P[j] ^ cyc_xor)
            owners.append(node)
        tail_nodes = []
        for node in cyc:
            tail_nodes.extend(tails_of.get(node, ()))
        for u in tail_nodes:
            pj = P[pos[entry[u]]]
            queries.append(down[u] ^ pj)
            queries.append(down[u] ^ pj ^ cyc_xor)
            owners.append(u)
        res = batch_max_xor(P, queries, maxb)
        for i, node in enumerate(owners):
            r1 = res[2 * i]
            r2 = res[2 * i + 1]
            best = r1 if r1 >= r2 else r2
            if removed[node]:
                cycle_part[node] = best
            else:
                ans[node] = best

        # DFS into the trees: candidate stops inside the tail itself
        for entry_node in cyc:
            if entry_node not in tails_of:
                continue
            del tt[3:]
            tt[0] = -1; tt[1] = -1; tt[2] = 0
            trie_insert(0)  # down[entry] == 0 is always a candidate stop
            stack = [(ch, 0) for ch in radj[entry_node] if removed[ch]]
            while stack:
                u, phase = stack.pop()
                if phase == 0:
                    du = down[u]
                    best = trie_max_xor(du)
                    if cycle_part[u] > best:
                        best = cycle_part[u]
                    ans[u] = best
                    kids = [ch for ch in radj[u] if removed[ch]]
                    if kids:
                        trie_insert(du)
                        stack.append((u, 1))
                        for ch in kids:
                            stack.append((ch, 0))
                else:
                    trie_erase(down[u])
    return ans


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    t = next(it, 0)
    out_lines = []
    for _ in range(t):
        n = next(it)
        W = [next(it) - 1 for _ in range(n)]
        V = [next(it) for _ in range(n)]
        res = solve_case(n, W, V)
        out_lines.append(" ".join(map(str, res)))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()
