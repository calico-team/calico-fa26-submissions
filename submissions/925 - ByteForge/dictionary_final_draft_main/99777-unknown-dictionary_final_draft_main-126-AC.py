
from array import array
from collections import deque
import sys

def solve(N, A, V):
    A = [x - 1 for x in A]
    deg = [0] * N
    head = [-1] * N
    link = [-1] * N

    for i, j in enumerate(A):
        deg[j] += 1
        link[i] = head[j]
        head[j] = i

    q = deque(i for i in range(N) if not deg[i])
    order = []

    while q:
        u = q.popleft()
        order.append(u)
        v = A[u]
        deg[v] -= 1
        if not deg[v]:
            q.append(v)

    X = [0] * N
    groups = []
    cyc = [d > 0 for d in deg]

    for c in range(N):
        if not deg[c]:
            continue
        cycle = []
        u = c
        while deg[u]:
            deg[u] = 0
            cycle.append(u)
            u = A[u]

        for u in reversed(cycle[1:]):
            X[u] = V[u] ^ X[A[u]]
        groups.append(cycle)

    for u in reversed(order):
        X[u] = V[u] ^ X[A[u]]

    ans = [0] * N

    for cycle in groups:
        left = array('i', [-1])
        right = array('i', [-1])
        cnt = array('i', [0])

        def add(x, delta):
            p = 0
            cnt[p] += delta
            for b in range(29, -1, -1):
                if x >> b & 1:
                    nxt = right[p]
                    if nxt < 0:
                        nxt = len(cnt)
                        right[p] = nxt
                        left.append(-1)
                        right.append(-1)
                        cnt.append(0)
                else:
                    nxt = left[p]
                    if nxt < 0:
                        nxt = len(cnt)
                        left[p] = nxt
                        left.append(-1)
                        right.append(-1)
                        cnt.append(0)
                p = nxt
                cnt[p] += delta

        def query(x):
            p = 0
            out = 0
            for b in range(29, -1, -1):
                t = x >> b & 1
                if t:
                    nxt = left[p]
                    if nxt >= 0 and cnt[nxt]:
                        out |= 1 << b
                    else:
                        nxt = right[p]
                else:
                    nxt = right[p]
                    if nxt >= 0 and cnt[nxt]:
                        out |= 1 << b
                    else:
                        nxt = left[p]
                p = nxt
            return out

        total = 0
        for u in cycle:
            total ^= V[u]

        for u in cycle:
            add(X[u], 1)
            if total:
                add(X[u] ^ total, 1)

        for u in cycle:
            ans[u] = query(X[u])

        stack = []
        for u in cycle:
            j = head[u]
            while j != -1:
                if not cyc[j]:
                    stack.append((j, 0))
                j = link[j]

        while stack:
            u, done = stack.pop()
            if done:
                add(X[u], -1)
                continue

            ans[u] = query(X[u])
            add(X[u], 1)
            stack.append((u, 1))

            j = head[u]
            while j != -1:
                if not cyc[j]:
                    stack.append((j, 0))
                j = link[j]

    return ans


def main():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    out = []

    for _ in range(T):
        N = next(data)
        A = [next(data) for _ in range(N)]
        V = [next(data) for _ in range(N)]
        out.append(' '.join(map(str, solve(N, A, V))))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
