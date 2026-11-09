
import sys

def solve():
    def read_line():
        line = sys.stdin.readline()
        while line and not line.strip():
            line = sys.stdin.readline()
        return line.strip()

    T = int(read_line())

    for _ in range(T):
        N, M, Q = map(int, read_line().split())
        grid = [read_line() for _ in range(N)]

        size = N * M * 2
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

        for r in range(N):
            for c in range(M):
                tile = grid[r][c]

                if tile == '.':
                    union(node(r, c, 0), node(r, c, 1))

                for dr, dc in ((0, 1), (1, 0)):
                    nr, nc = r + dr, c + dc

                    if nr >= N or nc >= M:
                        continue

                    other = grid[nr][nc]

                    if tile != 'R' and other != 'R':
                        union(node(r, c, 0), node(nr, nc, 0))

                    if tile != 'B' and other != 'B':
                        union(node(r, c, 1), node(nr, nc, 1))

        answers = []

        for _ in range(Q):
            sr, sc, er, ec = map(int, read_line().split())

            start = find(node(sr, sc, 0))
            destination = grid[er][ec]

            if destination == 'B':
                reachable = start == find(node(er, ec, 0))

            elif destination == 'R':
                reachable = start == find(node(er, ec, 1))

            else:
                reachable = start == find(node(er, ec, 0))

            answers.append("YES" if reachable else "NO")

        print("\n".join(answers))


if __name__ == "__main__":
    solve()
