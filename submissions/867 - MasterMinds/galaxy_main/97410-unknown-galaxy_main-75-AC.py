
import sys

def solve():
    input = sys.stdin.readline

    t = int(input())

    for _ in range(t):
        n, m, q = map(int, input().split())
        grid = [input().strip() for _ in range(n)]

        parent = list(range(n * m * 2))
        size = [1] * (n * m * 2)

        # Give each cell a unique ID for both modes
        def get_id(r, c, mode):
            return (r * m + c) * 2 + mode

        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(a, b):
            a = find(a)
            b = find(b)

            if a == b:
                return

            if size[a] < size[b]:
                a, b = b, a

            parent[b] = a
            size[a] += size[b]

        # Check whether a cell can be used in a given mode
        def valid(r, c, mode):
            if grid[r][c] == '.':
                return True

            if mode == 0 and grid[r][c] == 'B':
                return True

            if mode == 1 and grid[r][c] == 'R':
                return True

            return False

        # Build the connected components
        for r in range(n):
            for c in range(m):

                # Normal cells allow Ben to change modes
                if grid[r][c] == '.':
                    union(get_id(r, c, 0), get_id(r, c, 1))

                # Check neighbouring cells
                for dr, dc in [(0, 1), (1, 0)]:
                    nr = r + dr
                    nc = c + dc

                    if nr < n and nc < m:
                        for mode in range(2):
                            if valid(r, c, mode) and valid(nr, nc, mode):
                                union(
                                    get_id(r, c, mode),
                                    get_id(nr, nc, mode)
                                )

        # Answer the queries
        for _ in range(q):
            r1, c1, r2, c2 = map(int, input().split())

            start = get_id(r1, c1, 0)
            blue = get_id(r2, c2, 0)
            red = get_id(r2, c2, 1)

            if find(start) == find(blue) or find(start) == find(red):
                print("YES")
            else:
                print("NO")


if __name__ == "__main__":
    solve()
