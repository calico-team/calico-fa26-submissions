from collections import deque
def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]], K: list[int]) -> list[str]:
    """
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i] within K[i]
    seconds, and "NO" otherwise.

    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where each tile is 'R', 'B', or '.'
    start: the (row, column) of the starting tile of each query
    end: the (row, column) of the ending tile of each query
    K: the maximum number of seconds allowed for each query
    """
    results = []
    layerkasize = N * M
    def getnode(r, c, m):
        return m * layerkasize + r * M + c
    for i in range(Q):
        rs, cs = start[i]
        re, ce = end[i]
        KK = K[i]
        dist = [-1] * (2 * layerkasize)
        startnode = getnode(rs, cs, 0)
        dist[startnode] = 0
        queue = deque([startnode])
        possible = False
        while queue:
            curr = queue.popleft()
            d = dist[curr]
            m = curr // layerkasize
            rem = curr % layerkasize
            r = rem // M
            c = rem % M
            if r == re and c == ce:
                if d <= KK:
                    possible = True
                    break
            if d >= KK:
                continue
            if G[r][c] == '.':
                nextnode = getnode(r, c, 1 - m)
                if dist[nextnode] == -1:
                    dist[nextnode] = d + 1
                    queue.append(nextnode)
            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < N and 0 <= nc < M:
                    valid = False
                    if m == 0 and G[nr][nc] in '.B':
                        valid = True
                    elif m == 1 and G[nr][nc] in '.R':
                        valid = True    
                    if valid:
                        nextnode = getnode(nr, nc, m)
                        if dist[nextnode] == -1:
                            dist[nextnode] = d + 1
                            queue.append(nextnode)
        if possible:
            results.append("YES")
        else:
            results.append("NO")
            
    return results

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end, K = [], [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col, k = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
            K.append(k)
        for s in solve(N, M, Q, G, start, end, K):
            print(s)

if __name__ == '__main__':
    main()
