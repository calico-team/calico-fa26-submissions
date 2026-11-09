
from collections import deque


def solve():
    T = int(input())
    answers = []

    for _ in range(T):
        N, M, Q = map(int, input().split())
        grid = [input().strip() for _ in range(N)]

        total = 2 * N * M
        width = 2 * N

        adj = [[] for _ in range(total)]
        valid = [False] * total


        for c in range(M):
            for r in range(N):
                p = (c * N + r) * 2
                tile = grid[r][c]

                valid[p] = tile != 'R'
                valid[p + 1] = tile != 'B'

  
                if tile == '.':
                    adj[p].append(p + 1)
                    adj[p + 1].append(p)

                for nr, nc in ((r - 1, c), (r, c - 1)):
                    if nr < 0 or nc < 0:
                        continue

                    other = (nc * N + nr) * 2

                    for mode in (0, 1):
                        a = p + mode
                        b = other + mode

                        if valid[a] and valid[b]:
                            adj[a].append(b)
                            adj[b].append(a)

        starts = []
        ends = []
        start_cols = []
        end_cols = []
        limits = []

        for _ in range(Q):
            rs, cs, re, ce, K = map(int, input().split())

            s = (cs * N + rs) * 2
            e = (ce * N + re) * 2

            starts.append(s)

            if grid[re][ce] == 'R':
                ends.append((e + 1,))
            elif grid[re][ce] == 'B':
                ends.append((e,))
            else:
                ends.append((e, e + 1))

            start_cols.append(cs)
            end_cols.append(ce)
            limits.append(K)

        reachable = [False] * Q

        seen = [0] * total
        dist = [0] * total
        stamp = 0

        def divide(left, right, ids):
            nonlocal stamp

            if not ids:
                return

            mid = (left + right) // 2

            for r in range(N):
                for mode in (0, 1):

                    source = (mid * N + r) * 2 + mode

                    if not valid[source]:
                        continue

                    stamp += 1
                    seen[source] = stamp
                    dist[source] = 0

                    queue = deque([source])

                    while queue:
                        u = queue.popleft()
                        nd = dist[u] + 1

                        for v in adj[u]:
                            if seen[v] == stamp:
                                continue

                            col = v // width

                            if col < left or col > right:
                                continue

                            seen[v] = stamp
                            dist[v] = nd
                            queue.append(v)

                    for qi in ids:

                        if reachable[qi]:
                            continue

                        s = starts[qi]

                        if seen[s] != stamp:
                            continue

                        ds = dist[s]

                        if ds > limits[qi]:
                            continue

                        for e in ends[qi]:
                            if (seen[e] == stamp and
                                    ds + dist[e] <= limits[qi]):
                                reachable[qi] = True
                                break

            left_ids = []
            right_ids = []

            for qi in ids:
                if reachable[qi]:
                    continue

                a = start_cols[qi]
                b = end_cols[qi]

                if a < mid and b < mid:
                    left_ids.append(qi)
                elif a > mid and b > mid:
                    right_ids.append(qi)

            if left < mid:
                divide(left, mid - 1, left_ids)

            if mid < right:
                divide(mid + 1, right, right_ids)

        divide(0, M - 1, list(range(Q)))

        for result in reachable:
            answers.append("YES" if result else "NO")

    print("\n".join(answers))


if __name__ == "__main__":
    solve()
