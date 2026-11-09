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
    visit = [[[0] * 2 for _ in range(M)] for _ in range(N)]
    question_id = 0
    out = []
    for (r1,c1), (r2,c2) in zip(start, end):
        if r1 == r2 and c1 == c2:
            out.append("YES")
            continue
        question_id += 1
        queue=deque()

        queue.append((r1, c1, 0))
        visit[r1][c1][0] = question_id
        Got = False
        while queue:
            r, c, mode = queue.popleft()
            if r == r2 and c == c2:
                Got = True
                break
            if G[r][c] == '.':
                next_mode = 1 - mode
                if visit[r][c][next_mode] != question_id:
                    visit[r][c][next_mode] = question_id
                    queue.append((r, c, next_mode))

            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < N and 0 <= nc < M:
                    tile = G[nr][nc]
                    active = False
                    if tile == '.':
                        active = True
                    elif tile == 'B' and mode == 0:
                        active = True
                    elif tile == 'R' and mode == 1:
                        active = True
                    if active and visit[nr][nc][mode] != question_id:
                        visit[nr][nc][mode] = question_id
                        queue.append((nr, nc, mode))
        if Got:
            out.append("YES")
        else:
            out.append("NO")
            
    return out

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
