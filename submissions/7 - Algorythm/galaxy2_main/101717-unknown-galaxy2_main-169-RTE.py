
from array import array


def solve(N: int, M: int, Q: int, G: list[str],
          start: list[tuple[int, int]],
          end: list[tuple[int, int]],
          K: list[int]) -> list[str]:

    S = 2 * N
    V = M * S

    # Build the graph.
    adj = [[] for _ in range(V)]
    valid = bytearray(V)

    # Determine which states are valid.
    for c in range(M):
        for r in range(N):
            ch = G[r][c]
            base = c * S + r * 2

            if ch == '.':
                valid[base] = 1
                valid[base + 1] = 1
            elif ch == 'B':
                valid[base] = 1
            else:
                valid[base + 1] = 1

    # Construct graph edges.
    for c in range(M):
        for r in range(N):
            ch = G[r][c]

            for mode in range(2):
                u = c * S + r * 2 + mode

                if not valid[u]:
                    continue

                # Spin action on normal tiles.
                if ch == '.' and mode == 0:
                    v = u + 1
                    adj[u].append(v)
                    adj[v].append(u)

                # Move vertically.
                if r > 0:
                    v = u - 2
                    if valid[v]:
                        adj[u].append(v)
                        adj[v].append(u)

                # Move horizontally.
                if c > 0:
                    v = u - S
                    if valid[v]:
                        adj[u].append(v)
                        adj[v].append(u)

    # Divide-and-conquer preprocessing.
    # Each node stores distances from its middle-column
    # states to every state inside its interval.

    def build(l, r):
        mid = (l + r) // 2

        base = l * S
        size = (r - l + 1) * S

        dists = [None] * S

        # BFS from every valid state in the middle column.
        for si in range(S):
            src = mid * S + si

            if not valid[src]:
                continue

            dist = array('i', [-1]) * size

            dist[src - base] = 0

            queue = [src]
            head = 0

            while head < len(queue):
                u = queue[head]
                head += 1

                nd = dist[u - base] + 1

                for v in adj[u]:
                    vi = v - base

                    if 0 <= vi < size and dist[vi] == -1:
                        dist[vi] = nd
                        queue.append(v)

            dists[si] = dist

        left = build(l, mid - 1) if l < mid else None
        right = build(mid + 1, r) if mid < r else None

        return (l, r, mid, dists, left, right)

    root = build(0, M - 1)

    # Answer queries.
    answers = []

    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        k = K[i]

        # Starting state: blue mode.
        target_tile = G[er][ec]

        # Possible destination modes.
        if target_tile == '.':
            modes = (0, 1)
        elif target_tile == 'B':
            modes = (0,)
        else:
            modes = (1,)

        target_offsets = [
            ec * S + er * 2 + mode
            for mode in modes
        ]

        # Starting state has blue mode.
        start_id = sc * S + sr * 2

        best = 10**18

        # Collect all separator nodes on the path
        # containing both query endpoints.
        nodes = []
        node = root

        lo = min(sc, ec)
        hi = max(sc, ec)

        while node is not None:
            nodes.append(node)

            l, r, mid, dists, left, right = node

            if lo < mid and hi < mid:
                node = left
            elif lo > mid and hi > mid:
                node = right
            else:
                break

        # Find the shortest path through any separator.
        for l, r, mid, dists, left, right in nodes:

            uoff = start_id - l * S

            for si in range(S):
                ds = dists[si]

                if ds is None:
                    continue

                du = ds[uoff]

                if du < 0:
                    continue

                for voff in target_offsets:
                    dv = ds[voff]

                    if dv >= 0:
                        candidate = du + dv

                        if candidate < best:
                            best = candidate

        answers.append("YES" if best <= k else "NO")

    return answers


def main():
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())

        G = []
        for _ in range(N):
            G.append(input())

        start, end, K = [], [], []

        for _ in range(Q):
            start_row, start_col, end_row, end_col, k = map(int, input().split())

            start.append((start_row, start_col))
            end.append((end_row, end_col))
            K.append(k)

        for s in solve(N, M, Q, G, start, end, K):
            print(s)


if __name__ == '__main__':
    main()
