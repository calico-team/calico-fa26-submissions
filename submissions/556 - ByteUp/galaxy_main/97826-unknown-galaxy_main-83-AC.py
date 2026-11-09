
import sys


def solve(N: int, M: int, Q: int, G: list[str],
          start: list[tuple[int, int]],
          end: list[tuple[int, int]]) -> list[str]:

    cells = N * M
    parent = list(range(2 * cells))
    size = [1] * (2 * cells)

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

        if size[a] < size[b]:
            a, b = b, a

        parent[b] = a
        size[a] += size[b]

    for r in range(N):
        for c in range(M):
            idx = r * M + c
            tile = G[r][c]

            if tile == '.':
                union(idx, idx + cells)

            if r + 1 < N:
                nxt = (r + 1) * M + c
                other = G[r + 1][c]

                if tile != 'R' and other != 'R':
                    union(idx, nxt)

                if tile != 'B' and other != 'B':
                    union(idx + cells, nxt + cells)

            if c + 1 < M:
                nxt = idx + 1
                other = G[r][c + 1]

                if tile != 'R' and other != 'R':
                    union(idx, nxt)

                if tile != 'B' and other != 'B':
                    union(idx + cells, nxt + cells)

    ans = []

    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]

        s = sr * M + sc
        e = er * M + ec

        root = find(s)

        if G[er][ec] == 'R':
            reachable = root == find(e + cells)
        else:
            reachable = root == find(e)

        ans.append("YES" if reachable else "NO")

    return ans


def main():
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())

        G = []
        for _ in range(N):
            G.append(input().strip())

        start = []
        end = []

        for _ in range(Q):
            sr, sc, er, ec = map(int, input().split())
            start.append((sr, sc))
            end.append((er, ec))

        for s in solve(N, M, Q, G, start, end):
            print(s)


if __name__ == '__main__':
    main()
