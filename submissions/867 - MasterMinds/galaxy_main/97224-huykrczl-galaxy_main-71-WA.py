
import sys

def solve():
    input = sys.stdin.readline

    t = int(input())

    for _ in range(t):
        n, m, q = map(int, input().split())
        grid = [input().strip() for _ in range(n)]

       
        total = n * m * 2

        parent = list(range(total))
        size = [1] * total

        def get_id(r, c, mode):
            return (r * m + c) * 2 + mode

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

        def valid(r, c, mode):
            tile = grid[r][c]

            return (
                tile == '.' or
                (mode == 0 and tile == 'B') or
                (mode == 1 and tile == 'R')
            )

      
        for r in range(n):
            for c in range(m):

               
                if grid[r][c] == '.':
                    union(
                        get_id(r, c, 0),
                        get_id(r, c, 1)
                    )

               
                for dr, dc in [(0, 1), (1, 0)]:
                    nr = r + dr
                    nc = c + dc

                    if nr >= n or nc >= m:
                        continue

                    for mode in range(2):
                        if valid(r, c, mode) and valid(nr, nc, mode):
                            union(
                                get_id(r, c, mode),
                                get_id(nr, nc, mode)
                            )

       
        for _ in range(q):
            r1, c1, r2, c2 = map(int, input().split())

            start = get_id(r1, c1, 0)
            end = get_id(r2, c2, 0)

            if find(start) == find(end):
                print("YES")
            else:
                print("NO")


if __name__ == "__main__":
    solve()
