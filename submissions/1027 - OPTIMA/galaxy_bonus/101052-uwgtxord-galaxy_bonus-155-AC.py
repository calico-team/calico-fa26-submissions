
def solve():
    test_cases = int(input())

    for _ in range(test_cases):
        N, M, Q = map(int, input().split())
        board = [input().strip() for _ in range(N)]

        total_cells = N * M

        leader = list(range(2 * total_cells))
        component_size = [1] * (2 * total_cells)

        def find(x):
            if leader[x] != x:
                leader[x] = find(leader[x])
            return leader[x]

        def union(a, b):
            a = find(a)
            b = find(b)

            if a == b:
                return

            if component_size[a] < component_size[b]:
                a, b = b, a

            leader[b] = a
            component_size[a] += component_size[b]

        def get_id(r, c, mode):
            return mode * total_cells + r * M + c

        # Build connected components for both modes
        for mode in range(2):
            for r in range(N):
                for c in range(M):

                    tile = board[r][c]

                    active = (
                        tile == '.' or
                        (mode == 0 and tile == 'B') or
                        (mode == 1 and tile == 'R')
                    )

                    if not active:
                        continue

                    current = get_id(r, c, mode)

                    # Check downward neighbor
                    if r + 1 < N:
                        neighbor = board[r + 1][c]

                        if (neighbor == '.' or
                            (mode == 0 and neighbor == 'B') or
                            (mode == 1 and neighbor == 'R')):
                            union(current, get_id(r + 1, c, mode))

                    # Check right neighbor
                    if c + 1 < M:
                        neighbor = board[r][c + 1]

                        if (neighbor == '.' or
                            (mode == 0 and neighbor == 'B') or
                            (mode == 1 and neighbor == 'R')):
                            union(current, get_id(r, c + 1, mode))

        # Connect blue and red states of normal tiles
        for r in range(N):
            for c in range(M):
                if board[r][c] == '.':
                    union(
                        get_id(r, c, 0),
                        get_id(r, c, 1)
                    )

        # Process all queries
        for _ in range(Q):
            rs, cs, re, ce = map(int, input().split())

            start = get_id(rs, cs, 0)
            blue_end = get_id(re, ce, 0)
            red_end = get_id(re, ce, 1)

            if board[re][ce] != 'R' and find(start) == find(blue_end):
                print("YES")

            elif board[re][ce] != 'B' and find(start) == find(red_end):
                print("YES")

            else:
                print("NO")


if __name__ == "__main__":
    solve()
