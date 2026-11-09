import sys
from collections import deque
from array import array

input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n = int(input())
    f = [x - 1 for x in map(int, input().split())]
    v = list(map(int, input().split()))

    rev = [[] for _ in range(n)]
    deg = [0] * n

    for i in range(n):
        rev[f[i]].append(i)
        deg[f[i]] += 1

    q = deque(i for i in range(n) if deg[i] == 0)

    while q:
        u = q.popleft()
        deg[f[u]] -= 1
        if deg[f[u]] == 0:
            q.append(f[u])

    # Persistent binary trie
    L = array('i', [0])
    R = array('i', [0])
    C = array('i', [0])

    def insert(root, x):
        nr = len(C)
        L.append(L[root])
        R.append(R[root])
        C.append(C[root] + 1)

        a = nr
        b = root

        for bit in range(29, -1, -1):
            z = (x >> bit) & 1

            old = R[b] if z else L[b]
            new = len(C)

            L.append(L[old])
            R.append(R[old])
            C.append(C[old] + 1)

            if z:
                R[a] = new
            else:
                L[a] = new

            a = new
            b = old

        return nr

    def maxxor(x, hi, lo):
        ans = 0

        for bit in range(29, -1, -1):
            z = (x >> bit) & 1

            if z:
                a, b = L[hi], L[lo]
                c, d = R[hi], R[lo]
            else:
                a, b = R[hi], R[lo]
                c, d = L[hi], L[lo]

            if C[a] - C[b] > 0:
                ans |= (1 << bit)
                hi, lo = a, b
            else:
                hi, lo = c, d

        return ans

    zero = insert(0, 0)

    ans = [0] * n
    seen = [False] * n

    # Find and process every cycle
    for start in range(n):
        if deg[start] == 0 or seen[start]:
            continue

        cycle = []
        u = start

        while not seen[u]:
            seen[u] = True
            cycle.append(u)
            u = f[u]

        m = len(cycle)

        # Prefix XORs around the cycle
        p = [0] * (2 * m + 1)

        for i in range(2 * m):
            p[i + 1] = p[i] ^ v[cycle[i % m]]

        total = p[m]

        # Persistent tries for cycle prefix ranges
        roots = [0]

        for x in p:
            roots.append(insert(roots[-1], x))

        def cycle_best(key):
            r = maxxor(
                key,
                roots[j + m + 1],
                roots[j + 1]
            )

            if total:
                r = max(
                    r,
                    maxxor(
                        key ^ total,
                        roots[j + m + 1],
                        roots[j + 1]
                    )
                )

            return r

        # Process each cycle node and its attached tree
        for j in range(m):
            root = cycle[j]

            ans[root] = cycle_best(p[j])

            stack = [(child, root) for child in rev[root]
                     if deg[child] == 0]

            while stack:
                x, parent = stack.pop()

                d = v[x] ^ dist[parent]
                dist[x] = d

                pathroot[x] = insert(
                    pathroot[parent],
                    dist[parent]
                )

                a = maxxor(d, pathroot[x], 0)
                b = cycle_best(d ^ p[j])

                ans[x] = max(a, b)

                for child in rev[x]:
                    if deg[child] == 0:
                        stack.append((child, x))

    print(*ans)