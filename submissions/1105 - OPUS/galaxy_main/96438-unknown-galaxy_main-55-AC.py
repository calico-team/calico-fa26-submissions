from collections import deque

def solve():
    T = int(input())

    for _ in range(T):
        h, w, q = map(int, input().split())
        board = [input().strip() for _ in range(h)]

        component = [[[-1] * w for _ in range(h)] for _ in range(2)]
        group_id = 0

        for color in range(2):
            for y in range(h):
                for x in range(w):
                    tile = board[y][x]

                    if component[color][y][x] != -1:
                        continue

                    if tile == 'R' and color == 0:
                        continue
                    if tile == 'B' and color == 1:
                        continue

                    queue = deque([(y, x, color)])
                    component[color][y][x] = group_id

                    while queue:
                        row, col, mode = queue.popleft()

                        if board[row][col] == '.':
                            other = 1 - mode

                            if component[other][row][col] == -1:
                                component[other][row][col] = group_id
                                queue.append((row, col, other))

                        for dy, dx in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                            ny, nx = row + dy, col + dx

                            if not (0 <= ny < h and 0 <= nx < w):
                                continue

                            cell = board[ny][nx]

                            if mode == 0 and cell == 'R':
                                continue
                            if mode == 1 and cell == 'B':
                                continue

                            if component[mode][ny][nx] == -1:
                                component[mode][ny][nx] = group_id
                                queue.append((ny, nx, mode))

                    group_id += 1

        for _ in range(q):
            sy, sx, ey, ex = map(int, input().split())

            start_group = component[0][sy][sx]
            end_mode = 1 if board[ey][ex] == 'R' else 0
            end_group = component[end_mode][ey][ex]

            print("YES" if start_group == end_group else "NO")


solve()
