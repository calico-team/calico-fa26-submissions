import sys

def main():
    data = sys.stdin.buffer.read().split()
    p = 0
    t = int(data[p]); p += 1
    out = []

    for _ in range(t):
        n = int(data[p]); p += 1
        a = [int(x) - 1 for x in data[p:p+n]]; p += n
        v = [int(x) for x in data[p:p+n]]; p += n

        deg = [0] * n
        rev = [[] for _ in range(n)]
        for i in range(n):
            deg[a[i]] += 1
            rev[a[i]].append(i)

        # peel off everything that isn't on a cycle
        q = [i for i in range(n) if deg[i] == 0]
        qi = 0
        while qi < len(q):
            u = q[qi]; qi += 1
            w = a[u]
            deg[w] -= 1
            if deg[w] == 0:
                q.append(w)

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

            # trie nodes are [left, right, count]
            tr = [[-1, -1, 0]]

            def add(x, d):
                cur = 0
                for b in range(29, -1, -1):
                    bit = (x >> b) & 1
                    nxt = tr[cur][bit]
                    if nxt == -1:
                        nxt = len(tr)
                        tr[cur][bit] = nxt
                        tr.append([-1, -1, 0])
                    cur = nxt
                    tr[cur][2] += d

            def best(x):
                cur = 0
                res = 0
                for b in range(29, -1, -1):
                    bit = (x >> b) & 1
                    nxt = tr[cur][bit ^ 1]
                    if nxt != -1 and tr[nxt][2] > 0:
                        res |= 1 << b
                        cur = nxt
                    else:
                        cur = tr[cur][bit]
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