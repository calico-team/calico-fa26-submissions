def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    size = 2 * N * M
    parent = list(range(size))
    rank = [0] * size

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        a = find(a)
        b = find(b)
        if a == b:
            return
        if rank[a] < rank[b]:
            a, b = b, a
        parent[b] = a
        if rank[a] == rank[b]:
            rank[a] += 1

    def node(r, c, mode):
        return (r * M + c) * 2 + mode

    def active(r, c, mode):
        tile = G[r][c]
        return tile == "." or (tile == "B" and mode == 0) or (tile == "R" and mode == 1)

    for r in range(N):
        for c in range(M):
            if G[r][c] == ".":
                union(node(r, c, 0), node(r, c, 1))

            for mode in (0, 1):
                if not active(r, c, mode):
                    continue

                if r + 1 < N and active(r + 1, c, mode):
                    union(node(r, c, mode), node(r + 1, c, mode))

                if c + 1 < M and active(r, c + 1, mode):
                    union(node(r, c, mode), node(r, c + 1, mode))

    results = []
    for (sr, sc), (er, ec) in zip(start, end):
        source = find(node(sr, sc, 0))
        tile = G[er][ec]

        if tile == ".":
            possible = (
                source == find(node(er, ec, 0))
                or source == find(node(er, ec, 1))
            )
        elif tile == "B":
            possible = source == find(node(er, ec, 0))
        else:
            possible = source == find(node(er, ec, 1))

        results.append("YES" if possible else "NO")

    return results


def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = [input().strip() for _ in range(N)]
        start = []
        end = []

        for _ in range(Q):
            sr, sc, er, ec = map(int, input().split())
            start.append((sr, sc))
            end.append((er, ec))

        print("\n".join(solve(N, M, Q, G, start, end)))


if __name__ == "__main__":
    main()
