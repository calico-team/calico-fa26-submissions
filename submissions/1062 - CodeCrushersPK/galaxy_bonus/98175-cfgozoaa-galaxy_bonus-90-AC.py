def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    """
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i], and "NO"
    otherwise.

    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where each tile is 'R', 'B', or '.'
    start: the (row, column) of the starting tile of each query
    end: the (row, column) of the ending tile of each query
    """
    # YOUR CODE HERE
    parent = list(range(N * M))
    size = [1] * (N * M)
    
    def find(x):
        if parent[x] != x:
            parent[x] = find(parent[x])
        return parent[x]

    def union(a, b):
        root_a = find(a)
        root_b = find(b)

        if root_a == root_b:
            return
        if size[root_a] < size[root_b]:
            root_a, root_b = root_b, root_a

        parent[root_b] = root_a
        size[root_a] += size[root_b]

    for r in range(N):
        for c in range(M):
            current = G[r][c]
            current_id = r * M + c

            if c + 1 < M:
                right = G[r][c + 1]
                if current == right or current == "." or right == ".":
                    union(current_id, current_id + 1)

            if r + 1 < N:
                bottom = G[r + 1][c]
                if current == bottom or current == "." or bottom == ".":
                    union(current_id, current_id + M)

    result = []

    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]

        start_id = sr * M + sc
        end_id = er * M + ec

        if find(start_id) == find(end_id):
            result.append("YES")
        else:
            result.append("NO")

    
    return result

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
