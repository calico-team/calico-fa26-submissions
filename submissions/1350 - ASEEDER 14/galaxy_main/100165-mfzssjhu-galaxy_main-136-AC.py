import sys
from collections import deque

def solve(N, M, Q, grid, queries):
    """
    N: 矩阵行数 (int)
    M: 矩阵列数 (int)
    Q: 询问次数 (int)
    grid: 包含 N 个字符串的列表，代表地图
    queries: 包含 Q 个元素的列表，每个元素为 [r_start, c_start, r_end, c_end]
    """

    comp = [[[-1, -1] for _ in range(M)] for _ in range(N)]
    comp_id = 0

    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]

    for r in range(N):
        for c in range(M):
            for m in range(2):
                if comp[r][c][m] == -1:
                    tile = grid[r][c]
                    if m == 0 and tile == 'R': continue
                    if m == 1 and tile == 'B': continue

                    queue = deque([(r, c, m)])
                    comp[r][c][m] = comp_id

                    while queue:
                        curr_r, curr_c, curr_m = queue.popleft()

                        for i in range(4):
                            nr, nc = curr_r + dr[i], curr_c + dc[i]
                            if 0 <= nr < N and 0 <= nc < M and comp[nr][nc][curr_m] == -1:
                                ntile = grid[nr][nc]
                                if (curr_m == 0 and ntile != 'R') or (curr_m == 1 and ntile != 'B'):
                                    comp[nr][nc][curr_m] = comp_id
                                    queue.append((nr, nc, curr_m))
                        if grid[curr_r][curr_c] == '.':
                            next_m = 1 - curr_m
                            if comp[curr_r][curr_c][next_m] == -1:
                                comp[curr_r][curr_c][next_m] = comp_id
                                queue.append((curr_r, curr_c, next_m))  
                    comp_id += 1

    results = []
    for r_start, c_start, r_end, c_end in queries:
        start_color = comp[r_start][c_start][0]
        end_color_blue = comp[r_end][c_end][0]
        end_color_red = comp[r_end][c_end][1]

        if start_color != -1 and (start_color == end_color_blue or start_color == end_color_red):
            results.append("YES")
        else:
            results.append("NO")

    return results

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))

    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))

        grid = [next(iterator) for _ in range(N)]

        queries = []
        for _ in range(Q):
            r1 = int(next(iterator))
            c1 = int(next(iterator))
            r2 = int(next(iterator))
            c2 = int(next(iterator))
            queries.append([r1, c1, r2, c2])

        ans = solve(N, M, Q, grid, queries)
        print('\n'.join(ans))

if __name__ == '__main__':
    main()