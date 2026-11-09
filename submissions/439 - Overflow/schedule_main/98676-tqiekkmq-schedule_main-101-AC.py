import sys
from collections import deque

def solve():
    input = sys.stdin.readline
    t = int(input())

    for _ in range(t):
        n, m, k = map(int, input().split())
        p = [x - 1 for x in map(int, input().split())]

        adj = [[] for _ in range(n)]
        roots = []
        deg = [0] * n

        for v in range(n):
            if p[v] == -1:
                roots.append(v)
            else:
                adj[p[v]].append(v)
                deg[p[v]] += 1

        # Bottom-up computation subtree heights
        h = [1] * n
        dq = deque(v for v in range(n) if deg[v] == 0)

        while dq:
            v = dq.popleft()
            u = p[v]

            if u != -1:
                h[u] = max(h[u], h[v] + 1)
                deg[u] -= 1

                if deg[u] == 0:
                    dq.append(u)

        # Group initally courses by height
        buckets = [[] for _ in range(1002)]
        mx = 0

        for v in roots:
            buckets[h[v]].append(v)
            mx = max(mx, h[v])

        ans = 0

        for _ in range(m):
            selected = 0
            newly_available = []

            while selected < k:
                while mx > 0 and not buckets[mx]:
                    mx -= 1

                if mx == 0:
                    break

                v = buckets[mx].pop()
                ans += 1
                selected += 1

                newly_available.extend(adj[v])

            if selected == 0:
                break

            for v in newly_available:
                buckets[h[v]].append(v)
                mx = max(mx, h[v])

        print(ans)

if __name__ == "__main__":
    solve()
