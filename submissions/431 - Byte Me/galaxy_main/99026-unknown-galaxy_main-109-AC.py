def solve(N, M, Q):
    grid = [input().strip() for _ in range(N)]
    component = [[[-1, -1] for _ in range(M)] for _ in range(N)]
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    number = 0
 
    for r in range(N):
        for c in range(M):
            for mode in range(2):
                tile = grid[r][c]
                if (tile == 'R' and mode == 0) or (tile == 'B' and mode == 1):
                    continue
                if component[r][c][mode] != -1:
                    continue
 
                queue = [(r, c, mode)]
                component[r][c][mode] = number
                head = 0
 
                while head < len(queue):
                    x, y, color = queue[head]
                    head += 1
 
                    if grid[x][y] == '.' and component[x][y][1 - color] == -1:
                        component[x][y][1 - color] = number
                        queue.append((x, y, 1 - color))
 
                    for dx, dy in directions:
                        nx, ny = x + dx, y + dy
                        if 0 <= nx < N and 0 <= ny < M:
                            next_tile = grid[nx][ny]
                            if next_tile == '.' or (next_tile == 'B' and color == 0) or (next_tile == 'R' and color == 1):
                                if component[nx][ny][color] == -1:
                                    component[nx][ny][color] = number
                                    queue.append((nx, ny, color))
                number += 1
 
    for _ in range(Q):
        r1, c1, r2, c2 = map(int, input().split())
        start = component[r1][c1][0]
        if start in component[r2][c2]:
            print('YES')
        else:
            print('NO')
 
 
def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        solve(N, M, Q)
 
 
if __name__ == '__main__':
    main()