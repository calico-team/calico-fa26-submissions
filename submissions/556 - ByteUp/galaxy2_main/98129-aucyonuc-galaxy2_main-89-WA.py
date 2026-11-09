
import sys
from collections import deque


def solve(N: int, M: int, Q: int, G: list[str],
          start: list[tuple[int, int]],
          end: list[tuple[int, int]],
          K: list[int]) -> list[str]:

    S = N * M
    V = 2 * S
    adj = [[] for _ in range(V)]
    active = bytearray(V)

    for r in range(N):
        for c in range(M):
            p = r * M + c
            ch = G[r][c]

            if ch != 'R':
                active[p] = 1
            if ch != 'B':
                active[p + S] = 1

            if ch == '.':
                adj[p].append(p + S)
                adj[p + S].append(p)

            if r:
                q = p - M
                for mode in (0, S):
                    a = p + mode
                    b = q + mode
                    if active[a] and active[b]:
                        adj[a].append(b)
                        adj[b].append(a)

            if c:
                q = p - 1
                for mode in (0, S):
                    a = p + mode
                    b = q + mode
                    if active[a] and active[b]:
                        adj[a].append(b)
                        adj[b].append(a)

    queries = []
    answers = ["NO"] * Q

    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        if abs(sr - er) + abs(sc - ec) > K[i]:
            continue
        if sr == er and sc == ec:
            answers[i] = "YES"
            continue
        a = sr * M + sc
        b = er * M + ec
        targets = []
        if active[b]:
            targets.append(b)
        if active[b + S]:
            targets.append(b + S)
        if targets:
            queries.append((i, a, targets, min(sc, ec), max(sc, ec)))

    INF = 10**9
    dist = [0] * V
    stamp = [0] * V
    token = 0

    def bfs(src, left, right):
        nonlocal token
        token += 1
        t = token
        dq = deque([src])
        stamp[src] = t
        dist[src] = 0

        while dq:
            u = dq.popleft()
            nd = dist[u] + 1
            for v in adj[u]:
                cell = v % S
                col = cell % M
                if left <= col <= right and stamp[v] != t:
                    stamp[v] = t
                    dist[v] = nd
                    dq.append(v)

        return t

    def recurse(left, right, qs):
        if not qs:
            return

        mid = (left + right) // 2
        boundary = []

        for r in range(N):
            p = r * M + mid
            if active[p]:
                boundary.append(p)
            if active[p + S]:
                boundary.append(p + S)

        best = [INF] * len(qs)

        for src in boundary:
            t = bfs(src, left, right)

            for j, (_, a, targets, _, _) in enumerate(qs):
                if stamp[a] != t:
                    continue
                da = dist[a]
                for b in targets:
                    if stamp[b] == t:
                        value = da + dist[b]
                        if value < best[j]:
                            best[j] = value

        lq = []
        rq = []

        for j, query in enumerate(qs):
            i, a, targets, lo, hi = query

            if best[j] <= K[i]:
                answers[i] = "YES"
                continue

            if left == right:
                continue

            if hi < mid:
                lq.append(query)
            elif lo > mid:
                rq.append(query)

        if left < mid:
            recurse(left, mid - 1, lq)
        if mid < right:
            recurse(mid + 1, right, rq)

    recurse(0, M - 1, queries)
    return answers


def main():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = [input().strip() for _ in range(N)]

        start = []
        end = []
        K = []

        for _ in range(Q):
            sr, sc, er, ec, k = map(int, input().split())
            start.append((sr, sc))
            end.append((er, ec))
            K.append(k)

        result = solve(N, M, Q, G, start, end, K)
        sys.stdout.write("\n".join(result) + "\n")


if __name__ == '__main__':
    main()
