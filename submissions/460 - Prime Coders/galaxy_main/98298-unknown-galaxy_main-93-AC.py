def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    # """
    # Return an array of Q strings, the i-th of which is "YES"
    # if Big Ben can travel from start[i] to end[i], and "NO"
    # otherwise.

    # N: the number of rows in the grid
    # M: the number of columns in the grid
    # Q: the number of queries
    # G: the grid, where each tile is 'R', 'B', or '.'
    # start: the (row, column) of the starting tile of each query
    # end: the (row, column) of the ending tile of each query
    # """
    # # YOUR CODE HERE
    # return []

    parent = list(range(2 * N * M))
    size = [1] * (2 * N * M)

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        a = find(a)
        b = find(b)

        if a != b:
            if size[a] < size[b]:
                a, b = b, a

            parent[b] = a
            size[a] += size[b]

    def get_id(r, c, mode):
        return (r * M + c) * 2 + mode

    def active(tile, mode):
        if tile == '.':
            return True
        if mode == 0 and tile == 'R':
            return True
        if mode == 1 and tile == 'B':
            return True
        return False

    for r in range(N):
        for c in range(M):

            tile = G[r][c]

            if tile == '.':
                union(get_id(r, c, 0),
                      get_id(r, c, 1))

            for mode in range(2):

                if not active(tile, mode):
                    continue

                if c + 1 < M and active(G[r][c + 1], mode):
                    union(get_id(r, c, mode),
                          get_id(r, c + 1, mode))

                if r + 1 < N and active(G[r + 1][c], mode):
                    union(get_id(r, c, mode),
                          get_id(r + 1, c, mode))

    ans = []

    for i in range(Q):

        sr, sc = start[i]
        er, ec = end[i]

        source = get_id(sr, sc, 1)
        source_root = find(source)

        destination = G[er][ec]

        if destination == '.':
            possible_modes = [0, 1]
        elif destination == 'R':
            possible_modes = [0]
        else:
            possible_modes = [1]

        possible = False

        for mode in possible_modes:
            target = get_id(er, ec, mode)

            if source_root == find(target):
                possible = True
                break

        ans.append("YES" if possible else "NO")

    return ans

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end = [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
        for s in solve(N, M, Q, G, start, end):
            print(s)

if __name__ == '__main__':
    main()