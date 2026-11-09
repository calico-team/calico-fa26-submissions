
def solve():
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())

        board = [input().strip() for _ in range(N)]

        total = N * M

        parent = list(range(2 * total))
        size = [1] * (2 * total)

        # Find representative of a component
        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        # Merge two components
        def union(a, b):
            a = find(a)
            b = find(b)

            if a == b:
                return

            if size[a] < size[b]:
                a, b = b, a

            parent[b] = a
            size[a] += size[b]

        # Get index of a cell in a particular mode
        def get_id(r, c, mode):
            return mode * total + r * M + c

        # Build connectivity for both modes
        for mode in range(2):
            for r in range(N):
                for c in range(M):

                    cell = board[r][c]

                    # Check whether current cell is active
                    active = (
                        cell == '.' or
                        (mode == 0 and cell == 'B') or
                        (mode == 1 and cell == 'R')
                    )

                    if not active:
                        continue

                    current = get_id(r, c, mode)

                    # Connect with the cell below
                    if r + 1 < N:
                        nxt = board[r + 1][c]

                        next_active = (
                            nxt == '.' or
                            (mode == 0 and nxt == 'B') or
                            (mode == 1 and nxt == 'R')
                        )

                        if next_active:
                            union(current, get_id(r + 1, c, mode))

                    # Connect with the cell on the right
                    if c + 1 < M:
                        nxt = board[r][c + 1]

                        next_active = (
                            nxt == '.' or
                            (mode == 0 and nxt == 'B') or
                            (mode == 1 and nxt == 'R')
                        )

                        if next_active:
                            union(current, get_id(r, c + 1, mode))

        # Connect both modes at every normal tile
        for r in range(N):
            for c in range(M):
                if board[r][c] == '.':
                    blue = get_id(r, c, 0)
                    red = get_id(r, c, 1)

                    union(blue, red)

        # Process queries
        for _ in range(Q):
            rs, cs, re, ce = map(int, input().split())

            start_node = get_id(rs, cs, 0)

            blue_end = get_id(re, ce, 0)
            red_end = get_id(re, ce, 1)

            # Check whether destination is active
            # and reachable in either mode
            if board[re][ce] != 'R' and find(start_node) == find(blue_end):
                print("YES")

            elif board[re][ce] != 'B' and find(start_node) == find(red_end):
                print("YES")

            else:
                print("NO")


if __name__ == "__main__":
    solve()
