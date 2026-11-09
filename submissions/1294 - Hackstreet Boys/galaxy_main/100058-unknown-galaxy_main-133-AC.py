
import sys

def solve():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())
        grid = [input().strip() for _ in range(N)]

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

        def active(r, c, mode):
            ch = grid[r][c]
            return ch == '.' or (mode == 0 and ch == 'B') or (mode == 1 and ch == 'R')

        def node(r, c, mode):
            return (r * M + c) * 2 + mode

        # Build connected components for both modes
        for r in range(N):
            for c in range(M):
                # Spin on normal tiles
                if grid[r][c] == '.':
                    union(node(r, c, 0), node(r, c, 1))

                for mode in range(2):
                    if not active(r, c, mode):
                        continue

                    # Connect right neighbor
                    if c + 1 < M and active(r, c + 1, mode):
                        union(node(r, c, mode), node(r, c + 1, mode))

                    # Connect bottom neighbor
                    if r + 1 < N and active(r + 1, c, mode):
                        union(node(r, c, mode), node(r + 1, c, mode))

        # Answer queries
        for _ in range(Q):
            rs, cs, re, ce = map(int, input().split())

            start = find(node(rs, cs, 0))

            possible = False

            for mode in range(2):
                if active(re, ce, mode):
                    if start == find(node(re, ce, mode)):
                        possible = True
                        break

            print("YES" if possible else "NO")


if __name__ == "__main__":
    solve()
