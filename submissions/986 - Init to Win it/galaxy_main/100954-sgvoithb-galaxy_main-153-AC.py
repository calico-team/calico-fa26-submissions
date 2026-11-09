from collections import deque
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
    dest_to_queries = {}
    for i in range(Q):
        dest = end[i]
        if dest not in dest_to_queries:
            dest_to_queries[dest] = []
        dest_to_queries[dest].append(i)
    ans = ["" for _ in range(Q)]
    def is_active(r,c,mode):
        tile = G[r][c]
        if tile == '.':
            return True
        if mode==0 and tile =='B':
            return True
        if mode==1 and tile =='R':
            return True
        return False
    for dest,q_indices in dest_to_queries.items():
        dest_r, dest_c = dest
        dist = [[[-1, -1] for _ in range(M)] for _ in range(N)]
        queue = deque()
        for mode in range(2):
            if is_active(dest_r, dest_c, mode):
                dist[dest_r][dest_c][mode] = 0
                queue.append((dest_r, dest_c, mode))
        while queue:
            r, c, mode = queue.popleft()
            if G[r][c] == '.':
                other_mode = 1 - mode
                if dist[r][c][other_mode] == -1:
                    dist[r][c][other_mode] = dist[r][c][mode] + 1
                    queue.append((r, c, other_mode))
            dr = [-1, 1, 0, 0]
            dc = [0, 0, -1, 1]
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                if 0 <= nr < N and 0 <= nc < M:
                    if is_active(nr, nc, mode) and dist[nr][nc][mode] == -1:
                        dist[nr][nc][mode] = dist[r][c][mode] + 1
                        queue.append((nr, nc, mode))
        for idx in q_indices:
            sr, sc = start[idx]
            if dist[sr][sc][0] != -1:
                ans[idx] = "YES"
            else:
                ans[idx] = "NO"                      
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
