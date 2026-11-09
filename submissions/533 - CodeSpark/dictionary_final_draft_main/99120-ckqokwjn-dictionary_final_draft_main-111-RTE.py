import sys

BITS = 30


class Trie:
    def __init__(self):
        self.nxt = [0, 0]
        self.cnt = [0]
        self.free = []

    def clear(self):
        self.nxt = [0, 0]
        self.cnt = [0]
        self.free = []

    def add(self, v):
        nxt = self.nxt
        cnt = self.cnt
        node = 0
        for b in range(BITS - 1, -1, -1):
            idx = 2 * node + (v >> b & 1)
            child = nxt[idx]
            if not child:
                if self.free:
                    child = self.free.pop()
                    nxt[2 * child] = 0
                    nxt[2 * child + 1] = 0
                    cnt[child] = 0
                else:
                    nxt.append(0)
                    nxt.append(0)
                    cnt.append(0)
                    child = len(cnt) - 1
                nxt[idx] = child
            cnt[child] += 1
            node = child

    def remove(self, v):
        nxt = self.nxt
        cnt = self.cnt
        node = 0
        for b in range(BITS - 1, -1, -1):
            idx = 2 * node + (v >> b & 1)
            child = nxt[idx]
            cnt[child] -= 1
            if cnt[child] == 0:
                nxt[idx] = 0
                self.free.append(child)
            node = child

    def best(self, v):
        nxt = self.nxt
        node = 0
        res = 0
        for b in range(BITS - 1, -1, -1):
            bit = v >> b & 1
            other = nxt[2 * node + (bit ^ 1)]
            if other:
                res |= 1 << b
                node = other
            else:
                node = nxt[2 * node + bit]
        return res


def solve(n, A, V):
    A = [a - 1 for a in A]
    state = [0] * n
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
        if state[u] == 1:
            i = len(path) - 1
            while path[i] != u:
                i -= 1
            cyc = path[i:]
            for x in cyc:
                on_cycle[x] = True
            cycles.append(cyc)
        for x in path:
            state[x] = 2

    children = [[] for _ in range(n)]
    for u in range(n):
        if not on_cycle[u]:
            children[A[u]].append(u)

    ans = [0] * n
    g = [0] * n
    cyc_trie = Trie()
    chain_trie = Trie()

    for cyc in cycles:
        size = len(cyc)
        pre = [0] * (size + 1)
        for k in range(size):
            pre[k + 1] = pre[k] ^ V[cyc[k]]
        total = pre[size]
        cyc_trie.clear()
        for k in range(size):
            cyc_trie.add(pre[k])
            cyc_trie.add(pre[k] ^ total)
        for k in range(size):
            root = cyc[k]
            ans[root] = cyc_trie.best(pre[k])
            if not children[root]:
                continue
            chain_trie.clear()
            chain_trie.add(0)
            g[root] = 0
            stack = [(x, 0) for x in children[root]]
            while stack:
                u, phase = stack.pop()
                if phase:
                    chain_trie.remove(g[u])
                    continue
                g[u] = V[u] ^ g[A[u]]
                a = chain_trie.best(g[u])
                b = cyc_trie.best(g[u] ^ pre[k])
                ans[u] = a if a > b else b
                chain_trie.add(g[u])
                stack.append((u, 1))
                for child in children[u]:
                    stack.append((child, 0))
    return ans


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    t = int(data[pos])
    pos += 1
    out = []
    for _ in range(t):
        n = int(data[pos])
        pos += 1
        A = list(map(int, data[pos:pos + n]))
        pos += n
        V = list(map(int, data[pos:pos + n]))
        pos += n
        out.append(" ".join(map(str, solve(n, A, V))))
    print("\n".join(out))


if __name__ == "__main__":
    main()