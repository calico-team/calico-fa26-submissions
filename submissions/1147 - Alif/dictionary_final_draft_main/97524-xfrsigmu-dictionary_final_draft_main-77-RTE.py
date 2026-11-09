import sys
from collections import deque

def main():
    read = sys.stdin.buffer.readline
    t = int(read())
    out = []

    for _ in range(t):
        n = int(read())
        a = [x - 1 for x in map(int, read().split())]
        v = list(map(int, read().split()))

        deg = [0] * n
        rev = [[] for _ in range(n)]
        for i in range(n):
            deg[a[i]] += 1
            rev[a[i]].append(i)

        q = deque(i for i in range(n) if deg[i] == 0)
        while q:
            u = q.popleft()
            nxt = a[u]
            deg[nxt] -= 1
            if deg[nxt] == 0:
                q.append(nxt)

        ans = [0] * n
        pref = [0] * n
        vis = [False] * n

        for s in range(n):
            if deg[s] == 0 or vis[s]:
                continue

            cyc = []
            tot = 0
            u = s
            while True:
                vis[u] = True
                cyc.append(u)
                pref[u] = tot
                tot ^= v[u]
                u = a[u]
                if u == s:
                    break

            # trie: nodes are [left, right, count], root is 0
            trie = [[-1, -1, 0]]

            def add(x, d):
                cur = 0
                for b in range(29, -1, -1):
                    bit = (x >> b) & 1
                    nxt = trie[cur][bit]
                    if nxt == -1:
                        nxt = len(trie)
                        trie[cur][bit] = nxt
                        trie.append([-1, -1, 0])
                    cur = nxt
                    trie[cur][2] += d

            def best(x):
                cur = 0
                res = 0
                for b in range(29, -1, -1):
                    bit = (x >> b) & 1
                    nxt = trie[cur][bit ^ 1]
                    if nxt != -1 and trie[nxt][2] > 0:
                        res |= 1 << b
                        cur = nxt
                    else:
                        cur = trie[cur][bit]
                return res

            for x in cyc:
                add(pref[x], 1)
                if tot:
                    add(pref[x] ^ tot, 1)

            for x in cyc:
                ans[x] = best(pref[x])

            stack = []
            for x in cyc:
                for c in rev[x]:
                    if deg[c] == 0:
                        stack.append((c, pref[x] ^ v[c], False))

            while stack:
                node, x, done = stack.pop()
                if done:
                    add(x, -1)
                    continue
                ans[node] = best(x)
                add(x, 1)
                stack.append((node, x, True))
                for c in rev[node]:
                    stack.append((c, x ^ v[c], False))

        out.append(" ".join(map(str, ans)))

    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    main()